/******************************************************************************
 * SDLInitializer.hpp v1.0
 * Simple wrapper to initialize SDL, SDL_image, and SDL_ttf subsystems.
 * Includes:
 *   * SDL, IMG, and TTF initialization with error checking
 *   * Font loading helper
 ******************************************************************************/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class SDLInitializer {
private:
    bool sdlInitialized_; // True if SDL was successfully initialized
    bool imgInitialized_; // True if SDL_image was successfully initialized
    bool ttfInitialized_; // True if SDL_ttf was successfully initialized

public:
    // --- Constructor ---
    // Initializes SDL, SDL_image, and SDL_ttf
    SDLInitializer(Uint32 flags, int imgFlags);
    // --- end: Constructor ---

    // --- Destructor ---
    // Cleans up SDL, SDL_image, and SDL_ttf if they were initialized
    ~SDLInitializer();
    // --- end: Destructor ---

    // --- Font Loader ---
    // Opens a TTF font and returns a pointer
    TTF_Font* openFont(const std::string& file, int size);
    // --- end: Font Loader ---

    // --- Getters ---
    bool sdlInitialized() const { return sdlInitialized_; }
    bool imgInitialized() const { return imgInitialized_; }
    bool ttfInitialized() const { return ttfInitialized_; }
    // --- end: Getters ---
};
