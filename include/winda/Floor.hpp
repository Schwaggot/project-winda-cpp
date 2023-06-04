#ifndef PROJECT_WINDA_FLOOR_HPP
#define PROJECT_WINDA_FLOOR_HPP

#include "TextRenderer.hpp"
#include "spdlog/fmt/fmt.h"
#include "winda/Entity.hpp"
#include <cstdint>

namespace winda {

class Floor : public Entity {
public:
    Floor(uint16_t buildingWidth,
          uint16_t buildingHeight,
          uint16_t elevatorShaftWidth,
          uint8_t number)
        : mNumber(number),
          mWidth(buildingWidth),
          mBuildingHeight(buildingHeight),
          mElevatorShaftWidth(elevatorShaftWidth),
          mAltitude(mNumber * mHeight) {}

    void simulate(std::chrono::microseconds) override {}
    void render(SDL_Renderer* renderer) const override;

    inline uint8_t number() const { return mNumber; }
    inline uint16_t height() const { return mHeight; }
    inline int16_t altitude() const { return mAltitude; }

private:
    uint8_t mNumber = 0;              // 1st floor, 2nd floor etc.
    uint16_t mWidth = 0;              // in meters
    uint16_t mHeight = 3;             // in meters
    uint16_t mBuildingHeight = 0;     // in meters
    uint16_t mElevatorShaftWidth = 3; // in meters
    int16_t mAltitude = 0;            // in meters above ground
};

} // namespace winda

template <>
struct fmt::formatter<winda::Floor> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(winda::Floor const& floor, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "Floor number={} height={}m altitude={}m",
                              floor.number(), floor.height(), floor.altitude());
    }
};

#endif // PROJECT_WINDA_FLOOR_HPP
