#include <algorithm>
#include <iostream>
#include <memory.h>
#include <memory>

#include "ConstraintSolver.hpp"
#include "ParticleList.hpp"
#include "Renderer.hpp"
#include "SimulationState.hpp"
#include "particle.hpp"
#include "simulation.hpp"

int main(int argc, char *argv[]) {
    // Create state
    std::vector<Particle> particles;
    particles.push_back(Particle(vec2(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/2.0f), vec2(20, 0)));
    particles.push_back(Particle(vec2(3*SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/2.0f), vec2(-50, 0)));

    auto pList = std::make_unique<ParticleList>(particles);
    std::vector<std::unique_ptr<Constraint>> constraints = make_particle_particle_contact(*pList);
    auto c_solver = std::make_unique<ConstraintSolver>(constraints, 0.1f);
    std::unique_ptr<SimulationState> state = std::move(pList);

    // Create simulation
    Simulation simulation = Simulation(state, c_solver);
    simulation.start();

    return 0;
}
