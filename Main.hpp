/*
// clang-format off
//
//    Pepega ProStreet Fiddler (Pepega Mod)
//    Copyright (C) 2022 Berkay Yigit <berkaytgy@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program. If not, see <https://www.gnu.org/licenses/>.
//
// clang-format on
*/

#include "pch.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace SpeedPlayground {
  static inline std::deque<std::function<void()>> g_GameLoopActions;

  namespace Implementations {
    namespace details {
      static inline std::uint32_t       sCurImplId     = 1;
      static inline std::uint_least32_t sCustomSleepMS = 0;

      static constexpr inline std::uintptr_t sSleepFn  = 0x64CF00;
      static constexpr inline std::uintptr_t sImpl3Ret = 0x642EDA;
      static __declspec(naked) void Impl3() {
        __asm {
          mov eax, [sCustomSleepMS]
          push eax
          call [sSleepFn]
          add esp, 4
          jmp [sImpl3Ret]
        }
      }
    }  // namespace details

    static void InstallImpl1() {
      // impl2 cleanup
      MemoryEditor::Get().GetRawMemory(0x925854).SetValue(false);
      MemoryEditor::Get().GetRawMemory(0x663ECD).SetValue<std::array<std::uint8_t, 2>>({0x75, 0x05});
      MemoryEditor::Get().GetRawMemory(0x6F5919).SetValue<std::array<std::uint8_t, 7>>({0xC6, 0x05, 0x54, 0x58, 0x92, 0x00, 0x00});
      // impl3 cleanup
      MemoryEditor::Get().GetRawMemory(0x642EB1).SetValue<std::array<std::uint8_t, 5>>({0xD9, 0x44, 0x24, 0x0C, 0xD8});
      details::sCurImplId = 1;
    }
    static void InstallImpl2() {
      InstallImpl1();
      MemoryEditor::Get().GetRawMemory(0x925854).SetValue(true);
      MemoryEditor::Get().Make(MemoryEditor::MakeType::NOP, 0x663ECD, 0x663ECF);
      MemoryEditor::Get().Make(MemoryEditor::MakeType::NOP, 0x6F5919, 0x6F5920);
      details::sCurImplId = 2;
    }
    static void InstallImpl3() {
      InstallImpl1();
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x642EB1, reinterpret_cast<std::uintptr_t>(&details::Impl3));
      details::sCurImplId = 3;
    }
  }  // namespace Implementations

  namespace Overlay {
    void ScaleImGui(LPDIRECT3DDEVICE9 pDevice) {
      if (auto* imgui = ImGui::GetCurrentContext()) {
        float scale = 1.0f;

        D3DVIEWPORT9 v = {0};
        if (pDevice->GetViewport(&v) == D3D_OK) scale = std::max(0.9f, v.Height / 1080.0f);  // 1080p as base

        imgui->IO.Fonts->Clear();
        imgui->IO.Fonts->AddFontDefault();
        imgui->IO.Fonts->Build();

        imgui->Style.ScaleAllSizes(scale);
      }
    }

    /// HOOKS

    static HRESULT __stdcall BeginScene(LPDIRECT3DDEVICE9) {
      if (::GetForegroundWindow() != WndProcWalker::Get().GetWindowHandle()) return D3D_OK;
      if (ImGui::GetCurrentContext()->WithinFrameScope) return D3D_OK;

      ImGui_ImplDX9_NewFrame();
      ImGui_ImplWin32_NewFrame();
      ImGui::NewFrame();
      return D3D_OK;
    }
    static HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice) {
      if (!ImGui::GetCurrentContext()->WithinFrameScope) return D3D_OK;

      ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos, ImGuiCond_Once);
      if (ImGui::Begin("SpeedPlayground"), nullptr, ImGuiWindowFlags_AlwaysAutoResize) {
        if (ImGui::BeginTabBar("##TabMain")) {
          if (ImGui::BeginTabItem("Custom Frame Sleep Interval")) {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.1f, 1.0f), "Framerate %.1f", ImGui::GetIO().Framerate);
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.1f, 1.0f), "Currently running implementation %" PRIu32, Implementations::details::sCurImplId);

            ImGui::TextWrapped("- Implementation 1 is stock behavior.");
            ImGui::TextWrapped("- Implementation 2 removes the forced sleep entirely.");
            ImGui::TextWrapped("- Implementation 3 lets you set a custom sleep interval.");
            ImGui::TextWrapped(
                "NOTE: Implementation 3 with 0ms will be way more enjoyable than implementation 2. This is because implementation 2 sets a debug variable left "
                "in the game and implementation 3 only forces 0ms sleep.");

            if (ImGui::BeginTabBar("##TabCustomFrameSleepInterval")) {
              if (ImGui::BeginTabItem("Implementation 1")) {
                if (ImGui::Button("Enable")) g_GameLoopActions.push_back([]() { Implementations::InstallImpl1(); });
                ImGui::EndTabItem();
              }

              if (ImGui::BeginTabItem("Implementation 2")) {
                if (ImGui::Button("Enable")) g_GameLoopActions.push_back([]() { Implementations::InstallImpl2(); });
                ImGui::EndTabItem();
              }

              if (ImGui::BeginTabItem("Implementation 3")) {
                static std::uint_least32_t sMin = 0;
                static std::uint_least32_t sMax = 100;

                if (ImGui::Button("Enable")) g_GameLoopActions.push_back([]() { Implementations::InstallImpl3(); });
                ImGui::TextUnformatted("Custom Sleep Time (in milliseconds): ");
                ImGui::SameLine();
                ImGui::SliderScalar("##CustomSleepTimeMS", ImGuiDataType_U32, &Implementations::details::sCustomSleepMS, &sMin, &sMax, "%" PRIu32);
                ImGui::EndTabItem();
              }

              ImGui::EndTabBar();
            }

            ImGui::EndTabItem();
          }

          if (ImGui::BeginTabItem("Hasher")) {
            static char          temp_array[256] = {0};
            static std::uint32_t hash            = 0;
            ImGui::InputText("Text", temp_array, 255);
            if (ImGui::Button("stringhash32()")) hash = MW::Game::stringhash32(temp_array);
            ImGui::SameLine();
            if (ImGui::Button("bStringHash()")) hash = MW::Game::bStringHash(temp_array);
            ImGui::SameLine();
            if (ImGui::Button("Attrib::StringToKey()")) hash = MW::Attrib::StringToKey(temp_array);

            std::string str_hash = std::format("0x{:08X}", hash);
            ImGui::InputText("Hash", const_cast<char*>(str_hash.c_str()), str_hash.size(), ImGuiInputTextFlags_ReadOnly);

            ImGui::EndTabItem();
          }

          ImGui::EndTabBar();
        }
      }
      ImGui::End();

      ImGui::GetIO().MouseDrawCursor = ImGui::GetIO().WantCaptureMouse;
      ImGui::Render();
      ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
      return D3D_OK;
    }
    static HRESULT __stdcall BeforeReset(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*) {
      ImGui_ImplDX9_InvalidateDeviceObjects();
      return D3D_OK;
    }
    static HRESULT __stdcall AfterReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS*) {
      ScaleImGui(pDevice);
      ImGui_ImplDX9_CreateDeviceObjects();
      return D3D_OK;
    }

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
      ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

      switch (uMsg) {
        case WM_MOUSEMOVE:
        case WM_MOUSELEAVE:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
          return ImGui::GetIO().WantCaptureMouse;
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
          return ImGui::GetIO().WantCaptureKeyboard;
      }
      return FALSE;
    }

    static inline void Init() {
      ImGui::CreateContext();
      ImGui_ImplWin32_Init(WndProcWalker::Get().GetWindowHandle());
      ImGui_ImplDX9_Init(DirectXWalker::Get().GetDevice());
      ScaleImGui(DirectXWalker::Get().GetDevice());

      DirectXWalker::Get().SetBeginScene(&BeginScene);
      DirectXWalker::Get().SetEndScene(&EndScene);
      DirectXWalker::Get().SetBeforeReset(&BeforeReset);
      DirectXWalker::Get().SetAfterReset(&AfterReset);

      WndProcWalker::Get().AddWndProc(&WndProc);
    }

  }  // namespace Overlay

  static void Init() {
    auto info = NFSPluginSDK::GetInformationOfCurrentGame();
    if (info.mGame != NFSPluginSDK::Game::MW05) return;

    DirectXWalker::Get().Init(info.mGame);
    GameLoopWalker::Get().Init(info.mGame);
    GameLoopWalker::Get().SetFn([]() {
      if (!g_GameLoopActions.empty()) {
        g_GameLoopActions.front()();
        g_GameLoopActions.pop_front();
      }
    });

    std::thread([info]() {
      WndProcWalker::Get().Init(reinterpret_cast<HWND*>(info.mPHwnd));
      Overlay::Init();
    }).detach();
  }
}  // namespace SpeedPlayground