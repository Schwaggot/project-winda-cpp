# Project Winda (C++)

A simple simulation of an elevator using C++ and SDL2.

## Dependencies

System dependencies:

- CMake >=3.16
- C++17 compatible build environment

Tested on:
- MinGW 11.2.0
- Visual Studio 17
- WSL2 Debian 11 (compiles, but window does not open)

Bundled as git submodules:

- [SDL2](https://github.com/libsdl-org/SDL) release-2.26.5 for rendering
- [SDL2 TTF](https://github.com/libsdl-org/SDL_ttf) release-2.20.2 for text rendering
- [spdlog](https://github.com/gabime/spdlog) v1.11.0 for logging

## TODO

- Simulation of button pressing
- Simulation and rendering of passengers (movement, target destinations, weight etc.)
- Rendering of elevator doors
- Allow multiple buildings and elevators
- Unit testing (skipped due to `SDL2 missing main` errors)

## Acknowledgements

- Male and female names come from
  the [CMU Name Corpus](https://www.cs.cmu.edu/Groups/AI/util/areas/nlp/corpora/names/0.html)
- [Google Open Sans](https://fonts.google.com/specimen/Open+Sans) as a font
