#include "CollisionAcceleration.hpp"
#include "CollisionGrid.hpp"
#include "ParticleParticleCollisionConstraint.hpp"
#include "Renderer.hpp"
#include "particle.hpp"
#include <memory>
#include <vector>



CollisionAcceleration::CollisionAcceleration(ParticleList& pList)
    : _grid(CollisionGrid(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH / PARTICLE_DIAMETER, SCREEN_HEIGHT / PARTICLE_DIAMETER)),
      _pList(pList)
{}

void CollisionAcceleration::handleCollisions(ConstraintSolver& solver) {
    // First populate the grid
    populateGrid();

    // Avoid left and right columns
    for (int x = 1; x < _grid.getDimX(); x++) {
        for (int y = 1; y < _grid.getDimY(); y++) {
            CollisionCell current_cell = _grid.get(x, y);
            if (current_cell.particles.size() == 0) continue;
            // Iterate over neighbouring cells
            for (int xx=x-1; xx <= x+1; xx++) {
                for (int yy=y-1; yy <= y+1; yy++) {
                    CollisionCell other_cell = _grid.get(xx, yy);
                    if (other_cell.particles.size() == 0) continue;
                    std::cout << "This is me" << std::endl;
                    std::cout << vec2(x, y) << " "<< current_cell.particles.size() << std::endl;
                    std::cout << vec2(xx, yy)<< " "<< other_cell.particles.size() << std::endl;
                    handleCellCellsCollisions(solver, current_cell, other_cell);
                }
            }
        }
    }
}


void CollisionAcceleration::handleCellCellsCollisions(ConstraintSolver& solver, CollisionCell &c1, CollisionCell &c2) {
    for (int i = 0; i < c1.particles.size(); i++) {
        for (int j = 0; j < c2.particles.size(); j++) {
            Particle* p1 = c1.particles[i];
            Particle* p2 = c1.particles[j];
            if (p1 == p2) continue;
            if (p1->collidesWith(*p2)) {
                auto c = ParticleParticleCollisionConstraint(*p1, *p2);
                solver.solve(c);
            }
        }
    }
}

void CollisionAcceleration::populateGrid() {
    _grid.clear();
    std::vector<std::unique_ptr<Particle>>& particles = _pList.getParticles();
    for (int i = 0; i < particles.size(); i++) {
        _grid.set(particles[i].get());
    }
}
