#ifndef SDLVISUALIZER_H
#define SDLVISUALIZER_H

#include "IVisualizer.hpp"
#include <vector>
#include <tuple>
#include <functional>

struct SDL_Window;
struct SDL_Renderer;

namespace {
    typedef std::function<void(double,double)> ClickCallback;
};

class SDLVisualizer : public IVisualizer {
    std::vector<std::tuple<Color, bool, Point2D, Point2D>> segments;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool dirty, dragging;
    int windowSizeX, windowSizeY;
    unsigned int mouseDownTicks;
    float offsetX, offsetY;
    float zoomFactor;
    ClickCallback clickCallback;
public:
    SDLVisualizer(SDL_Window *window);
    virtual ~SDLVisualizer();
    virtual int drawLine(Point2D start, Point2D end, Color color);
    virtual int drawPoint(Point2D point, Color color);
    virtual void replacePoint(int id, Point2D point);
    virtual void updateColor(int lineId, Color newColor);
    virtual void clear();
    
    void runLoop();
    void setClickCallback(const ClickCallback &cb) { clickCallback = cb; }
};

#endif