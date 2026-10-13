#include "BoardRenderer.h"

#include <algorithm>

void BoardRenderer::Initialize(SDL_Renderer* renderer, TTF_Font* font)
{
    std::vector<wchar_t> komaNames = Koma::KomaNames();

    mTextures.clear();
    mTextures.reserve(komaNames.size());

    // Render each character as a surface
    for (size_t i = 0; i < komaNames.size(); ++i) {
        SDL_Surface* textSurface = TTF_RenderGlyph_Blended(font, komaNames[i], SDL_Color { 0, 0, 0, 255 });
        if (!textSurface) {
            std::cerr << "failed to create text surface: " << SDL_GetError() << std::endl;
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        mTextures.emplace(komaNames[i], texture);

        SDL_DestroySurface(textSurface);
    }

    for (int i = 0; i < 9; ++i) {
        std::wstring strNum = std::to_wstring(i);
        SDL_Surface* textSurface = TTF_RenderGlyph_Blended(font, strNum[0], SDL_Color { 0, 0, 0, 255 });
        if (!textSurface) {
            std::cerr << "failed to create text surface: " << SDL_GetError() << std::endl;
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        mTextures.emplace(strNum[0], texture);

        SDL_DestroySurface(textSurface);
    }

    {
        wchar_t x = L'x';
        SDL_Surface* textSurface = TTF_RenderGlyph_Blended(font, x, SDL_Color { 0, 0, 0, 255 });
        if (!textSurface) {
            std::cerr << "failed to create text surface: " << SDL_GetError() << std::endl;
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        mTextures.emplace(x, texture);

        SDL_DestroySurface(textSurface);
    }
}

SDL_Texture* BoardRenderer::Render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, const Shogi& shogi)
{
    int w = 300, h = 200;
    SDL_GetWindowSize(window, &w, &h);

    SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderTarget(renderer, result);

    SDL_SetRenderDrawColor(renderer, 240, 185, 100, 255);
    SDL_FRect rect {
        .x = 0.0f,
        .y = 0.0f,
        .w = (float)w,
        .h = (float)h,
    };
    SDL_RenderFillRect(renderer, &rect);

    // 升目を描画
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    float min = std::min(w, h);
    float size = min * 0.8f / 9.0f;
    float space = size * 0.001f;
    float padding = size + space;
    for (int i = 0; i <= 9; ++i) {
        SDL_RenderLine(renderer, padding, padding + i * size, padding + 9 * size, padding + i * size);
    }
    for (int j = 0; j <= 9; ++j) {
        SDL_RenderLine(renderer, padding + j * size, padding, padding + j * size, padding + 9 * size);
    }

    // 盤上の駒を描画
    float boardHeight = 0.0f;
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

            wchar_t komaName = koma->ToWChar();
            Direction direction = koma->Direction();

            if (direction == Direction::Black) {
                SDL_RenderTexture(renderer, mTextures[komaName], NULL, &area);
            } else {
                SDL_RenderTextureRotated(renderer, mTextures[komaName], NULL, &area, 180.0, NULL, SDL_FlipMode::SDL_FLIP_NONE);
            }

            if (j == 8) {
                boardHeight = area.y;
            }
        }
    }

    // 後手の駒台を描画
    {
        std::wstring komadaiWhite = shogi.ToWStringKomadaiWhite();
        float offset = padding;
        for (wchar_t ch : komadaiWhite) {
            if (ch == ' ') {
                offset += size * 0.1f;
                continue;
            }

            SDL_Texture* texture = mTextures[ch];
            SDL_FRect area { .x = offset, .y = space, .w = size, .h = size };

            if (ch == 'x' || (ch >= L'0' && ch <= L'9')) {
                area.w *= 0.5f;
                area.h *= 0.5f;
                SDL_RenderTexture(renderer, texture, NULL, &area);
            } else {
                SDL_RenderTextureRotated(renderer, texture, NULL, &area, 180.0, NULL, SDL_FlipMode::SDL_FLIP_NONE);
            }

            offset = area.x + area.w + size * 0.1f;
        }
    }

    // 先手の駒台を描画
    {
        std::wstring komadaiBlack = shogi.ToWStringKomadaiBlack();
        float offset = padding;
        for (wchar_t ch : komadaiBlack) {
            if (ch == ' ') {
                offset += size * 0.1f;
                continue;
            }

            SDL_Texture* texture = mTextures[ch];
            SDL_FRect area { .x = offset, .y = boardHeight + padding, .w = size, .h = size };

            if (ch == 'x' || (ch >= L'0' && ch <= L'9')) {
                area.w *= 0.5f;
                area.h *= 0.5f;
            }

            SDL_RenderTexture(renderer, texture, NULL, &area);
            offset = area.x + area.w + size * 0.1f;
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    return result;
}
