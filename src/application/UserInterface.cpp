#include "UserInterface.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#ifndef __EMSCRIPTEN__
#include <ImGuiFileDialog.h>
#endif

#include <string>

void UserInterface::Initilaize(SDL_Window* window, SDL_Renderer* renderer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/font/NotoSans/NotoSansJP-Light.ttf", 18.0f);
    io.IniFilename = "resources/ui/imgui.ini";

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
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("FullScreenWindow", nullptr, flags);
    ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2((float)texture->w, (float)texture->h));
    ImGui::SameLine();
    if (ImGui::Button("|<", { 50, 30 })) {
        mFirstCallback();
    }
    ImGui::SameLine();
    if (ImGui::Button("<", { 50, 30 })) {
        mBackwardCallback();
    }
    ImGui::SameLine();
    if (ImGui::Button(">", { 50, 30 })) {
        mForwardCallback();
    }
    ImGui::SameLine();
    if (ImGui::Button(">|", { 50, 30 })) {
        mLastCallback();
    }

    if (ImGui::Button("開く", { 100, 50 })) {
#ifdef __EMSCRIPTEN__
        mOpenFileDialogCallback();
#else
        mOpenFileDialog = true;
#endif
    }

#ifndef __EMSCRIPTEN__
    if (mOpenFileDialog) {
        auto io = ImGui::GetIO();
        IGFD::FileDialogConfig config;
        config.path = "./resources/kifu";
        config.countSelectionMax = 1;
        config.flags = ImGuiFileDialogFlags_Modal;

        ImGui::SetNextWindowPos(
            ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
            ImGuiCond_Always,
            ImVec2(0.5f, 0.5f));

        ImGuiFileDialog::Instance()->OpenDialog("LoadKifuFile", "棋譜ファイルを選択", ".kif,.kifu", config);

        if (ImGuiFileDialog::Instance()->Display("LoadKifuFile")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                mSelectFileCallback(filePathName);
            }
            mOpenFileDialog = false;
            ImGuiFileDialog::Instance()->Close();
        }
    }
#endif

    ImGui::End();

    ImGui::PopStyleVar(2);
}
