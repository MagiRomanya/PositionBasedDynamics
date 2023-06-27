#ifndef CONSTRAINTMANAGER_H_
#define CONSTRAINTMANAGER_H_

#include <eigen3/Eigen/Core>
#include <vector>

#include "SimulationState.hpp"

class ConstraintManager {
    public:
        ConstraintManager();

        unsigned int getDoF();

    private:
        Eigen::VectorXf evaluateConstraints(const SimulationState& state);

        Eigen::SparseMatrix<float> evaluateJacobian(const SimulationState& state);

        unsigned int _nDoF;

        Eigen::VectorXf _constraint_vector;
        Eigen::SparseMatrix<float> _constraint_jacobian;
        std::vector<Eigen::Triplet<float>> _jacobian_triplets;
};

#endif // CONSTRAINTMANAGER_H_
