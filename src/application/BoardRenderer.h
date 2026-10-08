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

    void Render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);

private:
    std::unordered_map<std::wstring, SDL_Texture*> mKomaTextures;
};
