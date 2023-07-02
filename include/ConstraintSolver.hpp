#ifndef CONSTRAINTSOLVER_H_
#define CONSTRAINTSOLVER_H_

#include <vector>
#include <memory>
#include "constraint.hpp"

class ConstraintSolver {
    public:
        ConstraintSolver(std::vector<std::unique_ptr<Constraint>>& constraints, float DeltaT);

        void solve_constraints();

        void solve(Constraint& constraint);

        inline void setDeltaT(float DeltaT) {_deltaT = DeltaT; }

    private:
        float _deltaT;

        std::vector<std::unique_ptr<Constraint>> _constraints;
};

#endif // CONSTRAINTSOLVER_H_
