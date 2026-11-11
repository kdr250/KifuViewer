#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <string>

#include "shogi/Kifu.h"

class UserInterface {
public:
    void Initilaize(SDL_Window* window, SDL_Renderer* renderer);

    void ProcessEvent(const SDL_Event& event);

    void CreateFrame(SDL_Texture* texture, const std::vector<std::string>& kifuStrings, int currentKifuIndex);
    void Render(SDL_Renderer* renderer);

    void Cleanup();

public:
    std::function<void(void)> mFirstCallback;
    std::function<void(void)> mBackwardCallback;
    std::function<void(void)> mForwardCallback;
    std::function<void(void)> mLastCallback;
    std::function<void(int index)> mKifuChangedCallback;
    std::function<void(std::string)> mPasteKifuCallback;

#ifdef __EMSCRIPTEN__
    std::function<void(void)> mOpenFileDialogCallback;
#else
    std::function<void(std::string)> mSelectFileCallback;

private:
    bool mOpenFileDialog = false;
#endif

private:
    void DisplayTexture(SDL_Texture* texture, const std::vector<std::string>& kifuStrings, int currentKifuIndex);

public:
    inline static std::string kifuStr = std::string();
    inline static bool isPasted = false;
};
