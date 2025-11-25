#include "Window.hpp"

Window::Window(const char* title, int width, int height) {
    window_ = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (!window_) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

void Window::beginFrame() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Window::drawPoint(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer_, x, y);
}

void Window::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
}

void Window::drawRect(SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer_, &rect);
}

void Window::drawFilledRect(SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer_, &rect);
}

void Window::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color) {
    this->drawLine(x1, y1, x2, y2, color); 
    this->drawLine(x2, y2, x3, y3, color);
    this->drawLine(x3, y3, x1, y1, color);
}

void Window::drawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color) {
    // Sort vertices by y-coordinate (y1 <= y2 <= y3)
    if (y1 > y2) { std::swap(x1,x2); std::swap(y1,y2); }
    if (y2 > y3) { std::swap(x2,x3); std::swap(y2,y3); }
    if (y1 > y2) { std::swap(x1,x2); std::swap(y1,y2); }

    // Lambda function to draw every pixel from startX till endX at Y
    auto drawLineH = [&](int sx, int ex, int y){
        if (sx > ex) { std::swap(sx, ex); } // Make sure the start is on the left of the end
        for (int x = sx; x <= ex; x++) {
            drawPoint(x, y, color);
        }
    };

    // Interpolation to figure out the x-axis of an edge at a certain y
    auto interp = [](float a, float b, float t){ return a + (b - a) * t; };

    if (y2 == y3) { // Flat-bottom triangle
        for (int y = y1; y <= y3; y++){
            if (y3 == y1) {
                throw std::runtime_error("Triangle with no height");
            }
            float t1 = (float)(y - y1) / (y3 - y1);
            float sx = interp(x1, x3, t1);
            float ex = interp(x1, x2, t1);
            drawLineH(int(sx), int(ex), y);
        }
    } else if (y1 == y2) { // Flat-top triangle
        for (int y = y1; y <= y3; y++){
            if (y3 == y1) {
                throw std::runtime_error("Triangle with no height");
            }
            float t1 = (float)(y - y1) / (y3 - y1);
            float sx = interp(x1, x3, t1);
            float ex = interp(x2, x3, t1);
            drawLineH(int(sx), int(ex), y);
        }
    } else { // General triangle: split into top-flat and bottom-flat
        int x4 = x1 + (float)(y2 - y1)/(y3 - y1) * (x3 - x1); // New vertex at y2
        int y4 = y2;

        drawFilledTriangle(x1, y1, x2, y2, x4, y4, color); // Top flat
        drawFilledTriangle(x2, y2, x4, y4, x3, y3, color); // Bottom flat
    }
}

void Window::drawCircle(int cx, int cy, int radius, SDL_Color color) {
    int x = 0;
    int y = -radius;
    int p = -radius;

    while (x < -y) {
        if (p > 0) {
            y++;
            p += 2*(x+y) + 1;
        } else {
            p += 2*x + 1;
        }

        this->drawPoint(cx + x, cy + y, color); // right edge of circle
        this->drawPoint(cx - x, cy + y, color); // left edge
        this->drawPoint(cx + x, cy - y, color); // right edge, mirrored vertically
        this->drawPoint(cx - x, cy - y, color); // left edge, mirrored vertically
        this->drawPoint(cx + y, cy + x, color); // top point
        this->drawPoint(cx - y, cy + x, color); // mirrored top
        this->drawPoint(cx + y, cy - x, color); // bottom
        this->drawPoint(cx - y, cy - x, color); // mirrored bottom

        x++;
    }
}

void Window::endFrame() {
    SDL_RenderPresent(renderer_);
}

Window::~Window() {
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
}
