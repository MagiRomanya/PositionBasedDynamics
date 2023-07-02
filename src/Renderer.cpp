#include "Renderer.hpp"
#include <raylib.h>

Renderer::Renderer(int width, int height) {
    _screenWidth = width;
    _screenHeight = height;
    Initialize();
}
Renderer::~Renderer() {
    CloseWindow();        // Close window and OpenGL context
}

void Renderer::Initialize() {

    InitWindow(_screenWidth, _screenHeight, "Simulation");
    SetTargetFPS(60);
};


void Renderer::draw(const SimulationState& state) {
    ClearBackground(DARKGRAY);
    state.render();
}
