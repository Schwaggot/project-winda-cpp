#ifndef PROJECT_WINDA_ELEVATORSHAFT_HPP
#define PROJECT_WINDA_ELEVATORSHAFT_HPP

#include "winda/Entity.hpp"
#include "winda/Floor.hpp"

#include <cstdint>

namespace winda {

class ElevatorShaft : public Entity {
public:
    ElevatorShaft(uint16_t height, const std::vector<Floor>& floors)
        : mHeight(height), mFloors(floors) {}

    void simulate(std::chrono::microseconds) override {}
    void render(SDL_Renderer* renderer) const override;

    inline uint16_t width() const { return mWidth; }
    inline uint16_t height() const { return mHeight; }

private:
    uint16_t mWidth = 3;  // in meters
    uint16_t mHeight = 3; // in meters
    const std::vector<Floor>& mFloors;
};

} // namespace winda

#endif // PROJECT_WINDA_ELEVATORSHAFT_HPP
