#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "shogi/Shogi.h"

/**
 * 盤を描画
 */
class BoardRenderer {
public:
    void Render(SDL_Window* window, SDL_Renderer* renderer, TTF_Text* text);
};
