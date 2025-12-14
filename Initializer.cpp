#include "Initializer.hpp"

SDLInitializer::SDLInitializer(Uint32 flags, int imgFlags)  {
    if (SDL_Init(flags) != 0) { // SDL_Init returns 0 if success
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        this->sdlInitialized_ = false;
        return;
    } 
    this->sdlInitialized_ = true;

    if ((IMG_Init(imgFlags)) != imgFlags) {
        std::cerr << "IMG_Init error: " << IMG_GetError() << std::endl;
        return;
    }
    this->imgInitialized_ = true;

    if (TTF_Init() == -1) {
        std::cerr << "TFT_Init error:" << TTF_GetError() << std::endl;
        return;
    }
    this->ttfInitialized_ = true;
}

TTF_Font* SDLInitializer::openFont(const std::string& file, int size) {
    TTF_Font* font = TTF_OpenFont(file.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    return font;
}

SDLInitializer::~SDLInitializer() {
    // Only quit if was initialized, otherwise, not necessary.
    if (this->sdlInitialized_) {
        SDL_Quit();
    }
    if (this->imgInitialized_) {
        IMG_Quit();
    }
    if (this->ttfInitialized_) {
        TTF_Quit();
    }
}