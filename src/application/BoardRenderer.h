#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>

#include "shogi/Shogi.h"

/**
 * 盤を描画
 */
class BoardRenderer {
public:
    void Initialize(SDL_Renderer* renderer, TTF_Font* font);

    SDL_Texture* Render(SDL_Renderer* renderer, TTF_Font* font, const Shogi& shogi, unsigned int w, unsigned int h);

private:
    std::unordered_map<wchar_t, SDL_Texture*> mTextures;
};
