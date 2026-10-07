#include "BoardRenderer.h"

#include <algorithm>

void BoardRenderer::Render(SDL_Window* window, SDL_Renderer* renderer, TTF_Text* text)
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    float padding = 100.0f + 10.0f;
    float size = 600.0f / 9.0f;
    for (int i = 0; i < 10; ++i) {
        SDL_RenderLine(renderer, padding, padding + i * size, padding + 9 * size, padding + i * size);
    }
    for (int j = 0; j < 10; ++j) {
        SDL_RenderLine(renderer, padding + j * size, padding, padding + j * size, padding + 9 * size);
    }
}
