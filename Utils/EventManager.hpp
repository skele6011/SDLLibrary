/******************************************************************************
 * EventManager.hpp/cpp v1.1
 * Simple SDL event manager. Includes the following:
    * Keys held down
    * Keys pressed (single-frame)
    * Mouse X and Y getters
    * Mouse buttons presses (single-frame)
    * Quit checking throgh pollEvents
    * Getters for windowHeight and windowWidth that dynamically adjust
 ******************************************************************************/

#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <unordered_set> 

class EventManager {
// --- Member variables ---
private:
    SDL_Event event_; // Event struct
    const Uint8* state_ = SDL_GetKeyboardState(NULL); // Holds current state

    bool mouseEnabled_;
    int mouseX_ = 0;
    int mouseY_ = 0; 
    Uint32 mouseButtons_ = 0;

    // Holds the keys pressed that frame (mouse and keyboard)
    std::unordered_set<int> keysDownThisFrame_;
    std::unordered_set<Uint8> mouseButtonsPressedThisFrame_;

    // Window stuff
    int windowWidth_ = 0;
    int windowHeight_ = 0;
    SDL_Window* window_ = nullptr; // Reference to the SDL window

// --- end: Member variables ---

public:
    EventManager(SDL_Window* window, bool mouseEnabled);

    // Poll events for this frame; returns false if SDL_QUIT is received
    bool pollEvents();

    // Key held down (like SDL_GetKeyboardState)
    bool isKeyDown(SDL_KeyCode key) const;

    // Key pressed this frame only
    bool isKeyPressed(SDL_KeyCode key) const;

    // Mouse pressed this frame only
    bool isMousePressed(Uint8 buttons) const;

    // --- Getters ---
    const Uint8* state() const { return state_; }
    int mouseX() const { return mouseX_; }
    int mouseY() const { return mouseY_; }
    Uint32 mouseButtons() const { return mouseButtons_; }
    int windowWidth() const { return windowWidth_; }
    int windowHeight() const { return windowHeight_; }
    // --- end: Getters ---

    void clearFrame();
};
