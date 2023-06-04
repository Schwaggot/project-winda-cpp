#include "winda/Building.hpp"

using namespace winda;

Building::Building() : mElevatorShaft(mHeight, mFloors), mElevator(mElevatorShaft) {
    for (auto i = 0u; i < 21; ++i) {
        mFloors.emplace_back(mWidth, mHeight, mElevatorShaft.width(), i);
        mFloorAltitudes.emplace_back(mFloors.back().altitude());
    }
}

void Building::render(SDL_Renderer* renderer) const {
    SDL_Rect rect;
    rect.w = mWidth * 10;
    rect.h = mHeight * 10;
    rect.x = 10;
    rect.y = 10;

    SDL_RenderDrawRect(renderer, &rect);

    for (const auto& floor : mFloors) {
        floor.render(renderer);
    }

    mElevatorShaft.render(renderer);
    mElevator.render(renderer);
}
