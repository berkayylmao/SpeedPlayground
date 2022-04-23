#include "pch.h"
#include "OpenMW.h"

__DISABLE_VC_WARNINGS__()
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
__RESTORE_VC_WARNINGS__()

namespace SpeedPlayground {
  namespace AttemptToIncreaseCarLimit {
    struct testclass {
      std::uint32_t                                                            vfptr;
      OpenMW::UTL::ListableSet<OpenMW::IVehicle, 64, OpenMW::eVehicleList, 10> data;
    };
    static testclass overrideclass;

    static void debug() {
      ::AllocConsole();
      ::_CrtSetDbgFlag(::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);

      switch (OpenSpeed::GetCurrentSpeedGame()) {
        case OpenSpeed::SpeedGame::MW05: {
          // SkipFE
          MemoryEditor::Get().UnlockMemory(0x926064, 4);
          *reinterpret_cast<bool*>(0x926064) = true;
          MemoryEditor::Get().LockMemory(0x926064);
          // enable release printf
          MemoryEditor::Get().UnlockMemory(0x90E630, 4);
          *reinterpret_cast<bool*>(0x90E630) = true;
          MemoryEditor::Get().LockMemory(0x90E630);

          static std::vector<std::uintptr_t> size_limits = {
              // 0x67AEB0,  // default initializer for UTL::Collections::ListableSet<IVehicle,10,eVehicleList,10>::_mLists
              // 0x67E9DA,  // default initializer for UTL::Collections::ListableSet<IVehicle,10,eVehicleList,10>::_mLists
              // 0x67ECCA,  // ???
              // 0x424501, 0x424511, // vfptr to ListableSet
              // 0x41EC15, // AITrafficManager::NeedsTraffic
              // 0x426332,  // AITrafficManager::NextSpawn
              // 0x674BD3, // FastMem, alloc 0x14 and set to 0
              // 0x675723, // FastMem, alloc 0x14, set to 0 and copy some data
              // 0x683DB5,  // PVehicle::CountResources
              // 0x683DCA,  // PVehicle::CountResources
              // 0x687855,  // PVehicle::MakeRoom
              // 0x679801,  // UTL::FixedVector<PVehicle::ManageNode, 10, 16>::GetGrowSize
              // 0x679811,  // UTL::FixedVector<PVehicle::ManageNode, 10, 16>::GetMaxCapacity
              0x687819  // PVehicle::MakeRoom, compare if more than 20 cars, and try to remove some if it is
          };
          for (auto addr : size_limits) {
            MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint8_t));
            *reinterpret_cast<std::uint8_t*>(addr) = (std::uint8_t)64;
            MemoryEditor::Get().LockMemory(addr);
          }

          reinterpret_cast<void(__stdcall*)(void*, std::uint32_t, std::int32_t, std::uintptr_t, std::uintptr_t)>(0x7C90A0)(&overrideclass, 0x60, 64, 0x430910,
                                                                                                                           0x430930);

          std::uintptr_t loop   = reinterpret_cast<std::uintptr_t>(&overrideclass);
          std::int32_t   amount = 64;
          do {
            reinterpret_cast<void(__thiscall*)(std::uintptr_t, std::uint32_t)>(0x41AE90)(loop, 64);
            loop += 0x60;
            --amount;
          } while (amount);

          static std::vector<std::uintptr_t> direct_mlist_references = {
              0x40B5CB, 0x41D2C9, 0x41D309, 0x42537B, 0x4254E9, 0x425532, 0x425574, 0x4255B9, 0x4790EC, 0x57A143, 0x60CF0B, 0x610252, 0x67AC39, 0x67AEA4,
              0x67DC7E, 0x67DC93, 0x67DCB4, 0x67E9CE, 0x67ECBE, 0x686604, 0x686617, 0x6893BC, 0x6893C3, 0x6893CC, 0x70641F, 0x8870B1, 0x88E971};
          for (auto addr : direct_mlist_references) {
            MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uintptr_t));
            *reinterpret_cast<std::uintptr_t*>(addr) = reinterpret_cast<std::uintptr_t>(&overrideclass);
            MemoryEditor::Get().LockMemory(addr);
          }

