#ifndef RENDERER_H_
#define RENDERER_H_

#include <raylib.h>
#include "SimulationState.hpp"

class Renderer {
    public:
        Renderer(int width=800, int height=450);

        ~Renderer();

        void draw(const SimulationState& state);

    private:
        void Initialize();

        int _screenWidth, _screenHeight;
};

#endif // RENDERER_H_
