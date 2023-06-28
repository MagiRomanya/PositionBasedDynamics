#ifndef RENDERER_H_
#define RENDERER_H_

#include <raylib.h>
#include "SimulationState.hpp"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1000

class Renderer {
    public:
        Renderer(int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT);

        ~Renderer();

        void draw(const SimulationState& state);

    private:
        void Initialize();

        int _screenWidth, _screenHeight;
};

#endif // RENDERER_H_
