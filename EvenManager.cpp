#include "EventManager.hpp"

EventManager::EventManager(bool mouseEnabled) {
    this->mouseEnabled_ = mouseEnabled;
    if (!this->mouseEnabled_) {
        SDL_ShowCursor(SDL_DISABLE);
    } else {
        SDL_ShowCursor(SDL_ENABLE);
    }
}

bool EventManager::pollEvents() {
    while (SDL_PollEvent(&event_)) { // Pass through the address to write to it what event happened
        switch (event_.type) {
            case SDL_QUIT:
                return false;
            
            case SDL_KEYDOWN:
                if (event_.key.keysym.sym == SDLK_SPACE) {
                    
                } break;


            
            case SDL_MOUSEBUTTONDOWN:
                if (event_.button.button == SDL_BUTTON_LEFT) {
                    
                } break;
        }
    }
    mouseButtons_ = SDL_GetMouseState(&mouseX_, &mouseY_);
    return true;
}