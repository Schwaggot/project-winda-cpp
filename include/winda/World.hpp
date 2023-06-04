#ifndef PROJECT_WINDA_WORLD_HPP
#define PROJECT_WINDA_WORLD_HPP

#include "winda/Building.hpp"
#include "winda/Person.hpp"

#include "spdlog/spdlog.h"
#include "winda/TextRenderer.hpp"

namespace winda {

class World : public Entity {
public:
    World();

    void simulate(std::chrono::microseconds delta) override;
    void render(SDL_Renderer* renderer) const override;

private:
    Building mBuilding;
    std::vector<Person> mPersons;
};

} // namespace winda

#endif // PROJECT_WINDA_WORLD_HPP
