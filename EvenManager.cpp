#include "EventManager.hpp"

// --- Constructor ---
EventManager::EventManager(bool mouseEnabled) {
    // Show or hide cursor depending on mouseEnabled
    this->mouseEnabled_ = mouseEnabled;
    if (!this->mouseEnabled_) {
        SDL_ShowCursor(SDL_DISABLE);
    } else {
        SDL_ShowCursor(SDL_ENABLE);
    }
}
// --- end: Constructor ---

// --- Main Method: Polling of events ---
bool EventManager::pollEvents() {
    // Clear keys from previous frame
    this->keysDownThisFrame_.clear();

    // Run event loop
    while (SDL_PollEvent(&this->event_)) { // Process all pending events
        // Quit if quit (return false)
        switch (this->event_.type) {
            case SDL_QUIT:
                return false;

            // If a key is done, add that key to our set to be used
            case SDL_KEYDOWN:
                this->keysDownThisFrame_.insert(this->event_.key.keysym.sym);
                break;
            
            // If a mouse is pressed, add that key to our set to be used
            case SDL_MOUSEBUTTONDOWN:
                this->mouseButtonsPressedThisFrame_.insert(this->event_.button.button);
                break;
        }
    }

    // Set mouseButtons to be the ones pressed and give mouseX and mouseY their values\
    // Return true (so program knows we didn't quit)
    this->mouseButtons_ = SDL_GetMouseState(&this->mouseX_, &this->mouseY_); 
    return true;
}
// --- end: Main Method ---


// --- Key held down method ---
// Returns true if the specified key is currently being held down (across all frames).
bool EventManager::isKeyDown(SDL_KeyCode key) const {
    SDL_Scancode sc = SDL_GetScancodeFromKey(key);
    return this->state_[sc] != 0;
}
// --- end: Key held down method ---

// --- Key pressed method ---
// Returns true only on the frame when the key was first pressed.
// Subsequent frames while holding the key will return false.
bool EventManager::isKeyPressed(SDL_KeyCode key) const {
    return this->keysDownThisFrame_.find(key) != this->keysDownThisFrame_.end();
}
// --- end: Key pressed method ---

// --- Mouse pressed method ---
// Returns true only on the frame when the specified mouse button was pressed.
bool EventManager::isMousePressed(Uint8 button) const {
    return mouseButtonsPressedThisFrame_.find(button) != mouseButtonsPressedThisFrame_.end(); 
}
// --- end: Mouse pressed method ---

// --- Manual clearing method --- 
// Clear keys/mouse buttons pressed in previous frame
void EventManager::clearFrame() {
    this->keysDownThisFrame_.clear();
    this->mouseButtonsPressedThisFrame_.clear();
}
// --- end: Manual clearing ---
