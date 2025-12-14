/******************************************************************************
 * Collision.hpp/cpp v1.0
 * Simple SDL collision checker. Includes the following:
    * Custom-made perfect circle to rectangle collisions
    * Custom-made perfect circle to circle collisions
 ******************************************************************************/

#pragma once
#include <SDL2/SDL.h>
#include <algorithm>


class Collision { 
public:
    static bool circleRectCollision(int cx, int cy, int radius, SDL_Rect rect);
    static bool circleCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2);
};