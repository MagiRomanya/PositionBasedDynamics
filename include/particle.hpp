#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "vec2.hpp"

class Particle {
    public:
        Particle(vec2 x0, vec2 v0, float mass=1.0f, float radius=10.0f);

        inline vec2 getPosition() const { return position; };

        inline vec2 getVelocity() const { return velocity; };

        inline void setPosition(const vec2& p) { position = p; };

        inline void setVelocity(const vec2& v) { velocity = v; };

        inline float getMass() const {return mass; }

        inline float getRadius() const {return radius; }

    private:
        float radius;
        float mass;
        vec2 position;
        vec2 velocity;
};

#endif // PARTICLE_H_
