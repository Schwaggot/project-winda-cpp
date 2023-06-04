#ifndef PROJECT_WINDA_PERSON_HPP
#define PROJECT_WINDA_PERSON_HPP

#include "winda/NameGenerator.hpp"
#include "winda/RandomGenerator.hpp"

#include "spdlog/fmt/fmt.h"

namespace winda {

class Person : public Entity {
public:
    enum Gender { MALE, FEMALE };

    Person() : mGender(RandomGenerator::getInstance().randomBool() ? MALE : FEMALE) {
        // name
        switch (mGender) {
        case MALE:
            mName = NameGenerator::getInstance().maleName();
            break;
        case FEMALE:
            mName = NameGenerator::getInstance().femaleName();
            break;
        }

        // age
        mAge = RandomGenerator::getInstance().randomPersonAge();

        // height
        // TODO educated guess or formula
        mHeight = RandomGenerator::getInstance().randomPersonHeight();

        // weight
        // calculate weight based on Hamwi method,
        // see https://en.wikipedia.org/wiki/Human_body_weight#Hamwi_method
        switch (mGender) {
        case MALE:
            mWeight = 48.f + 1.1f * ((float)mHeight - 152.f);
            break;
        case FEMALE:
            mWeight = 45.4f + 0.9f * ((float)mHeight - 152.f);
            break;
        }
    }

    void simulate(std::chrono::microseconds) override {}
    void render(SDL_Renderer*) const override {}

    inline std::string_view name() const { return mName; }
    inline Gender gender() const { return mGender; }
    inline uint8_t age() const { return mAge; }
    inline float weight() const { return mWeight; }
    inline float height() const { return mHeight; }

private:
    std::string mName;
    Gender mGender = MALE;
    uint8_t mAge;
    float mWeight; // in meters
    float mHeight; // in centimeters
};

} // namespace winda

template <>
struct fmt::formatter<winda::Person> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(winda::Person const& person, FormatContext& ctx) {
        return fmt::format_to(
            ctx.out(), "Person name={} gender={} age={} weight={}kg height={}cm",
            person.name(), person.gender() == winda::Person::MALE ? "MALE" : "FEMALE",
            person.age(), person.weight(), person.height());
    }
};

#endif // PROJECT_WINDA_PERSON_HPP
