#include "simulation.hpp"
#include "SimpleIntegrator.hpp"
#include "SimulationState.hpp"
#include <memory>

Simulation::Simulation(std::unique_ptr<SimulationState> &state, float deltaT) {
    _state = std::move(state);
    _integrator = std::make_unique<SimpleIntegrator>(deltaT);
    _renderer = std::make_unique<Renderer>();
    _deltaT = deltaT;
}

void Simulation::iteration() {
    // Update positions and velocities
    _integrator->integrate(*_state);

    // Solve all constraints

    // Calculate the new velocities based on new positions

    // Render
    if (_renderer)
        _renderer->draw(*_state);
};

void Simulation::start() {
    while (!WindowShouldClose()) {
        iteration();
    }
}
