/******************************************************************************
 * Window.hpp/cpp v1.0
 * Simple SDL window and rendering wrapper. Includes the following:
 *   * Window and renderer creation/destruction
 *   * Frame begin/end handling
 *   * Basic primitive rendering:
 *       - Points
 *       - Lines
 *       - Rectangles (outlined and filled)
 *       - Triangles (outlined and filled)
 *       - Circles (outlined)
 *       - Dependency: SDL2 only. All drawings are manually done without SDL_gfx
 ******************************************************************************/

#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>

class Window {
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

public:
    Window(const char* title, int width, int height);
    ~Window();

    // Clears the screen and prepares the frame (default: black)
    void beginFrame(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);

    // --- Primitive drawing ---
    void drawPoint(int x, int y, SDL_Color color);
    void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);
    void drawRect(SDL_Rect rect, SDL_Color color);
    void drawFilledRect(SDL_Rect rect, SDL_Color color);
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
    void drawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
    void drawCircle(int cx, int cy, int radius, SDL_Color color);
    // --- end: Primitive drawing ---

    // Presents the rendered frame
    void endFrame();

    // --- Getters ---
    SDL_Renderer* renderer() const { return renderer_; }
    // --- end: Getters ---
};
