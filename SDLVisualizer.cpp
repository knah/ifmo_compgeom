#include "SDLVisualizer.hpp"
#include <SDL.h>

using namespace std;

SDLVisualizer::SDLVisualizer(SDL_Window *window) : window(window) {
    dirty = dragging = false;
    zoomFactor = 1.0f;
    SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);
    
    renderer = SDL_CreateRenderer(window, -1, 0);
}

SDLVisualizer::~SDLVisualizer() {
    if(renderer)
        SDL_DestroyRenderer(renderer);
}

int SDLVisualizer::drawLine(Point2D start, Point2D end, Color color) {
    segments.push_back(make_tuple(color, false, start, end));
    dirty = true;
    return segments.size() - 1;
}

int SDLVisualizer::drawPoint(Point2D point, Color color) {
    segments.push_back(make_tuple(color, true, point, point));
    dirty = true;
    return segments.size() - 1;
}

void SDLVisualizer::updateColor(int lineId, Color newColor) {
    get<0>(segments[lineId]) = newColor;
    dirty = true;
}

void SDLVisualizer::clear() {
    segments.clear();
    dirty = true;
}

void SDLVisualizer::runLoop() {
    SDL_Event evt;
    //std::cerr << SDL_GetError();
    while(SDL_WaitEvent(&evt))
    {
        switch(evt.type)
        {
        case SDL_KEYDOWN:
            goto out;
            break;
        case SDL_MOUSEMOTION:
            if(dragging) {
                offsetX -= evt.motion.xrel / zoomFactor;
                offsetY -= evt.motion.yrel / zoomFactor;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            dragging = true;
            break;
        case SDL_MOUSEBUTTONUP:
            dragging = false;
            break;
        case SDL_MOUSEWHEEL:
            zoomFactor *= pow(1.1f, evt.wheel.y);
            break;
        case SDL_KEYUP:
            break;
        case SDL_WINDOWEVENT:
            dirty = true;
            switch(evt.window.event)
            {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    if(evt.window.windowID == SDL_GetWindowID(window)) {
                        windowSizeX = evt.window.data1;
                        windowSizeY = evt.window.data2;
                    }
                    break;
            }
            break;
        case SDL_QUIT:
            goto out;
            break;
        }
        if(dirty) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            for(auto seg : segments) {
                auto col = get<0>(seg);
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 255);
                if(get<1>(seg)) {
                    auto pt = get<2>(seg);
                    SDL_RenderDrawPoint(renderer, (pt.x - offsetX) * zoomFactor + windowSizeX/2, (pt.y - offsetY) * zoomFactor + windowSizeY/2);
                } else {
                    auto p1 = get<2>(seg);
                    auto p2 = get<3>(seg);
                    SDL_RenderDrawLine(renderer, (p1.x - offsetX) * zoomFactor + windowSizeX/2, (p1.y - offsetY) * zoomFactor + windowSizeY/2,
                                                 (p2.x - offsetX) * zoomFactor + windowSizeX/2, (p2.y - offsetY) * zoomFactor + windowSizeY/2);
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
    out:;
}
