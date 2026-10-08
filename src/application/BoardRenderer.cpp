#include "BoardRenderer.h"

#include <algorithm>

void BoardRenderer::Initialize(SDL_Renderer* renderer, TTF_Font* font)
{
    std::vector<std::wstring> komaNames = Koma::KomaNames();

    mKomaTextures.clear();
    mKomaTextures.reserve(komaNames.size());

    // Render each character as a surface
    for (size_t i = 0; i < komaNames.size(); ++i) {
        SDL_Surface* textSurface = TTF_RenderGlyph_Blended(font, komaNames[i][0], SDL_Color { 0, 0, 0, 255 });
        if (!textSurface) {
            std::cerr << "failed to create text surface: " << SDL_GetError() << std::endl;
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        mKomaTextures.emplace(komaNames[i], texture);

        SDL_DestroySurface(textSurface);
    }
}

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
            SDL_FRect area {
                .x = padding + (8 - i) * size,
                .y = padding + j * size,
                .w = size,
                .h = size,
            };

            std::wstring komaName = koma->ToWString();
            Direction direction = koma->Direction();

            if (direction == Direction::Black) {
                SDL_RenderTexture(renderer, mKomaTextures[komaName], NULL, &area);
            } else {
                SDL_FPoint center {
                    .x = area.x + area.w / 2.0f,
                    .y = area.y + area.h / 2.0f,
                };
                SDL_RenderTextureRotated(renderer, mKomaTextures[komaName], NULL, &area, 180.0, NULL, SDL_FlipMode::SDL_FLIP_NONE);
            }
        }
    }
}
