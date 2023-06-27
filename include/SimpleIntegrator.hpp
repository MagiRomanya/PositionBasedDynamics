#ifndef SIMPLEINTEGRATOR_H_
#define SIMPLEINTEGRATOR_H_

#include "integrator.hpp"

class SimpleIntegrator : public Integrator {
    public:
        SimpleIntegrator(float deltaT) { _deltaT = deltaT; }
        void integrate(SimulationState& state) override;

    private:
};

#endif // SIMPLEINTEGRATOR_H_
