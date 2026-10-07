#include "BoardRenderer.h"

#include <algorithm>

void BoardRenderer::Render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font)
{
    // FIXME
    SDL_SetRenderDrawColor(renderer, 240, 185, 100, 255);
    SDL_FRect rect {
        .x = 90.0f,
        .y = 90.0f,
        .w = 710.0f,
        .h = 710.0f,
    };
    SDL_RenderFillRect(renderer, &rect);

    // 升目を描画
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    float padding = 100.0f + 30.0f;
    float size = 600.0f / 9.0f;
    for (int i = 0; i <= 9; ++i) {
        SDL_RenderLine(renderer, padding, padding + i * size, padding + 9 * size, padding + i * size);
    }
    for (int j = 0; j <= 9; ++j) {
        SDL_RenderLine(renderer, padding + j * size, padding, padding + j * size, padding + 9 * size);
    }

    // 盤上の駒を描画
    Shogi shogi;
    const auto& masume = shogi.GetMasume();
    for (int i = 8; i >= 0; --i) {
        for (int j = 0; j <= 8; ++j) {
            KomaRef koma = masume[j][i];
            if (koma == nullptr) {
                continue;
            }
            float posX = padding + (8 - i) * size;
            float posY = padding + j * size;

            // FIXME: See https://glusoft.com/sdl3-tutorials/display-unicode-texts-sdl3-ttf/
            SDL_Surface* surace = TTF_RenderText_Blended(font, "あ", 2, SDL_Color { .r = 0, .g = 0, .b = 0, .a = 255 });
        }
    }
}
