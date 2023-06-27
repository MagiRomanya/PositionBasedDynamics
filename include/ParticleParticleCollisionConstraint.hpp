#ifndef PARTICLEPARTICLECOLLISIONCONSTRAINT_H_
#define PARTICLEPARTICLECOLLISIONCONSTRAINT_H_

#include "constraint.hpp"
#include "particle.hpp"
#include <eigen3/Eigen/src/Core/Matrix.h>

class ParticleParticleCollisionConstraint : public Constraint {
    public:
        ParticleParticleCollisionConstraint(Particle &p1, Particle &p2);

        unsigned int getDoF() const override;

        float evaluateConstraint() const override;

        Eigen::VectorXf evaluateJacobian() override;

        Eigen::MatrixXf getInvMass() override;

        void updateSystem(const Eigen::VectorXf& deltax) override;

    private:
        const unsigned int _nDoF = 4;
        Particle &_p1;
        Particle &_p2;

        Eigen::VectorXf _jacobian;
        Eigen::MatrixXf _inv_mass;
};

#endif // PARTICLEPARTICLECOLLISIONCONSTRAINT_H_
