#ifndef COLLISIONACCELERATION_H_
#define COLLISIONACCELERATION_H_

#include "CollisionGrid.hpp"
#include "ConstraintSolver.hpp"
#include "ParticleList.hpp"
#include <memory>
#include <vector>

class CollisionAcceleration {
    public:
        CollisionAcceleration(ParticleList& pList);

        void handleCollisions(ConstraintSolver& solver);

    private:
        void populateGrid();

        void handleCellCellsCollisions(ConstraintSolver& solver, CollisionCell &c1, CollisionCell &c2);

        CollisionGrid _grid;
        ParticleList& _pList;
};

#endif // COLLISIONACCELERATION_H_
