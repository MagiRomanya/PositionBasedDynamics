#include "ParticleParticleCollisionConstraint.hpp"
#include "vec2.hpp"
#include <eigen3/Eigen/src/Core/Matrix.h>

ParticleParticleCollisionConstraint::ParticleParticleCollisionConstraint(Particle &p1, Particle &p2)
    : _p1(p1), _p2(p2)
{
    _jacobian.resize(_nDoF);
    _inv_mass = Eigen::MatrixXf::Zero(_nDoF, _nDoF);

    _inv_mass(0,0) = 1.0f / _p1.getMass();
    _inv_mass(1,1) = 1.0f / _p1.getMass();
    _inv_mass(2,2) = 1.0f / _p2.getMass();
    _inv_mass(3,3) = 1.0f / _p2.getMass();
}


unsigned int ParticleParticleCollisionConstraint::getDoF() const { return _nDoF; }

float ParticleParticleCollisionConstraint::evaluateConstraint() const {
    const float dist0 = _p1.getRadius() + _p2.getRadius();

    const vec2& pos1 = _p1.getPosition();
    const vec2& pos2 = _p2.getPosition();
    const float dist = distance(pos1, pos2);
    float c = dist - dist0;
    c = (c <= 0) ? c : 0;
    // Only apply the constraint if c < 0 (the particles are colliding)
    return c;
}

Eigen::VectorXf ParticleParticleCollisionConstraint::evaluateJacobian() {
    const float dist0 = _p1.getRadius() + _p2.getRadius();

    vec2 pos1 = _p1.getPosition();
    const vec2& pos2 = _p2.getPosition();
    float dist = distance(pos1, pos2);
    float c = dist - dist0;

    if (c >= 0) return Eigen::VectorXf::Zero(_nDoF);
    // If the particles are exactly at the same point we don't want the simulation to break
    const float EPSILON = 1e-5;
    vec2 v_eps = vec2(EPSILON, 0.0f);
    if (dist <1e-6) {
        dist = EPSILON;
        pos1 +=v_eps;
    }

    // 1st particle
    vec2 j1 = (pos1 - pos2) / dist;
    _jacobian[0] = j1.x();
    _jacobian[1] = j1.y();

    // 2nd particle
    vec2 j2 = -j1;
    _jacobian[2] = j2.x();
    _jacobian[3] = j2.y();

    return _jacobian;
}

void ParticleParticleCollisionConstraint::updateSystem(const Eigen::VectorXf& deltax) {
    if (deltax.size() != _nDoF){
        std::cerr << "ERROR::PARTICLE_PARTICLE_COLLISION_CONSTRAINT::UPDATE_SYSTEM: deltax does not match dimensionality " << deltax.size() << std::endl;
        exit(-1);
    }
    _p1.setPosition( _p1.getPosition() + vec2(deltax[0], deltax[1]));
    _p2.setPosition( _p2.getPosition() + vec2(deltax[2], deltax[3]));
}

Eigen::MatrixXf ParticleParticleCollisionConstraint::getInvMass() {
    return _inv_mass;
}
