#include "Texture.hpp"
#include <iostream>

Texture::Texture(SDL_Renderer* renderer, const std::string& file) 
    : texture_(nullptr), width_(0), height_(0)
{

    // --- Load Image Into A Surface ---
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        std::cerr << "Failed to load PNG: " << IMG_GetError() << std::endl;
        return;
    }
    // --- ---- ---- ---

    // --- Create Texture From Surface --- 
    texture_ = SDL_CreateTextureFromSurface(renderer, surface); // Converts CPU-side surface into GPU-side texture
    if (!texture_) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    } else {
        // Simply get the width from surface struct and load them into our variables
        this->width_ = surface->w;
        this->height_ = surface->h;
    }
    // --- ---- ---- ---
    
    // --- Clear Surface ---
    SDL_FreeSurface(surface); // No use for it anymore, clear RAM.
    // --- ---- ---- ---
}

Texture::~Texture() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int w, int h) const {
    if (!texture_) return; //  Nothing to rnder

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = (w == -1) ? this->width_ : w;
    dstRect.h = (h == -1) ? this->height_ : h;

    SDL_RenderCopy(renderer, texture_, nullptr, &dstRect); // Draw texture onto the renderer. nullptr just means to use the entire texture, not just a part.
}

void Texture::handleFont(TTF_Font* font, const std::string& text, SDL_Color color, SDL_Renderer* renderer, SDL_Rect dstRect) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}


/*
Load PNG -> Surface (RAM) ->
Convert Surface -> Texture (VRAM) ->
Free surface (no longer need) ->
Draw using texture
*/