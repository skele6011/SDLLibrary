#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class SDLInitializer {
private:
    bool sdlInitialized_;
    bool imgInitialized_;
    bool ttfInitialized_;

public:
    SDLInitializer(Uint32 flags, int imgFlags);

    ~SDLInitializer();

    TTF_Font* openFont(const std::string& file, int size);

    bool sdlInitialized() const { return sdlInitialized_; }
    bool imgInitialized() const { return imgInitialized_; }
    bool ttfInitialized() const { return ttfInitialized_; }
};

