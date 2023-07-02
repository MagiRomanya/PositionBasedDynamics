#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <memory> // unique ptr

#include "CollisionAcceleration.hpp"
#include "ConstraintSolver.hpp"
#include "SimulationState.hpp"
#include "integrator.hpp"
#include "Renderer.hpp"

class Simulation {
    public:
        Simulation(std::unique_ptr<SimulationState>& state,
                   std::unique_ptr<ConstraintSolver>& c_solver,
                   std::unique_ptr<CollisionAcceleration>& accelerator,
                   float deltaT=0.1f);

        void start();

    private:
        void iteration();

        float _deltaT;

        std::unique_ptr<SimulationState> _state;
        std::unique_ptr<Integrator> _integrator;
        std::unique_ptr<Renderer> _renderer;
        std::unique_ptr<ConstraintSolver> _constraint_solver;
        std::unique_ptr<CollisionAcceleration> _collision_acceleration;
};

#endif // SIMULATION_H_
