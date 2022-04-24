#include "pch.h"
#include "OpenMW.h"

__DISABLE_VC_WARNINGS__()
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
__RESTORE_VC_WARNINGS__()

namespace SpeedPlayground {
  namespace AttemptToIncreaseIVehicleLimit {
    static constexpr size_t                                                               newLimit = 40;
    static OpenMW::UTL::ListableSet<OpenMW::IVehicle, newLimit, OpenMW::eVehicleList, 10> newList;

    namespace details {
      static auto* hk40B5C0(OpenMW::eVehicleList idx) { return &newList.mSet[idx]; }
      static auto  hk41D2B0(void* a1, std::size_t idx, void* a3, void* a4) {
        reinterpret_cast<void*(__cdecl*)(void*, void*, void*, void*, void*)>(0x40ED50)(a1, newList.mSet[idx].mBegin,
                                                                                       newList.mSet[idx].mBegin + 4 * newList.mSet[idx].mSize, a3, a4);
        return a1;
      }
      static auto hk41D2F0(void* a1, std::size_t idx, void* a3, void* a4) {
        reinterpret_cast<void*(__cdecl*)(void*, void*, void*, void*, void*)>(0x40EDD0)(a1, newList.mSet[idx].mBegin,
                                                                                       newList.mSet[idx].mBegin + 4 * newList.mSet[idx].mSize, a3, a4);
        return a1;
      }
      static auto hk425370(OpenMW::eVehicleList idx) {
        auto& bucket = newList.mSet[idx];
        void* ret    = nullptr;
        if (bucket.mSize > 0) ret = bucket.mBegin;
        return ret;
      }
      static auto hk4254C0(void* a1, std::size_t idx, void* a3, void* a4, void* a5, void* a6) {
        reinterpret_cast<void*(__cdecl*)(void*, void*, void*, void*, void*, void*, void*)>(0x41DA00)(
            a1, newList.mSet[idx].mBegin, newList.mSet[idx].mBegin + 4 * newList.mSet[idx].mSize, a3, a4, a5, a6);
        return a1;
      }
      static auto hk425510(void* a1, std::size_t idx, void* a3, void* a4, void* a5) {
        reinterpret_cast<void*(__cdecl*)(void*, void*, void*, void*, void*, void*)>(0x41DAD0)(
            a1, newList.mSet[idx].mBegin, newList.mSet[idx].mBegin + 4 * newList.mSet[idx].mSize, a3, a4, a5);
        return a1;
      }
      static auto hk425560(void* a1, std::size_t idx, void* a3) {
        reinterpret_cast<void*(__cdecl*)(void*, void*, void*, void*)>(0x41DB60)(a1, newList.mSet[idx].mBegin,
                                                                                newList.mSet[idx].mBegin + 4 * newList.mSet[idx].mSize, a3);
        return a1;
      }
      static constexpr std::uintptr_t                       hk4790E4_jmpback = 0x4790F0;
      static std::size_t                                    hk4790E4_idx     = 0;
      static OpenMW::UTL::List<OpenMW::IVehicle, newLimit>* hk4790E4_ptr     = nullptr;
      static void __declspec(naked) hk4790E4() {
        _asm mov hk4790E4_idx, eax;
        _asm pushad;
        hk4790E4_ptr = &newList.mSet[hk4790E4_idx];
        _asm popad;
        _asm {
          // eax is idx
          // edx should be list ptr
          mov edx, hk4790E4_ptr
          jmp [hk4790E4_jmpback]
        }
      }
      static constexpr std::uintptr_t                       hk57A13B_jmpback = 0x57A147;
      static std::size_t                                    hk57A13B_idx     = 0;
      static OpenMW::UTL::List<OpenMW::IVehicle, newLimit>* hk57A13B_ptr     = nullptr;
      static void __declspec(naked) hk57A13B() {
        _asm mov hk57A13B_idx, edi;
        _asm pushad;
        hk57A13B_ptr = &newList.mSet[hk57A13B_idx];
        _asm popad;
        _asm {
          // edi is idx
          // edi should be list ptr
          // can use esi and eax freely
          mov edi, hk57A13B_ptr
          jmp [hk57A13B_jmpback]
        }
      }
      static constexpr std::uintptr_t                       hk60CF04_jmpback = 0x60CF0F;
      static std::size_t                                    hk60CF04_idx     = 0;
      static OpenMW::UTL::List<OpenMW::IVehicle, newLimit>* hk60CF04_ptr     = nullptr;
      static void __declspec(naked) hk60CF04() {
        _asm mov hk60CF04_idx, eax;
        _asm pushad;
        hk60CF04_ptr = &newList.mSet[hk60CF04_idx];
        _asm popad;
        _asm {
          // eax is idx
          // eax should be list ptr
          mov eax, hk60CF04_ptr
          jmp [hk60CF04_jmpback]
        }
      }
      static auto hk610230(void* a1, std::size_t idx, void* a3, void* a4, void* a5) {
        reinterpret_cast<void*(__cdecl*)(void*, void*, void*, void*, void*, void*)>(0x60D580)(
            a1, newList.mSet[idx].mBegin, newList.mSet[idx].mBegin + 4 * newList.mSet[idx].mSize, a3, a4, a5);
        return a1;
      }
      static constexpr std::uintptr_t                       hk67AC31_jmpback = 0x67AC3D;
      static std::size_t                                    hk67AC31_idx     = 0;
      static OpenMW::UTL::List<OpenMW::IVehicle, newLimit>* hk67AC31_ptr     = nullptr;
      static void __declspec(naked) hk67AC31() {
        _asm mov hk67AC31_idx, eax;
        _asm pushad;
        hk67AC31_ptr = &newList.mSet[hk67AC31_idx];
        _asm popad;
        _asm {
          // eax is idx
          // esi should be list ptr
          mov esi, hk67AC31_ptr
          jmp [hk67AC31_jmpback]
        }
      }
      static constexpr std::uintptr_t                       hk67AD46_jmpback = 0x67AD52;
      static std::size_t                                    hk67AD46_idx     = 0;
      static OpenMW::UTL::List<OpenMW::IVehicle, newLimit>* hk67AD46_ptr     = nullptr;
      static void __declspec(naked) hk67AD46() {
        _asm mov hk67AD46_idx, eax;
        _asm pushad;
        hk67AD46_ptr = &newList.mSet[hk67AD46_idx];
        _asm popad;
        _asm {
          // ecx is list ptr
          // ecx is saved to edx
          // eax is idx
          // ecx should be list ptr
          // eax should be list.mBegin ptr
          mov ecx, hk67AD46_ptr
          mov eax, [ecx+4]
          jmp [hk67AD46_jmpback]
        }
      }
      static constexpr std::uintptr_t                       hk706418_jmpback = 0x706423;
      static std::size_t                                    hk706418_idx     = 0;
      static OpenMW::UTL::List<OpenMW::IVehicle, newLimit>* hk706418_ptr     = nullptr;
      static void __declspec(naked) hk706418() {
        _asm mov hk706418_idx, eax;
        _asm pushad;
        hk706418_ptr = &newList.mSet[hk706418_idx];
        _asm popad;
        _asm {
          // eax is idx
          // DO NOT USE EDX
          // eax should be list ptr
          // can use ecx freely
          mov eax, hk706418_ptr
          jmp [hk706418_jmpback]
        }
      }
    }  // namespace details

