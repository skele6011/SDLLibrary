#include "Window.hpp"

// --- Constructor ---
Window::Window(const char* title, int width, int height) {
    // Setup window struct
    this->window_ = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    // Error checking: Window pointer is null
    if (!this->window_) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    // Set up renderer struct
    this->renderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED);
    // Error checking: Renderer pointer is null
    if (!this->renderer_) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}
// --- end: Constructor ---

// --- First Frame ---
void Window::beginFrame(Uint8 r, Uint8 g , Uint8 b, Uint8 a) { // Default values as black
    SDL_SetRenderDrawColor(this->renderer_, r, g, b, a);
    SDL_RenderClear(this->renderer_); // Fill screen with the color set
}
// --- end: First Frame ---

// --- Draw a pixel ---
void Window::drawPoint(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(this->renderer_, x, y);
}
// --- end: Draw a pixel ---

// --- Draw a line ---
void Window::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(this->renderer_, x1, y1, x2, y2);
}
// --- end: Draw a line ---

// --- Draw a rectangle (outline) --- 
void Window::drawRect(SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(this->renderer_, &rect);
}
// --- end: Draw a rectangle (outline) --- 

// --- Draw a rectangle (filled) --- 
void Window::drawFilledRect(SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(this->renderer_, &rect);
}
// --- end: Draw a rectangle (filled) ---

// --- Draw a triangle (outline) --- 
void Window::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color) { // Takes in 3 points & a color
    // Draw a line connecting each point
    this->drawLine(x1, y1, x2, y2, color); 
    this->drawLine(x2, y2, x3, y3, color);
    this->drawLine(x3, y3, x1, y1, color);
}
// --- end: Draw a triangle (outline) --- 

// --- Draw a triangle (filled) ---
// Manual triangle. Uses interpolation.
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
// --- end: Draw a triangle (filled) ---

// --- Draw a circle (outline) ---
void Window::drawCircle(int cx, int cy, int radius, SDL_Color color) {
    // Start at the rightmost point of the circle and move counterclockwise
    int x = 0;
    int y = -radius;

    // Decision parameter for the Midpoint Circle Algorithm
    int p = -radius;

    // Iterate until x crosses the 45-degree line (x == -y)
    while (x < -y) {

        // If the midpoint is outside the circle, move diagonally (down-right)
        if (p > 0) {
            y++;
            p += 2 * (x + y) + 1;
        }
        // If the midpoint is inside the circle, move horizontally (right)
        else {
            p += 2 * x + 1;
        }

        // Draw all 8 symmetrical points of the circle
        this->drawPoint(cx + x, cy + y, color); // right side
        this->drawPoint(cx - x, cy + y, color); // left side
        this->drawPoint(cx + x, cy - y, color); // right side (mirrored vertically)
        this->drawPoint(cx - x, cy - y, color); // left side (mirrored vertically)

        this->drawPoint(cx + y, cy + x, color); // top
        this->drawPoint(cx - y, cy + x, color); // top (mirrored horizontally)
        this->drawPoint(cx + y, cy - x, color); // bottom
        this->drawPoint(cx - y, cy - x, color); // bottom (mirrored horizontally)

        // Move to the next x-coordinate
        x++;
    }
}
// --- end: Draw a circle (outline) ---

// --- Ending frame ---
void Window::endFrame() {
    SDL_RenderPresent(this->renderer_); // Presents everything added to the renderer.
}
// --- end: Ending frame ---

// --- Destructor ---
Window::~Window() {
    // If pointers were valid, then destroy them.
    if (this->renderer_) { SDL_DestroyRenderer(this->renderer_); }
    if (this->window_) { SDL_DestroyWindow(this->window_); }
}
// --- end: Destructor ---
