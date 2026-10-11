#include "UserInterface.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

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

void UserInterface::CreateFrame(SDL_Texture* texture)
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    DisplayTexture(texture);
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

void UserInterface::DisplayTexture(SDL_Texture* texture)
{
    ImGui::Begin("SDL_Renderer Texture Test");
    ImGui::Text("pointer = %p", texture);
    ImGui::Text("size = %d x %d", texture->w, texture->h);
    ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2((float)texture->w, (float)texture->h));
    ImGui::End();
}
