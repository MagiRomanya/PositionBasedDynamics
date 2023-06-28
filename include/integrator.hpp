#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "eigen3/Eigen/Core"
#include <eigen3/Eigen/src/Core/Matrix.h>

#include "SimulationState.hpp"

class Integrator {
    public:
        virtual void integrate(SimulationState& state) = 0;

        inline void setDeltaT(float DeltaT) { _deltaT = DeltaT; }

    protected:
        float _deltaT;
        float _gravity = 9.8f;
};

#endif // INTEGRATOR_H_
