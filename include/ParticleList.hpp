#ifndef PARTICLELIST_H_
#define PARTICLELIST_H_

#include "SimulationState.hpp"
#include "particle.hpp"
#include <vector>

class ParticleList : public SimulationState {
    public:
        ParticleList(std::vector<Particle> particles);

        Eigen::VectorXf getPositions() override;

        Eigen::VectorXf getVelocities() override;

        void setPositions(const Eigen::VectorXf& pos) override;

        void setVelocities(const Eigen::VectorXf& vel) override;

        Eigen::SparseMatrix<float> getMass() override;

        virtual Eigen::SparseMatrix<float> getInvMass() override;

        unsigned int getDoF() const override;

        void render() const override;

    private:
        std::vector<Particle> _particles;

};

#endif // PARTICLELIST_H_
