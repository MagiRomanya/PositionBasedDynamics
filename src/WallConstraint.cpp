#include "WallConstraint.hpp"
#include "vec2.hpp"
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <iostream>


WallConstraint::WallConstraint(vec2 position, vec2 normal, Particle &p1)
    : _particle(p1), _position(position), _normal(normal)
{
    _jacobian.resize(_nDoF);
    _inv_mass = Eigen::MatrixXf::Zero(_nDoF, _nDoF);
    _inv_mass(0,0) = 1.0f / _particle.getMass();
    _inv_mass(1,1) = 1.0f / _particle.getMass();
}

unsigned int WallConstraint::getDoF() const {
    return _nDoF;
}

float WallConstraint::evaluateConstraint() const {
    const vec2& ppos = _particle.getPosition();
    float c = dot(ppos - _position, _normal) - _particle.getRadius();
    c = (c <= 0) ? c: 0;
    return c;
}

Eigen::VectorXf WallConstraint::evaluateJacobian() {
    const vec2& ppos = _particle.getPosition();
    float c = evaluateConstraint();
    if (c > 0) return Eigen::VectorXf::Zero(_nDoF);

    const vec2 jac = _normal;
    _jacobian[0] = jac.x();
    _jacobian[1] = jac.y();
    return _jacobian;
}

Eigen::MatrixXf WallConstraint::getInvMass() {
    return _inv_mass;
}

void WallConstraint::updateSystem(const Eigen::VectorXf& deltax) {
    if (deltax.size() != _nDoF) {
        std::cerr << "ERROR::WALL_CONSTRAINT::UPDATE_SYSTEM" << std::endl;
        exit(-1);
    }
    vec2 delta = vec2(deltax[0], deltax[1]);
    _particle.setPosition(_particle.getPosition() + delta);
}
