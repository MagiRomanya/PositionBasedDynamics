#include "SimpleIntegrator.hpp"
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <eigen3/Eigen/src/SparseCore/SparseMatrix.h>
#include <iostream>

Eigen::VectorXf gravityVector(unsigned int dim) {
    Eigen::VectorXf vec = Eigen::VectorXf::Ones(dim);
    if (dim % 2 != 0){
        std::cerr << "ERROR::SIMPLE_INTEGRATOR::GRAVITY_VECTOR: dimensions not even: " << dim << std::endl;
        exit(-1);
    }
    for (int i = 0; i < dim; i+=2) {
        vec[i] = 0.0f;
    }
    return vec;
}

void SimpleIntegrator::integrate(SimulationState &state) {
    // Get state
    const unsigned int nDoF = state.getDoF();

    Eigen::VectorXf positions = state.getPositions();

    Eigen::VectorXf velocities = state.getVelocities();

    Eigen::SparseMatrix<float> mass = state.getMass();

    // Integration
    velocities += _gravity * _deltaT * mass * gravityVector(nDoF);
    positions += _deltaT * velocities;

    // Update state
    state.setPositions(positions);
    state.setVelocities(velocities);
}

