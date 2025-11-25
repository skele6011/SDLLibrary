#pragma once
#include <SDL2/SDL.h>
#include <algorithm>


class Collision { 
public:
    static bool circleRectCollision(int cx, int cy, int radius, SDL_Rect rect);
    static bool circleCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2);
};