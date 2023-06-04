#include "winda/Floor.hpp"

using namespace winda;

void Floor::render(SDL_Renderer* renderer) const {
    SDL_Rect rect;
    rect.w = (mWidth - mElevatorShaftWidth) * 10;
    rect.h = mHeight * 10;
    rect.x = 10 + mElevatorShaftWidth * 10;
    rect.y = 10 + (mBuildingHeight - mHeight - mAltitude) * 10;

    SDL_SetRenderDrawColor(renderer, 0x21, 0x21, 0x21, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0xEE, 0x4D, 0x2E, 0xFF);
    SDL_RenderDrawRect(renderer, &rect);

    TextRenderer::getInstance().renderText(renderer, "Floor " + std::to_string(mNumber),
                                           rect.x + rect.w + 5, rect.y);
}
