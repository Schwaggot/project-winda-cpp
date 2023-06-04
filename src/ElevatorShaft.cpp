#include "winda/ElevatorShaft.hpp"

using namespace winda;

void ElevatorShaft::render(SDL_Renderer* renderer) const {
    SDL_Rect rect;
    rect.w = mWidth * 10;
    rect.h = mHeight * 10;
    rect.x = 10;
    rect.y = 10;

    SDL_SetRenderDrawColor(renderer, 0x21, 0x21, 0x21, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0xEE, 0x4D, 0x2E, 0xFF);
    SDL_RenderDrawRect(renderer, &rect);
}
