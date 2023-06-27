#include "ConstraintSolver.hpp"

ConstraintSolver::ConstraintSolver(std::vector<std::unique_ptr<Constraint>>& constraints, float DeltaT)
    : _deltaT(DeltaT)
{
    _constraints = std::move(constraints);
}

void ConstraintSolver::solve(Constraint& constraint) {
    const float c = constraint.evaluateConstraint();
    Eigen::VectorXf jacobian = constraint.evaluateJacobian();

    Eigen::MatrixXf inv_mass = constraint.getInvMass();

    const float denominator = jacobian.dot(inv_mass * jacobian) + constraint.getComplience() / _deltaT;
    const float lambda = - c / denominator;

    Eigen::VectorXf deltax = lambda * inv_mass * jacobian;
    constraint.updateSystem(deltax);
}

void ConstraintSolver::solve_constraints() {
    for (int i = 0; i < _constraints.size(); i++) {
        solve(*_constraints[i]);
    }
}
