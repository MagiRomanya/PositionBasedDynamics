#include "particle.hpp"
#include "vec2.hpp"

Particle::Particle(vec2 x0, vec2 v0, float mass, float radius) : position(x0), velocity(v0) {
    this->mass = mass;
    this->radius = radius;
}

bool Particle::collidesWith(const Particle& p) {
    return ( distance2(p.getPosition(), this->getPosition()) - this->getRadius() - p.getRadius() ) < 0.0f;
}
