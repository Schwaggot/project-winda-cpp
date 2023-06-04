#ifndef PROJECT_WINDA_BUILDING_HPP
#define PROJECT_WINDA_BUILDING_HPP

#include "Elevator.hpp"
#include "ElevatorShaft.hpp"
#include "winda/Floor.hpp"

#include <cstdint>
#include <vector>

namespace winda {

class Building : public Entity {
public:
    Building();

    void simulate(std::chrono::microseconds) override {}
    void render(SDL_Renderer* renderer) const override;

    inline uint16_t width() const { return mWidth; }
    inline uint16_t height() const { return mHeight; }
    inline int16_t altitude() const { return mAltitude; }
    inline const std::vector<Floor>& floors() const { return mFloors; }
    inline const std::vector<uint16_t>& floorAltitudes() const { return mFloorAltitudes; }
    inline uint16_t floorAltitude(size_t floor) const { return mFloorAltitudes[floor]; }
    inline ElevatorShaft& elevatorShaft() { return mElevatorShaft; }
    inline Elevator& elevator() { return mElevator; }

private:
    uint16_t mWidth = 32;
    uint16_t mHeight = 63;
    int16_t mAltitude = 0; // in meters above ground

    std::vector<Floor> mFloors;
    std::vector<uint16_t> mFloorAltitudes;
    ElevatorShaft mElevatorShaft;
    Elevator mElevator;
};

} // namespace winda

template <>
struct fmt::formatter<winda::Building> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(winda::Building const& building, FormatContext& ctx) {
        return fmt::format_to(
            ctx.out(), "Building width={}m height={}m altitude={} floors.size()={}",
            building.width(), building.height(), building.altitude(),
            building.floors().size());
    }
};

#endif // PROJECT_WINDA_BUILDING_HPP
