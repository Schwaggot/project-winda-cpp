#ifndef PROJECT_WINDA_TEXTRENDERER_HPP
#define PROJECT_WINDA_TEXTRENDERER_HPP

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "spdlog/spdlog.h"
#include <string>

namespace winda {

class TextRenderer {
public:
    static TextRenderer& getInstance() {
        static TextRenderer instance; // Guaranteed to be destroyed.
                                      // Instantiated on first use.
        return instance;
    }

    TextRenderer(TextRenderer const&) = delete;
    void operator=(TextRenderer const&) = delete;

    void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y);

private:
    TextRenderer();
    ~TextRenderer();

    TTF_Font* mFont;
    SDL_Color mTextColor = {0xF2, 0xF5, 0xF4, 255};
};

} // namespace winda

#endif // PROJECT_WINDA_TEXTRENDERER_HPP
