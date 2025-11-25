#include "Initializer.hpp"

SDLInitializer::SDLInitializer(Uint32 flags, int imgFlags)  { // Flags such as SDL_INIT_VIDEO are in Uint32
    if (SDL_Init(flags) != 0) { // SDL_Init returns 0 if success
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        sdlInitialized_ = false;
        return;
    } 
    sdlInitialized_ = true;

    if ((IMG_Init(imgFlags)) != imgFlags) {
        std::cerr << "IMG_Init error: " << IMG_GetError() << std::endl;
        return;
    }
    imgInitialized_ = true;

    if (TTF_Init() == -1) {
        std::cerr << "TFT_Init error:" << TTF_GetError() << std::endl;
        return;
    }
    ttfInitialized_ = true;
}

TTF_Font* SDLInitializer::openFont(const std::string& file, int size) {
    TTF_Font* font = TTF_OpenFont(file.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    return font;
}

SDLInitializer::~SDLInitializer() {
    if (sdlInitialized_) { // Only quit if was initialized, otherwise, not necessary.
        SDL_Quit();
    }
    if (imgInitialized_) {
        IMG_Quit();
    }
    if (ttfInitialized_) {
        TTF_Quit();
    }
}