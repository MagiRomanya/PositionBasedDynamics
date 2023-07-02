#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include "vec2.hpp"
#include "particle.hpp"

struct CollisionCell {
    CollisionCell(int i, int j) : i(i), j(j) {}
    std::vector<Particle*> particles;
    const int i, j;
};

class CollisionGrid {
    public:
        CollisionGrid(float width, float height, unsigned int dimX, unsigned int dimY);

        CollisionCell get(int i, int j) const;

        void set(Particle* p);

        inline unsigned int getDimX() const { return _dimX; }

        inline unsigned int getDimY() const { return _dimY; }

        void clear();

    private:

        float _width, _height;                // physical dimensions of the grid
        unsigned int _dimX, _dimY;            // number of cells

        std::vector<std::vector<CollisionCell>> _grid;
};

#endif // GRID_H_
