#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "eigen3/Eigen/Core"
#include <eigen3/Eigen/src/Core/Matrix.h>

#include "SimulationState.hpp"

class Integrator {
    public:
        virtual void integrate(SimulationState& state) = 0;

    protected:
        float _deltaT;
        float _gravity = 9.8;
};

#endif // INTEGRATOR_H_