    template <typename T>
    static void SetAddressTo(std::uintptr_t addr, const T& value) {
      DWORD _old;
      VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(T), PAGE_EXECUTE_READWRITE, &_old);
      *reinterpret_cast<T*>(addr) = value;
    }

    static void debug() {
      // reinterpret_cast<void(__stdcall*)(void*, std::uint32_t, std::int32_t, std::uintptr_t, std::uintptr_t)>(0x7C90A0)(&newList, 0x60, 20, 0x430910,
      // 0x430930);

      // std::uintptr_t loop   = reinterpret_cast<std::uintptr_t>(&newList);
      // std::int32_t   amount = 20;
      // do {
      //   reinterpret_cast<void(__thiscall*)(std::uintptr_t, std::uint32_t)>(0x41AE90)(loop, newLimit);
      //   loop += 0x60;
      //   --amount;
      // } while (amount);

      // mLists[All]
      static std::vector<std::uintptr_t> mlists_refs = {0x67AEA4, 0x67DC7E, 0x67DC93, 0x67DCB4, 0x67E9CE, 0x67ECBE, 0x686604,
                                                        0x686617, 0x6893BC, 0x6893C3, 0x6893CC, 0x8870B1, 0x88E971};
      for (auto addr : mlists_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::All]);
      // MLists[All]::mBegin
      std::vector<std::uintptr_t> mlists_all_begin_refs = {0x410A6D, 0x410AB6, 0x410F9A, 0x411038, 0x41A05C, 0x41A148, 0x47A934, 0x6614C5, 0x6614DC, 0x6893D6};
      for (auto addr : mlists_all_begin_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::All].mBegin);
      // MLists[All]::mCapacity
      std::vector<std::uintptr_t> mlists_all_capacity_refs = {0x6893B4};
      for (auto addr : mlists_all_capacity_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::All].mCapacity);
      // MLists[All]::mSize
      std::vector<std::uintptr_t> mlists_all_size_refs = {0x40DFBC, 0x410A66, 0x410ABC, 0x410F92, 0x41103E, 0x41A062, 0x41A14E, 0x41EC0D, 0x42632C,
                                                          0x47A923, 0x6614BE, 0x6614F1, 0x6877F4, 0x6893AE, 0x6893DC, 0x6893EB, 0x6893F4};
      for (auto addr : mlists_all_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::All].mSize);

      // MLists[Players]::mBegin
      std::vector<std::uintptr_t> mlists_players_begin_refs = {
          0x41991B, 0x419987, 0x4220A0, 0x4284FE, 0x42859A, 0x428607, 0x4286E8, 0x429511, 0x42C3C6, 0x42C732, 0x42F593, 0x42F5AF, 0x44D780, 0x44DA35,
          0x44DCD2, 0x47FC84, 0x61DC4F, 0x61DDC8, 0x641E55, 0x641EFB, 0x6EEF51, 0x6EEF8F, 0x6EEFAD, 0x6EEFEB, 0x6EF228, 0x6EF23F, 0x75547A, 0x7555B9};
      for (auto addr : mlists_players_begin_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Players].mBegin);
      // MLists[Players]::mSize
      std::vector<std::uintptr_t> mlists_players_size_refs = {
          0x419912, 0x41998D, 0x4220AB, 0x42850F, 0x4285A3, 0x428600, 0x4286E2, 0x429508, 0x42C3B7, 0x42C727, 0x42F58C, 0x42F5B5, 0x44D771, 0x44DA1F,
          0x44DCC6, 0x47FC76, 0x61DC54, 0x61DDD1, 0x641E44, 0x641EE6, 0x6EEF56, 0x6EEF94, 0x6EEFB2, 0x6EEFF0, 0x6EF221, 0x6EF245, 0x75546D, 0x7555AC};
      for (auto addr : mlists_players_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Players].mSize);

      // MLists[AIRacers]::mBegin
      std::vector<std::uintptr_t> mlists_airacers_begin_refs = {0x720E2D, 0x720E86};
      for (auto addr : mlists_airacers_begin_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::AIRacers].mBegin);
      // MLists[AIRacers]::mSize
      std::vector<std::uintptr_t> mlists_airacers_size_refs = {0x4E5CC4, 0x4F3002,
                                                               //
                                                               /* byte ptr-> */ 0x720E21,
                                                               //
                                                               0x720E33, 0x720E80};
      for (auto addr : mlists_airacers_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::AIRacers].mSize);

      // MLists[AICops]::mBegin
      std::vector<std::uintptr_t> mlists_aicops_begin_refs = {0x470A84, 0x470BC7, 0x47292B, 0x472B9F, 0x4744BA, 0x474537, 0x47517A, 0x475300,
                                                              0x47A514, 0x47A558, 0x53107F, 0x531309, 0x579E6B, 0x57A0A1, 0x6410ED, 0x64125B,
                                                              0x6EE183, 0x6EE27E, 0x71F6FA, 0x71F731, 0x720EDA, 0x7213F6, 0x760835, 0x760969};
      for (auto addr : mlists_aicops_begin_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::AICops].mBegin);
      // MLists[AICops]::mSize
      std::vector<std::uintptr_t> mlists_aicops_size_refs = {0x470A89, 0x470BCC, 0x472931, 0x472BA5, 0x4744C0, 0x47453D, 0x475183, 0x475306,
                                                             0x47A51A, 0x47A55E, 0x53108B, 0x53130E, 0x579E70, 0x57A0A6, 0x6410F3, 0x641267,
                                                             0x6EE188, 0x6EE283, 0x71F6F2, 0x71F737, 0x720EE0, 0x7213FC, 0x76083B, 0x76096F};
      for (auto addr : mlists_aicops_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::AICops].mSize);

      // MLists[Racers]::mBegin
      std::vector<std::uintptr_t> mlists_racers_begin_refs = {0x41999D, 0x419A13, 0x42F5DF, 0x42F610, 0x47FBB2, 0x47FC15, 0x5E30A9, 0x5E30D7, 0x5EB839};
      for (auto addr : mlists_racers_begin_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Racers].mBegin);
      // MLists[Racers]::mSize
      std::vector<std::uintptr_t> mlists_racers_size_refs = {0x4199A3, 0x419A19, 0x42F5D8, 0x42F616, 0x47FB94, 0x47FC1B,
                                                             0x5E30A1, 0x5E30DD, 0x5EB82E, 0x5EB938, 0x641320};
      for (auto addr : mlists_racers_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Racers].mSize);

      // MLists[Remote]::mSize
      std::vector<std::uintptr_t> mlists_remote_size_refs = {0x4E5CCE, 0x4F300C};
      for (auto addr : mlists_remote_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Remote].mSize);

      // MLists[Inactive]
      std::vector<std::uintptr_t> mlists_inactive_refs = {0x67ED67, 0x67ED6E, 0x67ED77};
      for (auto addr : mlists_inactive_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Inactive]);
      // MLists[Inactive]::mBegin
      std::vector<std::uintptr_t> mlists_inactive_begin_refs = {0x67ED81};
      for (auto addr : mlists_inactive_begin_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Inactive].mBegin);
      // MLists[Inactive]::mCapacity
      std::vector<std::uintptr_t> mlists_inactive_capacity_refs = {0x67ED5F};
      for (auto addr : mlists_inactive_capacity_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Inactive].mCapacity);
      // MLists[Inactive]::mSize
      std::vector<std::uintptr_t> mlists_inactive_size_refs = {0x67ED59, 0x67ED87, 0x67ED96};
      for (auto addr : mlists_inactive_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Inactive].mSize);

      // MLists[Trailers]
      std::vector<std::uintptr_t> mlists_trailers_refs = {0x67EDC3, 0x67EDC8, 0x67EDD1};
      for (auto addr : mlists_trailers_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Trailers]);
      // MLists[Trailers]::mBegin
      std::vector<std::uintptr_t> mlists_trailers_begin_refs = {0x474205, 0x474406, 0x67EDDC};
      for (auto addr : mlists_trailers_begin_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Trailers].mBegin);
      // MLists[Trailers]::mCapacity
      std::vector<std::uintptr_t> mlists_trailers_capacity_refs = {0x67EDBA};
      for (auto addr : mlists_trailers_capacity_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Trailers].mCapacity);
      // MLists[Trailers]::mSize
      std::vector<std::uintptr_t> mlists_trailers_size_refs = {0x4741FD, 0x47440C, 0x67EDB4, 0x67EDE2, 0x67EDF1};
      for (auto addr : mlists_trailers_size_refs) SetAddressTo(addr, &newList.mSet[OpenMW::eVehicleList::Trailers].mSize);

      static std::vector<std::uintptr_t> size_limits = {
          0x67AEB0,  // default initializer for UTL::Collections::ListableSet<IVehicle,10,eVehicleList,10>::_mLists
          0x67E9DA,  // default initializer for UTL::Collections::ListableSet<IVehicle,10,eVehicleList,10>::_mLists
          // 0x67ECCA,  // PVehicle::UpdateListings
          // 0x424501,
          0x424511,  // vfptr to ListableSet
          0x41EC15,  // AITrafficManager::NeedsTraffic
                     // 0x426332,  // AITrafficManager::NextSpawn
                     // 0x674BD3, // FastMem, alloc 0x14 and set to 0
                     // 0x675723, // FastMem, alloc 0x14, set to 0 and copy some data
                     // 0x683DB5,  // PVehicle::CountResources
                     // 0x683DCA,  // PVehicle::CountResources
          // 0x687855,  // PVehicle::MakeRoom
          // 0x679801,  // UTL::FixedVector<PVehicle::ManageNode, 10, 16>::GetGrowSize
          0x679811,  // UTL::FixedVector<PVehicle::ManageNode, 10, 16>::GetMaxCapacity
          0x687819   // PVehicle::MakeRoom, compare if more than 20 cars, and try to remove some if it is
      };
      for (auto addr : size_limits) SetAddressTo(addr, static_cast<std::uint8_t>(newLimit));
    }
    static void doHooks() {
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x40B5C0, reinterpret_cast<std::uintptr_t>(&details::hk40B5C0));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x41D2B0, reinterpret_cast<std::uintptr_t>(&details::hk41D2B0));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x41D2F0, reinterpret_cast<std::uintptr_t>(&details::hk41D2F0));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x425370, reinterpret_cast<std::uintptr_t>(&details::hk425370));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x4254C0, reinterpret_cast<std::uintptr_t>(&details::hk4254C0));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x425510, reinterpret_cast<std::uintptr_t>(&details::hk425510));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x425560, reinterpret_cast<std::uintptr_t>(&details::hk425560));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x4790E4, reinterpret_cast<std::uintptr_t>(&details::hk4790E4));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x57A13B, reinterpret_cast<std::uintptr_t>(&details::hk57A13B));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x60CF04, reinterpret_cast<std::uintptr_t>(&details::hk60CF04));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x610230, reinterpret_cast<std::uintptr_t>(&details::hk610230));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x67AC31, reinterpret_cast<std::uintptr_t>(&details::hk67AC31));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x67AD46, reinterpret_cast<std::uintptr_t>(&details::hk67AD46));
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x706418, reinterpret_cast<std::uintptr_t>(&details::hk706418));
    }
  }  // namespace AttemptToIncreaseIVehicleLimit

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
          if (ImGui::Button("Spawn car") && pvehicle) {
            OpenMW::UMath::Vector3 direction;
            pvehicle->GetRigidBody()->GetForwardVector(direction);
            OpenMW::PVehicle::Construct(OpenMW::VehicleParams(OpenMW::DriverClass::None, OpenMW::Attrib::StringToKey("911turbo"), direction,
                                                              pvehicle->GetPosition() + (direction * 5.0f)));
          }
          if (ImGui::Button("Spawn cop") && pvehicle) {
            OpenMW::UMath::Vector3 direction;
            pvehicle->GetRigidBody()->GetForwardVector(direction);
            OpenMW::PVehicle::Construct(OpenMW::VehicleParams(OpenMW::DriverClass::Cop, OpenMW::Attrib::StringToKey("copgto"), direction,
                                                              pvehicle->GetPosition() + (direction * 5.0f)));
          }
          if (ImGui::Button("Spawn traffic") && pvehicle) {
            OpenMW::UMath::Vector3 direction;
            pvehicle->GetRigidBody()->GetForwardVector(direction);
            OpenMW::PVehicle::Construct(OpenMW::VehicleParams(OpenMW::DriverClass::Traffic, OpenMW::Attrib::StringToKey("traftaxi"), direction,
                                                              pvehicle->GetPosition() + (direction * 5.0f)));
          }
          for (std::size_t _1 = 0; _1 < 10; _1++) {
            ImGui::Separator();
            ImGui::Text("Bucket nr: %d", _1);
            ImGui::Text("vfptr: %08X", AttemptToIncreaseIVehicleLimit::newList.mSet[static_cast<OpenMW::eVehicleList>(_1)]);
            ImGui::Text("Capacity: %d", AttemptToIncreaseIVehicleLimit::newList.mSet[static_cast<OpenMW::eVehicleList>(_1)].mCapacity);
            ImGui::Text("Size: %d", AttemptToIncreaseIVehicleLimit::newList.mSet[static_cast<OpenMW::eVehicleList>(_1)].mSize);
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
      // Set up MirrorHook
      while (MirrorHook::Init(MirrorHook::Framework::D3D9, &d3d) != MirrorHook::Result::Successful) std::this_thread::sleep_for(1s);
      // Set Up Dear ImGui
      {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        auto& io = ImGui::GetIO();

        io.FontDefault = NULL;
        io.IniFilename = NULL;
        ImGui_ImplWin32_Init(MirrorHook::WndProc::GetWindowHandle());
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
    // SkipFE
    MemoryEditor::Get().UnlockMemory(0x926064, 4);
    *reinterpret_cast<bool*>(0x926064) = true;
    MemoryEditor::Get().LockMemory(0x926064);
    // enable release printf
    MemoryEditor::Get().UnlockMemory(0x90E630, 4);
    *reinterpret_cast<bool*>(0x90E630) = true;
    MemoryEditor::Get().LockMemory(0x90E630);
    d3d9::hook();
    AttemptToIncreaseIVehicleLimit::debug();
    AttemptToIncreaseIVehicleLimit::doHooks();
  }

}  // namespace SpeedPlayground

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);
    std::thread(SpeedPlayground::Init).detach();
  }
  return TRUE;
}
