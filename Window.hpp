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

    void beginFrame();

    void drawPoint(int x, int y, SDL_Color color);
    void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);
    void drawRect(SDL_Rect rect, SDL_Color color);
    void drawFilledRect(SDL_Rect rect, SDL_Color color);
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
    void drawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
    void drawCircle(int cx, int cy, int radius, SDL_Color color);


    void endFrame();

    SDL_Renderer* renderer() const { return renderer_; }
};
