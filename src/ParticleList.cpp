#include "ParticleList.hpp"
#include <memory>
#include <vector>
#include "constraint.hpp"
#include "raylib.h"
#include "ParticleParticleCollisionConstraint.hpp"

ParticleList::ParticleList(std::vector<Particle> particles) {
    _particles = particles;
    _previous_positions = getPositions();
}

unsigned int ParticleList::getDoF() const {
    // 2 dimensional particles
    return _particles.size() * 2;
}

Eigen::VectorXf ParticleList::getPositions() {
    _positions.resize(getDoF());
    for (int i = 0; i < _particles.size(); i++) {
        const vec2& pos = _particles[i].getPosition();
        _positions[2*i] = pos.x();
        _positions[2*i+1] = pos.y();
    }
    return _positions;
}

Eigen::VectorXf ParticleList::getVelocities() {
    _velocities.resize(getDoF());
    for (int i = 0; i < _particles.size(); i++) {
        const vec2& vel = _particles[i].getVelocity();
        _velocities[2*i] = vel.x();
        _velocities[2*i+1] = vel.y();
    }

    return _velocities;
}

void ParticleList::setPositions(const Eigen::VectorXf& pos) {
    _positions = pos;
    for (int i = 0; i < _particles.size(); i++) {
        _particles[i].setPosition(vec2(_positions[2*i], _positions[2*i+1]));
    }
}

void ParticleList::setVelocities(const Eigen::VectorXf& vel) {
    _velocities = vel;
    for (int i = 0; i < _particles.size(); i++) {
        _particles[i].setVelocity(vec2(_velocities[2*i], _velocities[2*i+1]));
    }
}

Eigen::SparseMatrix<float> ParticleList::getMass() {
    _mass.resize(getDoF(), getDoF());
    _mass_triplets.clear();
    for(int i = 0; i < getDoF(); i+=2) {
        _mass_triplets.push_back(Eigen::Triplet<float>(i,i, _particles[i].getMass()));
        _mass_triplets.push_back(Eigen::Triplet<float>(i+1, i+1, _particles[i].getMass()));
    }

    _mass.setFromTriplets(_mass_triplets.begin(), _mass_triplets.end());
    return _mass;
}

void ParticleList::render() const {
    BeginDrawing();
    for (int i = 0; i < _particles.size(); i++) {
        const vec2& pos = _particles[i].getPosition();
        const float radius = _particles[i].getRadius();
        DrawCircle(pos.x(), pos.y(), radius, PURPLE);
    }
    EndDrawing();
}

Eigen::SparseMatrix<float> ParticleList::getInvMass() {
    _inv_mass.resize(getDoF(), getDoF());
    _inv_mass_triplets.clear();
    for(int i = 0; i < getDoF(); i+=2) {
        _inv_mass_triplets.push_back(Eigen::Triplet<float>(i,i, 1.0f / _particles[i].getMass()));
        _inv_mass_triplets.push_back(Eigen::Triplet<float>(i+1, i+1, 1.0f / _particles[i].getMass()));
    }

    _inv_mass.setFromTriplets(_inv_mass_triplets.begin(), _inv_mass_triplets.end());
    return _inv_mass;
}

std::vector<std::unique_ptr<Constraint>> make_particle_particle_contact(ParticleList& pList) {
    std::vector<Particle>& particles = pList.getParticles();
    std::vector<std::unique_ptr<Constraint>> constraints;
    for (int i = 0; i < particles.size(); i++) {
        for (int j = i+1; j < particles.size(); j++) {
            Particle& p1 = particles[i];
            Particle& p2 = particles[j];
            constraints.push_back(std::make_unique<ParticleParticleCollisionConstraint>(p1, p2));

        }
    }
    return constraints;
}

void ParticleList::updateVelocities(float DeltaT) {
    _velocities = (_positions - _previous_positions) / DeltaT;
    _previous_positions = getPositions();
}
