/******************************************************************************
 * Texture.hpp v1.0
 * Simple SDL texture wrapper. Includes the following:
    * Load a PNG image into a texture
    * Render texture to screen
    * Render text using TTF fonts
 ******************************************************************************/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>


class Texture {
public:
    // --- Constructor ---
    // Loads the PNG image from file and creates an SDL_Texture
    Texture(SDL_Renderer* renderer, const std::string& file);
    // --- end: Constructor ---

    // --- Destructor ---
    // Frees SDL_Texture from GPU memory
    ~Texture();
    // --- end: Destructor ---

    // --- Render method ---
    // Draws the texture onto the renderer at position (x, y)
    // w/h: -1 means use natural texture size
    void render(SDL_Renderer* renderer, int x, int y, int w = -1, int h = -1) const;
    // --- end: Render method ---

    // --- Text rendering helper ---
    // Creates a temporary texture from the specified text + font + color
    // Draws it at the given destination rectangle
    static void renderText(
        SDL_Renderer* renderer,
        const std::string& text,
        TTF_Font* font,
        SDL_Color color,
        const SDL_Rect& dstRect
    );
    // --- end: Text rendering helper ---

    // --- Getters ---
    int width() const { return width_; }   // Returns width of texture
    int height() const { return height_; } // Returns height of texture
    // --- end: Getters ---

private:
    SDL_Texture* texture_; // GPU-side texture
    int width_;            // Width in pixels
    int height_;           // Height in pixels
};
