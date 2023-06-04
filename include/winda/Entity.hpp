#ifndef PROJECT_WINDA_ENTITY_HPP
#define PROJECT_WINDA_ENTITY_HPP

#include "SDL_render.h"
#include <chrono>

namespace winda {

class Entity {
public:
    virtual ~Entity() {}

    virtual void simulate(std::chrono::microseconds delta) = 0;
    virtual void render(SDL_Renderer* renderer) const = 0;
};

} // namespace winda

#endif // PROJECT_WINDA_ENTITY_HPP
