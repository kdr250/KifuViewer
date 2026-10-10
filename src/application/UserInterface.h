#pragma once

#include <SDL3/SDL.h>

class UserInterface {
public:
    void Initilaize(SDL_Window* window, SDL_Renderer* renderer);

    void ProcessEvent(const SDL_Event& event);

    void CreateFrame(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);

    void Cleanup();

private:
    void DisplayTexture(SDL_Renderer* renderer);
};
