#ifndef PROJECT_WINDA_NAMEGENERATOR_H
#define PROJECT_WINDA_NAMEGENERATOR_H

#include <filesystem>
#include <fstream>
#include <functional>
#include <random>

namespace winda {

class NameGenerator {
public:
    static NameGenerator& getInstance() {
        static NameGenerator instance; // Guaranteed to be destroyed.
                                       // Instantiated on first use.
        return instance;
    }

    NameGenerator(NameGenerator const&) = delete;
    void operator=(NameGenerator const&) = delete;

    inline const std::string& maleName() const {
        static auto gen =
            std::bind(std::uniform_int_distribution<size_t>(0, mMaleNames.size()),
                      std::default_random_engine());
        return mMaleNames[gen()];
    }

    inline const std::string& femaleName() const {
        static auto gen =
            std::bind(std::uniform_int_distribution<size_t>(0, mMaleNames.size()),
                      std::default_random_engine());
        return mFemaleNames[gen()];
    }

private:
    NameGenerator() {
        auto path = std::filesystem::path() / "data" / "cmu-name-corpus" / "male_names.txt";
        std::ifstream maleNamesIFStream(path);
        if (!maleNamesIFStream) {
            throw std::runtime_error("unable to open male_names.txt");
        }

        std::string line;
        while (std::getline(maleNamesIFStream, line)) {
            if (!line.empty() && line.at(0) != '#') {
                mMaleNames.emplace_back(line);
            }
        }

        path = std::filesystem::path() / "data" / "cmu-name-corpus" / "female_names.txt";
        std::ifstream femaleNamesIFStream(path);
        if (!femaleNamesIFStream) {
            throw std::runtime_error("unable to open female_names.txt");
        }

        while (std::getline(femaleNamesIFStream, line)) {
            if (!line.empty() && line.at(0) != '#') {
                mFemaleNames.emplace_back(line);
            }
        }
    }

    std::vector<std::string> mMaleNames;
    std::vector<std::string> mFemaleNames;
};

} // namespace winda

#endif // PROJECT_WINDA_NAMEGENERATOR_H
