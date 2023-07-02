#include "simulation.hpp"
#include "CollisionAcceleration.hpp"
#include "ConstraintSolver.hpp"
#include "SimpleIntegrator.hpp"
#include "SimulationState.hpp"
#include <iostream>
#include <memory>
#include <raylib.h>

Simulation::Simulation(std::unique_ptr<SimulationState> &state,
                       std::unique_ptr<ConstraintSolver>& c_solver,
                       std::unique_ptr<CollisionAcceleration>& accelerator,
                       float deltaT) {
    _deltaT = deltaT;
    _state = std::move(state);
    _constraint_solver = std::move(c_solver);
    _integrator = std::make_unique<SimpleIntegrator>(deltaT);
    _renderer = std::make_unique<Renderer>();
    _collision_acceleration = std::move(accelerator);
}

void Simulation::iteration() {
    const unsigned int SUBSTEPS = 8;
    const float subDeltaT = _deltaT / SUBSTEPS;
    _integrator->setDeltaT(subDeltaT);
    _constraint_solver->setDeltaT(subDeltaT);

    for (int i = 0; i < SUBSTEPS; i++) {
        // Update positions and velocities
        _integrator->integrate(*_state);


        // Solve all constraints
        _collision_acceleration->handleCollisions(*_constraint_solver);
        _constraint_solver->solve_constraints();

        // Calculate the new velocities based on new positions
        _state->updateVelocities(subDeltaT);
    }
};

void Simulation::start() {
    bool frame_by_frame = true;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) frame_by_frame = !frame_by_frame;
        if (!frame_by_frame or IsKeyPressed(KEY_ENTER)) {
            iteration();
        }
        // Render
        if (_renderer)
            _renderer->draw(*_state);
    }

}
