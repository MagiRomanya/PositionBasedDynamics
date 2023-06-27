#include "ParticleParticleCollisionConstraint.hpp"
#include "vec2.hpp"

ParticleParticleCollisionConstraint::ParticleParticleCollisionConstraint(Particle &p1, Particle &p2)
    : _p1(p1), _p2(p2)
{
    _jacobian.resize(_nDoF);
    _inv_mass = Eigen::MatrixXf::Zero(_nDoF, _nDoF);

    _inv_mass(0,0) = _p1.getMass();
    _inv_mass(1,1) = _p1.getMass();
    _inv_mass(2,2) = _p2.getMass();
    _inv_mass(3,3) = _p2.getMass();
}


unsigned int ParticleParticleCollisionConstraint::getDoF() const { return _nDoF; }

float ParticleParticleCollisionConstraint::evaluateConstraint() const {
    const float dist0 = _p1.getRadius() + _p2.getRadius();

    const vec2& pos1 = _p1.getPosition();
    const vec2& pos2 = _p2.getPosition();
    const float dist2 = distance2(pos1, pos2);

    return dist2 - dist0*dist0;
}

Eigen::VectorXf ParticleParticleCollisionConstraint::evaluateJacobian() {
    const vec2& pos1 = _p1.getPosition();
    const vec2& pos2 = _p2.getPosition();

    // 1st particle
    vec2 j1 = 2.0f * (pos1 - pos2);
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
    _p1.setPosition( _p1.getPosition() + vec2(deltax[0], deltax[1]) );
    _p2.setPosition( _p2.getPosition() + vec2(deltax[2], deltax[4]) );
}

Eigen::MatrixXf ParticleParticleCollisionConstraint::getInvMass() {
    return _inv_mass;
}
