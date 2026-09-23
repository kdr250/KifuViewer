#include <SDL3/SDL.h>

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    auto window = SDL_CreateWindow("Kifu Viewer", 1024, 768, 0);
    if (!window) {
        SDL_Log("failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    auto renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_Log("failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    isRunning = false;
                    break;

                default:
                    break;
            }
        }

        auto state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_ESCAPE]) {
            isRunning = false;
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
