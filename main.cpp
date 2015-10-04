#include <SDL.h>
#include "SDLVisualizer.hpp"
#include "NaiveSegmentLocalization.hpp"
#include <fstream>
#include <vector>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Visualizer Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    SDLVisualizer vis(window);
    vis.drawPoint(Point2D(400, 300), {255,255,255,255});
   
    
    std::ifstream fin("segments.txt");
    std::vector<Segment2D> segments;
    while(!fin.eof()) {
        double x1, y1, x2, y2;
        fin >> x1 >> y1 >> x2 >> y2;
        if(fin.eof())
            break;
        segments.push_back(Segment2D(Point2D(x1, y1), Point2D(x2, y2)));
        vis.drawLine(segments.back().first, segments.back().second, {255,255,255,255});
    }
    
    NaiveSegmentLocalization segmentLoc(segments);
    
    vis.setClickCallback([&segmentLoc, &vis, last1 = 0, last2 = 0] (double x, double y) mutable {
       vis.replacePoint(0, Point2D(x, y));
       auto hilit = segmentLoc.performQuery(Point2D(x, y));
       vis.updateColor(last1, {255,255,255,255});
       vis.updateColor(last2, {255,255,255,255});
       
       last1 = hilit.first + 1;
       last2 = hilit.second + 1;
       if(last1 > 0)
           vis.updateColor(last1, {255,0,255,255});
       if(last2 > 0)
           vis.updateColor(last2, {255,255,0,255});
    });
    
    vis.runLoop();
    SDL_Quit();
    return 0;
}
