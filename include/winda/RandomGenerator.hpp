#ifndef PROJECT_WINDA_RANDOMGENERATOR_HPP
#define PROJECT_WINDA_RANDOMGENERATOR_HPP

#include <cstdint>
#include <functional>

namespace winda {

class RandomGenerator {
public:
    static RandomGenerator& getInstance() {
        static RandomGenerator instance; // Guaranteed to be destroyed.
                                         // Instantiated on first use.
        return instance;
    }

    RandomGenerator(RandomGenerator const&) = delete;
    void operator=(RandomGenerator const&) = delete;

    bool randomBool() {
        static auto gen = std::bind(std::uniform_int_distribution<>(0, 1),
                                    std::default_random_engine());
        return gen();
    }

    uint8_t randomPersonHeight() {
        static auto gen = std::bind(std::uniform_int_distribution<>(150, 190),
                                    std::default_random_engine());
        return static_cast<uint8_t>(gen());
    }

    uint8_t randomPersonAge() {
        static auto gen = std::bind(std::uniform_int_distribution<>(6, 99),
                                    std::default_random_engine());
        return static_cast<uint8_t>(gen());
    }

private:
    RandomGenerator() {}
};

} // namespace winda

#endif // PROJECT_WINDA_RANDOMGENERATOR_HPP
