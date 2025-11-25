#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class EventManager {
private:
    bool mouseEnabled_;

    SDL_Event event_;

    const Uint8* state_ = SDL_GetKeyboardState(NULL);

    int mouseX_ = 0;
    int mouseY_ = 0; 
    Uint32 mouseButtons_ = 0;

public:
    EventManager(bool mouseEnabled);

    bool pollEvents();

    const Uint8* state() const { return state_; }
    int mouseX() const { return mouseX_; }
    int mouseY() const { return mouseY_; }
    Uint32 mouseButtons() const { return mouseButtons_; }
};