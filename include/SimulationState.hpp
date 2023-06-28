#ifndef SIMULATIONSTATE_H_
#define SIMULATIONSTATE_H_

#include <vector>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/SparseCore"

class SimulationState {
    public:
        virtual Eigen::VectorXf getPositions() = 0;

        virtual Eigen::VectorXf getVelocities() = 0;

        virtual void setPositions(const Eigen::VectorXf& pos) = 0;

        virtual void setVelocities(const Eigen::VectorXf& vel) = 0;

        virtual Eigen::SparseMatrix<float> getMass() = 0;

        virtual Eigen::SparseMatrix<float> getInvMass() = 0;

        virtual unsigned int getDoF() const = 0;

        virtual void updateVelocities(float DeltaT) = 0;

        virtual void render() const = 0;

    protected:

        Eigen::SparseMatrix<float> _mass;
        Eigen::SparseMatrix<float> _inv_mass;
        Eigen::VectorXf _positions;
        Eigen::VectorXf _previous_positions;
        Eigen::VectorXf _velocities;
        std::vector<Eigen::Triplet<float>> _mass_triplets;
        std::vector<Eigen::Triplet<float>> _inv_mass_triplets;
};

#endif // SIMULATIONSTATE_H_
