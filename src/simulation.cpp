#include "simulation.hpp"
#include "ConstraintSolver.hpp"
#include "SimpleIntegrator.hpp"
#include "SimulationState.hpp"
#include <memory>
#include <raylib.h>

Simulation::Simulation(std::unique_ptr<SimulationState> &state, std::unique_ptr<ConstraintSolver>& c_solver, float deltaT) {
    _deltaT = deltaT;
    _state = std::move(state);
    _constraint_solver = std::move(c_solver);
    _integrator = std::make_unique<SimpleIntegrator>(deltaT);
    _renderer = std::make_unique<Renderer>();
}

void Simulation::iteration() {
    const unsigned int SUBSTEPS = 8;
    const float subDeltaT = _deltaT / 8;
    _integrator->setDeltaT(subDeltaT);
    _constraint_solver->setDeltaT(subDeltaT);
    for (int i = 0; i < SUBSTEPS; i++) {
        // Update positions and velocities
        _integrator->integrate(*_state);

        // Solve all constraints
        _constraint_solver->solve_constraints();

        // Calculate the new velocities based on new positions
    }
};

void Simulation::start() {
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) {
            iteration();
        }
        // Render
        if (_renderer)
            _renderer->draw(*_state);
    }

}
