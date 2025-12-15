#include "Texture.hpp"
#include <iostream>

// --- Constructor ---
// Loads PNG -> creates SDL_Texture -> stores width/height
Texture::Texture(SDL_Renderer* renderer, const std::string& file)
    : texture_(nullptr), width_(0), height_(0)
{
    // --- Load Image Into A Surface ---
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }
    // --- end: Load Image Into A Surface ---

    // --- Create Texture From Surface ---
    this->texture_ = SDL_CreateTextureFromSurface(renderer, surface);
    if (!this->texture_) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface); // Free surface before returning
        return;
    }

    // --- Store texture size ---
    this->width_  = surface->w;
    this->height_ = surface->h;
    // --- end: Store texture size ---

    SDL_FreeSurface(surface); // Free RAM surface, texture now on GPU
}
// --- end: Constructor ---


// --- Render method ---
// Draws the texture at given position + optional size set in hpp
void Texture::render(SDL_Renderer* renderer, int x, int y, int w, int h) const {
    if (!this->texture_) { return; } // Nothing to render
    
    SDL_Rect dst{
        x,
        y,
        (w == -1) ? this->width_  : w,
        (h == -1) ? this->height_ : h
    };
    
    SDL_RenderCopy(renderer, this->texture_, NULL, &dst);
}
// --- end: Render method ---

// --- Text rendering helper ---
// Render a single line of text using TTF font
void Texture::renderText(
    SDL_Renderer* renderer,
    const std::string& text,
    TTF_Font* font,
    SDL_Color color,
    const SDL_Rect& dstRect
) {
    // --- Render text to surface ---
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        return;
    }
    // --- end: Render text to surface ---
    
    // --- Create temporary texture from surface ---
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Surface no longer needed
    if (!texture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        return;
    }
    // --- end: Create temporary texture ---
    
    // --- Draw the text texture to renderer ---
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture); // Free temporary texture
    // --- end: Draw the text texture ---
}
// --- end: Text rendering helper ---

// --- Destructor ---
// Frees GPU texture if it exists
Texture::~Texture() {
    if (this->texture_) {
        SDL_DestroyTexture(this->texture_);
    }
}
// --- end: Destructor ---

/*
Texture workflow:
Load PNG -> Surface (RAM) ->
Create Texture (VRAM) -> Free Surface ->
Render Texture
*/
