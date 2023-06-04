#include "winda/TextRenderer.hpp"
#include <filesystem>

using namespace std;
using namespace winda;

TextRenderer::TextRenderer() {
    if (TTF_Init() < 0) {
        spdlog::error("Error initializing SDL_ttf: {}", TTF_GetError());
    }

    auto path = filesystem::path() / "data" / "fonts" / "OpenSans" / "static" /
                "OpenSans-Light.ttf";
    mFont = TTF_OpenFont(filesystem::absolute(path).string().c_str(), 15);
    if (!mFont) {
        spdlog::error("Failed to load font: {}", TTF_GetError());
    }
}

TextRenderer::~TextRenderer() {
    TTF_CloseFont(mFont);
    TTF_Quit();
}

void TextRenderer::renderText(SDL_Renderer* renderer,
                              const std::string& text,
                              int x,
                              int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(mFont, text.c_str(), mTextColor);
    if (!surface) {
        spdlog::error("Failed to render text: {}", TTF_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect src = {0, 0, surface->w, surface->h};
    SDL_Rect dest = {x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, &src, &dest);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
