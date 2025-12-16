#include <SDL2/SDL.h>
#include "SDLLibrary.h"

#include <iostream>

int main() {
    // --- Initialize SDL, IMG, TTF ---
    SDLInitializer sdl(SDL_INIT_VIDEO, IMG_INIT_PNG);
    if (!sdl.sdlInitialized() || !sdl.imgInitialized() || !sdl.ttfInitialized()) {
        std::cerr << "Failed to initialize SDL or related subsystems." << std::endl;
        return -1;
    }

    // --- Create window ---
    Window window("SDL2 Demo App", 1600, 1200);
    SDL_Renderer* renderer = window.renderer();

    // --- Load font ---
    TTF_Font* font = sdl.openFont("ExampleSrc/simple_font.ttf", 24);
    if (!font) {
        return -1;
    }

    // --- Load texture ---
    Texture tex(renderer, "ExampleSrc/exampleMario.png"); 

    // --- Event manager ---
    EventManager em(true);

    // --- Demo objects ---
    SDL_Rect rect = {300, 200, 200, 150};
    int circleX = 400, circleY = 300, circleR = 50;
    bool running = true;

    while (running) {
        // Poll events
        running = em.pollEvents();

        // --- Example usage of input ---
        if (em.isKeyPressed(SDLK_ESCAPE)) { // Exit on ESC
            break;
        }

        if (em.isKeyDown(SDLK_LEFT)) { circleX -= 1; }
        if (em.isKeyDown(SDLK_RIGHT)) { circleX += 1; }
        if (em.isKeyDown(SDLK_UP)) { circleY -= 1; }
        if (em.isKeyDown(SDLK_DOWN)) { circleY += 1; }

        if (em.isMousePressed(SDL_BUTTON_LEFT)) {
            std::cout << "Mouse clicked at (" << em.mouseX() << ", " << em.mouseY() << ")" << std::endl;
        }

        // --- Begin frame ---
        window.beginFrame(50, 50, 50); // dark gray background

        // --- Render texture ---
        tex.render(renderer, 50, 50);

        // --- Render primitives ---
        window.drawRect(rect, {255, 0, 0, 255});
        window.drawFilledRect({100, 400, 150, 100}, {0, 255, 0, 255});
        window.drawLine(0, 0, 800, 600, {255, 255, 0, 255});
        window.drawPoint(400, 300, {255, 0, 255, 255});
        window.drawTriangle(500, 100, 600, 200, 400, 200, {0, 255, 255, 255});
        window.drawFilledTriangle(600, 400, 700, 500, 500, 500, {128, 0, 128, 255});
        window.drawCircle(circleX, circleY, circleR, {255, 255, 255, 255});

        // --- Render text ---
        Texture::renderText(renderer, "SDL2 Library Demo", font, {255, 255, 255, 255}, {10, 10, 400, 30});

        // --- Collision check ---
        if (Collision::circleRectCollision(circleX, circleY, circleR, rect)) {
            Texture::renderText(renderer, "Circle-Rect Collision!", font, {255, 0, 0, 255}, {10, 50, 300, 30});
        }

        // --- End frame ---
        window.endFrame();

        // Clear frame-specific keys/mouse presses
        em.clearFrame();

        SDL_Delay(15); // Give or take 60 FPS
    }

    // --- Clean up ---
    TTF_CloseFont(font);

    return 0;
}
