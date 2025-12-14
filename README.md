# SDLLibrary

A small SDL-based C++ library for personal projects.

## Modules

- [x] EventManager – mouse events, quitting, keyboard presses and holds
- [x] Initializer – initializes SDL, `SDL_image`, `SDL_ttf`
- [x] Texture – loads and draws images and fonts
- [x] Window – creates window, draws basic shapes, manages frame start/end
- [x] Collision – circle-to-circle and circle-to-rectangle detection

## Notes

- Everything is static where it makes sense
- All drawing is manual, no need for SDL_gfx (primitives or not)
- For Texture and Initializer, `SDL_ttf` and `SDL_image` are required
- Currently 10 files, flat structure. Empty Core & Utils folders just incase I ever decide to expand it.
