#include "CollisionGrid.hpp"

CollisionGrid::CollisionGrid(float width, float height, unsigned int dimX, unsigned int dimY) {
    _width = width;
    _height = height;
    _dimX = dimX;
    _dimY = dimY;
    clear();
}

void CollisionGrid::clear() {
    // Resets the grid to an empty one (with right dimensions)
    _grid.clear();
    _grid.resize(_dimX);

    for (int i = 0; i < _dimX; i++) {
        _grid[i].reserve(_dimY);
        for (int j = 0; j < _dimY; j++) {
            _grid[i].push_back(CollisionCell(i, j));
        }
    }
}

CollisionCell CollisionGrid::get(int i, int j) const {
    if ((i >= _dimX or j >= _dimY) or (i < 0 or j < 0)) {
        // Object outside the grid -> padding
        return CollisionCell(i, j);
    }
    return _grid[i][j];
}

void CollisionGrid::set(Particle* p) {
    const vec2& pos = p->getPosition();
    const unsigned int i = _dimX * pos.x() / _width;
    const unsigned int j = _dimY * pos.y() / _height;

    if (i < _dimX && j < _dimY) {
        _grid[i][j].particles.push_back(p);
        std::cout << i << ", " << j << std::endl;
    }
}
