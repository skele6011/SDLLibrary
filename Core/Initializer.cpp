#include "Initializer.hpp"

// --- Constructor ---
// Initializes SDL, SDL_image, and SDL_ttf
SDLInitializer::SDLInitializer(Uint32 flags, int imgFlags)
    : sdlInitialized_(false), imgInitialized_(false), ttfInitialized_(false)
{
    // --- Initialize SDL ---
    if (SDL_Init(flags) != 0) { // SDL_Init returns 0 on success
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    this->sdlInitialized_ = true;
    // --- end: Initialize SDL ---

    // --- Initialize SDL_image ---
    if (IMG_Init(imgFlags) != imgFlags) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return;
    }
    this->imgInitialized_ = true;
    // --- end: Initialize SDL_image ---

    // --- Initialize SDL_ttf ---
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return;
    }
    this->ttfInitialized_ = true;
    // --- end: Initialize SDL_ttf ---
}
// --- end: Constructor ---


// --- Open Font ---
// Loads a TTF font and returns a pointer
TTF_Font* SDLInitializer::openFont(const std::string& file, int size) {
    TTF_Font* font = TTF_OpenFont(file.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    return font;
}
// --- end: Open Font ---


// --- Destructor ---
// Cleans up SDL, SDL_image, and SDL_ttf if they were initialized
SDLInitializer::~SDLInitializer() {
    if (this->ttfInitialized_) { TTF_Quit(); }
    if (this->imgInitialized_) { IMG_Quit(); }
    if (this->sdlInitialized_) { SDL_Quit(); }
}
// --- end: Destructor ---