          static std::vector<std::uintptr_t> mlist_plus4_references = {0x410A6D, 0x410AB6, 0x410F9A, 0x411038, 0x41A05C,
                                                                       0x41A148, 0x47A934, 0x6614C5, 0x6614DC, 0x6893D6};
          for (auto addr : mlist_plus4_references) {
            MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uintptr_t));
            *reinterpret_cast<std::uintptr_t*>(addr) = reinterpret_cast<std::uintptr_t>(&overrideclass) + 4;
            MemoryEditor::Get().LockMemory(addr);
          }

          static std::vector<std::uintptr_t> mlist_plus8_references = {0x6893B4};
          for (auto addr : mlist_plus8_references) {
            MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uintptr_t));
            *reinterpret_cast<std::uintptr_t*>(addr) = reinterpret_cast<std::uintptr_t>(&overrideclass) + 8;
            MemoryEditor::Get().LockMemory(addr);
          }

          static std::vector<std::uintptr_t> mlist_plus12_references = {0x40DFBC, 0x410A66, 0x410ABC, 0x410F92, 0x41103E, 0x41A062,
                                                                        0x41A14E, 0x41EC0D, 0x42632C, 0x47A923, 0x6614BE, 0x6614F1,
                                                                        0x6877F4, 0x6893AE, 0x6893DC, 0x6893EB, 0x6893F4};
          for (auto addr : mlist_plus12_references) {
            MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uintptr_t));
            *reinterpret_cast<std::uintptr_t*>(addr) = reinterpret_cast<std::uintptr_t>(&overrideclass) + 12;
            MemoryEditor::Get().LockMemory(addr);
          }

          break;
        }
        case OpenSpeed::SpeedGame::Carbon:
          // SkipFE
          MemoryEditor::Get().UnlockMemory(0xA9E620, 4);
          *reinterpret_cast<bool*>(0xA9E620) = true;
          MemoryEditor::Get().LockMemory(0xA9E620);
          break;
      }
    }
  }  // namespace AttemptToIncreaseCarLimit

  namespace d3d9 {
    static bool sIsMenuVisible = true;

    static void __stdcall BeginScene(LPDIRECT3DDEVICE9) {
      ImGui_ImplDX9_NewFrame();
      ImGui_ImplWin32_NewFrame();
      ImGui::NewFrame();
    }
    static void __stdcall EndScene(LPDIRECT3DDEVICE9) {
      if (!ImGui::GetCurrentContext()->WithinFrameScope) return;
      const ImGuiViewport* viewport = ImGui::GetMainViewport();

      if (sIsMenuVisible) {
        ImGui::SetNextWindowPos(viewport->Pos + ImVec2(8.0f, 8.0f), ImGuiCond_Once);
        if (ImGui::Begin("Speed Playground", &sIsMenuVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
          auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
          ImGui::Text("Player PVehicle: %08X", pvehicle);
          ImGui::Text("Car capacity: %d", AttemptToIncreaseCarLimit::overrideclass.data.mSet._buckets->mCapacity);
          ImGui::Text("Car count: %d", AttemptToIncreaseCarLimit::overrideclass.data.mSet._buckets->mSize);
          if (ImGui::Button("Spawn car") && pvehicle) {
            OpenMW::UMath::Vector3 direction;
            pvehicle->GetRigidBody()->GetForwardVector(direction);
            OpenMW::PVehicle::Construct(OpenMW::VehicleParams(OpenMW::DriverClass::None, OpenMW::Attrib::StringToKey("copgto"), direction,
                                                              pvehicle->GetPosition() + (direction * 5.0f)));
          }
        }
        ImGui::End();
      }

      ImGui::GetIO().MouseDrawCursor = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
      ImGui::Render();
      ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
    static void __stdcall BeforeReset(LPDIRECT3DDEVICE9, void*) { ImGui_ImplDX9_InvalidateDeviceObjects(); }
    static void __stdcall AfterReset(LPDIRECT3DDEVICE9 pDevice, void*) { ImGui_ImplDX9_CreateDeviceObjects(); }

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
      if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return TRUE;
      if (uMsg == WM_KEYUP && wParam == VK_F10 && (!ImGui::GetIO().WantCaptureKeyboard || !ImGui::GetIO().WantTextInput)) sIsMenuVisible = !sIsMenuVisible;

      return MirrorHook::WndProc::g_constIgnoreThisReturn;
    }

    static void hook() {
      LPDIRECT3DDEVICE9 d3d = nullptr;
      // Wait for D3D9 device
      {
        auto** p = reinterpret_cast<LPDIRECT3DDEVICE9*>(OpenSpeed::GetInformationOfCurrentSpeedGame().ppD3DDevice);
        while (!d3d) {
          d3d = *p;
          std::this_thread::sleep_for(1s);
        }
      }
      D3DDEVICE_CREATION_PARAMETERS params;
      d3d->GetCreationParameters(&params);

      // Set up MirrorHook
      // Set Up Dear ImGui
      {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        auto& io = ImGui::GetIO();

        io.ConfigWindowsResizeFromEdges = false;
        io.FontDefault                  = NULL;
        io.IniFilename                  = NULL;
        ImGui_ImplWin32_Init(params.hFocusWindow);
        ImGui_ImplDX9_Init(d3d);
      }

      // Hook via MirrorHook
      {
        MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::BeginScene, &SpeedPlayground::d3d9::BeginScene);
        MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::EndScene, &SpeedPlayground::d3d9::EndScene);
        MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::BeforeReset, &SpeedPlayground::d3d9::BeforeReset);
        MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::AfterReset, &SpeedPlayground::d3d9::AfterReset);

        MirrorHook::WndProc::AddExtension(&SpeedPlayground::d3d9::WndProc);
      }
    }
  }  // namespace d3d9
  static void Init() {
    d3d9::hook();
    AttemptToIncreaseCarLimit::debug();
  }

}  // namespace SpeedPlayground

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);
    std::thread(SpeedPlayground::Init).detach();
  }
  return TRUE;
}
