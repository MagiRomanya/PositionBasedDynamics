#ifndef PARTICLELIST_H_
#define PARTICLELIST_H_

#include "SimulationState.hpp"
#include "particle.hpp"
#include <memory>
#include <vector>
#include <constraint.hpp>

class ParticleList : public SimulationState {
    public:
        ParticleList(std::vector<std::unique_ptr<Particle>>& particles);

        Eigen::VectorXf getPositions() override;

        Eigen::VectorXf getVelocities() override;

        void setPositions(const Eigen::VectorXf& pos) override;

        void setVelocities(const Eigen::VectorXf& vel) override;

        Eigen::SparseMatrix<float> getMass() override;

        Eigen::SparseMatrix<float> getInvMass() override;

        void updateVelocities(float DeltaT) override;

        unsigned int getDoF() const override;

        void render() const override;

        inline std::vector<std::unique_ptr<Particle>>& getParticles() { return _particles; }

    private:
        std::vector<std::unique_ptr<Particle>> _particles;

};

std::vector<std::unique_ptr<Constraint>> make_particle_particle_contact(ParticleList& pList);

#endif // PARTICLELIST_H_
