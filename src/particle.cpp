#include "particle.hpp"

Particle::Particle(vec2 x0, vec2 v0, float mass, float radius) : position(x0), velocity(v0) {
    this->mass = mass;
    this->radius = radius;
}
