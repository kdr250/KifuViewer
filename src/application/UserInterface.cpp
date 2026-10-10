#include "UserInterface.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <SDL3_image/SDL_image.h>

#include <string>

void UserInterface::Initilaize(SDL_Window* window, SDL_Renderer* renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void UserInterface::ProcessEvent(const SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void UserInterface::CreateFrame(SDL_Renderer* renderer)
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    DisplayTexture(renderer);
}

void UserInterface::Render(SDL_Renderer* renderer)
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void UserInterface::Cleanup()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

// FIXME
SDL_Texture* LoadTexture(const std::string& path, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
        SDL_Log("Failed to load texture file: %s", path.c_str());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create SDL texture: %s", SDL_GetError());
    }

    SDL_DestroySurface(surface);

    return texture;
}

SDL_Texture* texture = nullptr;

void UserInterface::DisplayTexture(SDL_Renderer* renderer)
{
    // FIXME
    if (texture == nullptr) {
        texture = LoadTexture("resources/texture/red.png", renderer);
        if (!texture) {
            return;
        }
    }

    ImGui::Begin("SDL_Renderer Texture Test");
    ImGui::Text("pointer = %p", texture);
    ImGui::Text("size = %d x %d", texture->w, texture->h);
    ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2((float)texture->w * 10.0f, (float)texture->h * 10.0f));
    ImGui::End();
}
