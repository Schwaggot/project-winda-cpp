#include "winda/Elevator.hpp"

using namespace std;
using namespace std::chrono;
using namespace winda;

void Elevator::simulate(std::chrono::microseconds delta) {
    float seconds = delta.count() / 1000.f / 1000.f;

    // calculate distance to target floor
    float distanceToTargetAltitude = std::abs(mTargetAltitude - mAltitude);

    if (mVelocity == 0.f) {
        // update door state
        switch (mDoorState) {
        case OPEN:
            mDoorActionTimeElapsed += duration_cast<milliseconds>(delta);
            if (mDoorActionTimeElapsed >= mDoorRemainOpenDuration) {
                mDoorState = CLOSING;
            }
            return;
        case CLOSING:
            mDoorActionTimeElapsed += duration_cast<milliseconds>(delta);
            if (mDoorActionTimeElapsed >= mDoorActionDuration) {
                mDoorState = CLOSED;
                break;
            }
            return;
        case OPENING:
            mDoorActionTimeElapsed += duration_cast<milliseconds>(delta);
            if (mDoorActionTimeElapsed >= mDoorActionDuration) {
                mDoorState = OPEN;
            }
            return;
        case CLOSED:
        default:
            break;
        }
    }

    // accept stopping accuracy of +/- 1cm
    if (targetAltitudeReached() && mVelocity == 0.f) {
        // destination reached
        return;
    }

    assert(mDoorState == DoorState::CLOSED);

    // calculate stopping distance and distance to target
    float breakDistance = (mVelocity * mVelocity) / (2.f * mDeceleration);

    // if necessary, decelerate in time to reach target altitude
    if ((distanceToTargetAltitude <= breakDistance) &&
        (mState == ACCELERATING || mState == MAX_VELOCITY)) {
        mState = DECELERATING;
    }

    // update velocity and direction
    switch (mState) {
    case STOPPED:
        // decide direction and switch into acceleration mode
        assert(!targetAltitudeReached());
        mDirection = mTargetAltitude > mAltitude ? UP : DOWN;
        mState = ACCELERATING;
        break;
    case ACCELERATING:
        // else accelerate towards (but do not exceed) the maximum velocity
        if (mVelocity < mMaxVelocity) {
            mVelocity = mVelocity + mAcceleration * seconds;
            if (mVelocity > mMaxVelocity) {
                mVelocity = mMaxVelocity;
                mState = MAX_VELOCITY;
            }
        }
        break;
    case DECELERATING:
        // decelerate towards full stop
        if (mVelocity > 0.f) {
            mVelocity = mVelocity - mDeceleration * seconds;
            if (mVelocity <= 0.f) {
                stop();
            }
        }
        break;
    case MAX_VELOCITY:
        break;
    case OVERWEIGHT:
        // elevator cannot move as long as too many people are inside
        return;
    }

    // update altitude
    mAltitude = mDirection == UP ? mAltitude + mVelocity * seconds
                                 : mAltitude - mVelocity * seconds;
    if (mAltitude > mMaxAltitude) {
        mAltitude = mMaxAltitude;
        stop();
    }
    if (mAltitude < mMinAltitude) {
        mAltitude = mMinAltitude;
        stop();
    }
}

void Elevator::personEnters(const Person& person) {
    assert(mState == STOPPED || mState == OVERWEIGHT);
    if (mPassengers == mMaxPassengers) {
        throw runtime_error(
            "cannot fit more than max number of passengers into elevator");
    }
    mWeight += person.weight();
    ++mPassengers;
}

void Elevator::personExits(const Person& person) {
    assert(mState == STOPPED || mState == OVERWEIGHT);
    mWeight -= person.weight();
    assert(mWeight >= 0.f);
    assert(mPassengers > 0);
    --mPassengers;
}

void Elevator::stop() {
    mState = STOPPED;
    mVelocity = 0.f;
    if (targetAltitudeReached()) {
        mDoorState = OPENING;
    }
}

void Elevator::render(SDL_Renderer* renderer) const {
    SDL_Rect rect;
    rect.w = mWidth * 10;
    rect.h = mHeight * 10;
    rect.x = 11;
    rect.y = 10 + (mElevatorShaft.height() - mAltitude - mHeight) * 10;

    SDL_SetRenderDrawColor(renderer, 0x2A, 0x2E, 0x31, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0xD2, 0x3C, 0x22, 0xFF);
    SDL_RenderDrawRect(renderer, &rect);
}
