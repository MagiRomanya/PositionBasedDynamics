#include "ConstraintSolver.hpp"
#include <iostream>

ConstraintSolver::ConstraintSolver(std::vector<std::unique_ptr<Constraint>>& constraints, float DeltaT)
    : _deltaT(DeltaT)
{
    _constraints = std::move(constraints);
}

void ConstraintSolver::solve(Constraint& constraint) {
    const float c = constraint.evaluateConstraint();
    if (c == 0.0f) return;
    Eigen::VectorXf jacobian = constraint.evaluateJacobian();
    std::cout << "constraint " << c << std::endl;
    std::cout << "jacobian " << jacobian << std::endl;

    Eigen::MatrixXf inv_mass = constraint.getInvMass();

    const float denominator = jacobian.dot(inv_mass * jacobian) + constraint.getComplience() / _deltaT;

    std::cout << "denominator " << denominator << std::endl;
    const float lambda = - c / denominator;

    Eigen::VectorXf deltax = lambda * inv_mass * jacobian;
    std::cout << "deltax" << deltax << std::endl;
    constraint.updateSystem(deltax);
}

void ConstraintSolver::solve_constraints() {
    for (int i = 0; i < _constraints.size(); i++) {
        solve(*_constraints[i]);
    }
}
