#include "winda/World.hpp"

#include "SDL.h"
#include "SDL_timer.h"
#include "spdlog/spdlog.h"

using namespace std;
using namespace std::chrono;
using namespace winda;

int main(int, char**) {
    World world;

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        spdlog::error("error initializing SDL_ERROR:{}", SDL_GetError());
    }

    SDL_Window* window =
        SDL_CreateWindow("Project Winda", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
    if (!window) {
        spdlog::error("Window could not be created, SDL_ERROR: {}", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // creates a renderer to render our images
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // controls animation loop
    bool run = true;

    // initialize clock
    steady_clock::time_point last = steady_clock::now();

    // animation loop
    while (run) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                run = false;
                break;
            }
        }

        // update object positions etc.
        steady_clock::time_point now = steady_clock::now();
        world.simulate(duration_cast<microseconds>(now - last));
        last = now;

        // render objects
        world.render(renderer);

        // calculates to 30 fps
        SDL_Delay(1000 / 30);
    }

    // destroy renderer
    SDL_DestroyRenderer(renderer);

    // destroy window
    SDL_DestroyWindow(window);

    // close SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
