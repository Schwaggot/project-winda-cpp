#include "winda/World.hpp"

using namespace winda;

World::World() {
    size_t numMales = 0;
    size_t numFemales = 0;

    for (auto i = 0; i < 100; ++i) {
        auto& person = mPersons.emplace_back();
        spdlog::info("{}", person);

        if (person.gender() == Person::Gender::MALE) {
            numMales += 1;
        } else {
            numFemales += 1;
        }
    }

    mBuilding.elevator().targetAltitude(mBuilding.floorAltitude(3));

    spdlog::info("Generated {} people ({} female and {} male)", numMales + numFemales,
                 numFemales, numMales);

    spdlog::info("Generated {}", mBuilding);
}

void World::simulate(std::chrono::microseconds delta) {
    mBuilding.elevator().simulate(delta);

    for (Person& person : mPersons) {
        person.simulate(delta);
    }
}

void World::render(SDL_Renderer* renderer) const {
    // set background color
    SDL_SetRenderDrawColor(renderer, 0x16, 0x16, 0x18, 0xFF);

    // clears the screen
    SDL_RenderClear(renderer);

    // Set renderer color red to draw the square
    SDL_SetRenderDrawColor(renderer, 0xEE, 0x4D, 0x2E, 0xFF);

    mBuilding.render(renderer);

    // TODO render persons

    // Update screen
    SDL_RenderPresent(renderer);
}
