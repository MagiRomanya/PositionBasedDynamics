#include <iostream>
#include <memory.h>
#include <memory>

#include "ParticleList.hpp"
#include "SimulationState.hpp"
#include "particle.hpp"
#include "simulation.hpp"

int main(int argc, char *argv[]) {
    // Create state
    std::vector<Particle> particles;
    particles.push_back(Particle(vec2(250,250), vec2(0,0)));
    std::unique_ptr<SimulationState> state = std::make_unique<ParticleList>(particles);

    // Create simulation
    Simulation simulation = Simulation(state);
    simulation.start();

    return 0;
}
