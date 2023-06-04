#ifndef PROJECT_WINDA_ELEVATOR_HPP
#define PROJECT_WINDA_ELEVATOR_HPP

#include "winda/ElevatorShaft.hpp"
#include "winda/Entity.hpp"
#include "winda/Person.hpp"

#include "spdlog/fmt/fmt.h"
#include "spdlog/spdlog.h"
#include <cassert>
#include <chrono>
#include <cstdint>

namespace winda {

class Elevator : public Entity {
public:
    /**
     * Movement state of the elevator. Following transitions are possible:
     * STOPPED -> ACCELERATING
     * ACCELERATING -> MAX_VELOCITY | DECELERATING
     * DECELERATING -> STOPPED
     * MAX_VELOCITY -> DECELERATING
     * OVERWEIGHT -> STOPPED
     *
     * TODO check invariants
     */
    enum State { STOPPED, ACCELERATING, DECELERATING, MAX_VELOCITY, OVERWEIGHT };

    /**
     * Whether elevator is going up or down, since velocity is always non-negative.
     */
    enum Direction { UP, DOWN };

    /**
     * The state of the elevator doors. Should only transition as follows:
     * OPEN -> CLOSING -> CLOSED -> OPENING -> OPEN
     *
     * TODO check invariants
     */
    enum DoorState { CLOSED, CLOSING, OPEN, OPENING };

    Elevator(const ElevatorShaft& elevatorShaft)
        : mMaxAltitude(elevatorShaft.height() - mHeight), mElevatorShaft(elevatorShaft) {}

    void simulate(std::chrono::microseconds delta) override;
    void render(SDL_Renderer* renderer) const override;

    void personEnters(const Person& person);
    void personExits(const Person& person);

    inline float maxAltitude() const { return mMaxAltitude; };

    inline float altitude() const { return mAltitude; }
    inline float targetAltitude() const { return mTargetAltitude; }
    inline void targetAltitude(float targetAltitude) {
        if (targetAltitude > mMaxAltitude) {
            throw std::runtime_error("target altitude exceeds max. elevator altitude");
        }
        mTargetAltitude = targetAltitude;
    }
    inline float velocity() const { return mVelocity; }
    inline float acceleration() const { return mAcceleration; }
    inline State state() const { return mState; }
    inline DoorState doorState() const { return mDoorState; }
    inline Direction direction() const { return mDirection; }

private:
    /**
     * Stops the elevator, i.e., switches to STOPPED, sets velocity to 0. If target
     * altitude is reached starts opening doors.
     */
    void stop();

    /**
     * Checks whether the elevator has reached the target altitude within +/- 1cm.
     * @return true if target altitude is reached, false otherwise
     */
    inline bool targetAltitudeReached() {
        return std::abs(mTargetAltitude - mAltitude) < 0.01f;
    }

    const float mWidth = 2.8f;  // in meters
    const float mHeight = 2.2f; // in meters

    const float mMaxWeight = 250.f; // in kg
    const uint8_t mMaxPassengers = 6;
    const float mMaxVelocity = 1.6f; // in meters per second
    const float mMinAltitude = 0.f;  // in meters
    const float mMaxAltitude = 64.f; // in meters
    const std::chrono::milliseconds mDoorRemainOpenDuration = std::chrono::seconds(10);
    const std::chrono::milliseconds mDoorActionDuration = std::chrono::milliseconds(2500);
    const float mAcceleration = 0.6f; // in meters per second squared
    const float mDeceleration = 0.7f; // in meters per second squared

    float mAltitude = 0;        // in meters above ground
    float mTargetAltitude = 32; // in meters above ground
    float mWeight = 0;          // in kg
    uint8_t mPassengers = 0;    // current number of passengers
    float mVelocity = 0;        // in meters per second

    DoorState mDoorState = CLOSED;
    std::chrono::milliseconds mDoorActionTimeElapsed = std::chrono::milliseconds(0);
    State mState = STOPPED;
    Direction mDirection = UP;

    const ElevatorShaft& mElevatorShaft;
};

} // namespace winda

template <>
struct fmt::formatter<winda::Elevator::State> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(winda::Elevator::State const& elevatorState, FormatContext& ctx) {
        switch (elevatorState) {
        case winda::Elevator::STOPPED:
            return fmt::format_to(ctx.out(), "STOPPED");
        case winda::Elevator::ACCELERATING:
            return fmt::format_to(ctx.out(), "ACCELERATING");
        case winda::Elevator::DECELERATING:
            return fmt::format_to(ctx.out(), "DECELERATING");
        case winda::Elevator::MAX_VELOCITY:
            return fmt::format_to(ctx.out(), "MAX_VELOCITY");
        case winda::Elevator::OVERWEIGHT:
            return fmt::format_to(ctx.out(), "OVERWEIGHT");
        default:
            throw std::invalid_argument("invalid value for ElevatorState");
        }
    }
};

template <>
struct fmt::formatter<winda::Elevator::DoorState> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(winda::Elevator::DoorState const& doorState, FormatContext& ctx) {
        switch (doorState) {
        case winda::Elevator::CLOSED:
            return fmt::format_to(ctx.out(), "CLOSED");
        case winda::Elevator::CLOSING:
            return fmt::format_to(ctx.out(), "CLOSING");
        case winda::Elevator::OPEN:
            return fmt::format_to(ctx.out(), "OPEN");
        case winda::Elevator::OPENING:
            return fmt::format_to(ctx.out(), "OPENING");
        default:
            throw std::invalid_argument("invalid value for DoorState");
        }
    }
};

template <>
struct fmt::formatter<winda::Elevator::Direction> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(winda::Elevator::Direction const& direction, FormatContext& ctx) {
        switch (direction) {
        case winda::Elevator::UP:
            return fmt::format_to(ctx.out(), "UP");
        case winda::Elevator::DOWN:
            return fmt::format_to(ctx.out(), "DOWN");
        default:
            throw std::invalid_argument("invalid value for ElevatorDirection");
        }
    }
};

template <>
struct fmt::formatter<winda::Elevator> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(winda::Elevator const& elevator, FormatContext& ctx) {
        return fmt::format_to(ctx.out(),
                              "Elevator alt={:>4.2f}m targetAlt={:>4.2f}m direction={} "
                              "v={:>5.3f}m/s a={:>1.1f}m/s^2 doors={} state={}",
                              elevator.altitude(), elevator.targetAltitude(),
                              elevator.direction(), elevator.velocity(),
                              elevator.acceleration(), elevator.doorState(),
                              elevator.state());
    }
};

#endif // PROJECT_WINDA_ELEVATOR_HPP
