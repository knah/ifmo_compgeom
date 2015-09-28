#include <SDL.h>
#include "SDLVisualizer.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Visualizer Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    SDLVisualizer vis(window);
    vis.drawPoint(Point2D(10, 10), {255, 0, 255, 0});
    vis.drawLine(Point2D(20, 20), Point2D(30, 100), {0, 255, 255, 0});
    vis.runLoop();
    SDL_Quit();
    return 0;
}