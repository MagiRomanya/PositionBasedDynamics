#ifndef WALLCONSTRAINT_H_
#define WALLCONSTRAINT_H_

#include "constraint.hpp"
#include "particle.hpp"
#include <eigen3/Eigen/Core>

class WallConstraint : public Constraint {
    public:
        WallConstraint(vec2 position, vec2 normal, Particle &p1);

        unsigned int getDoF() const override;

        float evaluateConstraint() const override;

        Eigen::VectorXf evaluateJacobian() override;

        Eigen::MatrixXf getInvMass() override;

        void updateSystem(const Eigen::VectorXf& deltax) override;

    private:
        float _nDoF = 2;
        vec2 _position, _normal;
        Particle& _particle;

        Eigen::VectorXf _jacobian;
        Eigen::MatrixXf _inv_mass;
};

#endif // WALLCONSTRAINT_H_
