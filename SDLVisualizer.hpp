#include "IVisualizer.hpp"
#include <vector>
#include <tuple>

struct SDL_Window;
struct SDL_Renderer;

class SDLVisualizer : public IVisualizer {
    std::vector<std::tuple<Color, bool, Point2D, Point2D>> segments;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool dirty, dragging;
    int windowSizeX, windowSizeY;
    float offsetX, offsetY;
    float zoomFactor;
public:
    SDLVisualizer(SDL_Window *window);
    virtual ~SDLVisualizer();
    virtual int drawLine(Point2D start, Point2D end, Color color);
    virtual int drawPoint(Point2D point, Color color);
    virtual void updateColor(int lineId, Color newColor);
    virtual void clear();
    
    void runLoop();
};
