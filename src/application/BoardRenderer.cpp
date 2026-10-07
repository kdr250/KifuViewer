#include "BoardRenderer.h"

void BoardRenderer::Render(SDL_Window* window, SDL_Renderer* renderer, TTF_Text* text)
{
    // FIXME
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    TTF_DrawRendererText(text, 100.0f, 100.0f);
    std::vector<SDL_FPoint> points {
        { .x = 100.0f, .y = 100.0f },
        { .x = 500.0f, .y = 100.0f },
        { .x = 500.0f, .y = 500.0f },
        { .x = 100.0f, .y = 500.0f },
        { .x = 100.0f, .y = 100.0f },
    };
    SDL_RenderLines(renderer, points.data(), points.size());
}
