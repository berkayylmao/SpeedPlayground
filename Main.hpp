/*
// clang-format off
//
//    NFSMW ChooseCorrectAnimation Fix
//    Copyright (C) 2026 Berkay Yigit <berkaytgy@gmail.com>
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

// Win32 targeting
#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0601  // _WIN32_WINNT_WIN7
#include <SDKDDKVer.h>
// Win32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
// Commonly used headers
#include <cinttypes>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace SpeedPlayground {
  inline constexpr std::uintptr_t ADDR_mLists        = 0x0092CD84;  // UTL::ListableSet::_mLists
  inline constexpr std::uintptr_t ADDR_PerpMgrPtr    = 0x0092CD7C;
  inline constexpr std::uintptr_t ADDR_IHandle       = 0x004037E0;
  inline constexpr std::uintptr_t ADDR_TheICEManager = 0x008EE320;

  static auto bRandom        = reinterpret_cast<float(__cdecl*)(float)>(0x0045DA70);
  static auto bStrNCpy       = reinterpret_cast<void(__cdecl*)(char*, const char*, int32_t)>(0x00460CA0);
  static auto bStringHash    = reinterpret_cast<std::uint32_t(__cdecl*)(const char*)>(0x00460BF0);
  static auto UTLFind        = reinterpret_cast<std::uintptr_t(__thiscall*)(void*, void*)>(0x005D59F0);
  static auto ICEGetNumScene = reinterpret_cast<std::int32_t(__thiscall*)(void*, std::uint32_t)>(0x0046E710);

  typedef double(__thiscall* fn_GetHeat)(void*);

  inline std::int32_t __cdecl hkFixedChooseArrestAnimation(std::int32_t* a2, char* BustedNISString, std::int32_t cnt) {
    std::int32_t heatlevel = 0;

    // Resolve heat level from perpetrator vehicle
    if (*(std::int32_t*)ADDR_mLists) {
      std::uintptr_t perpObj = *(std::uintptr_t*)(*(std::uintptr_t*)ADDR_PerpMgrPtr);
      if (perpObj) {
        std::uintptr_t v4 = UTLFind(*(void**)(perpObj + 4), (void*)ADDR_IHandle);

        if (v4) {
          auto fn_getheat = reinterpret_cast<double(__thiscall*)(void*)>((*(void***)v4)[1]);
          heatlevel       = (int)fn_getheat((void*)v4);
        }
      }
    }

    // Get random animation index [0, 7]
    const std::int32_t BustedNISID = (int)(uint64_t)((double)bRandom(0.99000001f) * 8.0);

    switch (heatlevel) {
      case 0:
      case 1:
        switch (BustedNISID) {
          case 0:
            bStrNCpy(BustedNISString, "ArrestM01", cnt);
            break;
          case 1:
            bStrNCpy(BustedNISString, "ArrestM16", cnt);
            break;
          case 2:
            bStrNCpy(BustedNISString, "ArrestF02", cnt);
            break;
          case 3:
            bStrNCpy(BustedNISString, "ArrestF18", cnt);
            break;
          case 4:
            bStrNCpy(BustedNISString, "ArrestM01b", cnt);
            break;
          case 5:
            bStrNCpy(BustedNISString, "ArrestM16b", cnt);
            break;
          case 6:
            bStrNCpy(BustedNISString, "ArrestF02b", cnt);
            break;
          default:
            bStrNCpy(BustedNISString, "ArrestF18b", cnt);
            break;
        }
        break;

      case 2:
        switch (BustedNISID) {
          case 0:
          case 1:
            bStrNCpy(BustedNISString, "ArrestM04", cnt);
            break;
          case 2:
          case 3:
            bStrNCpy(BustedNISString, "ArrestF23", cnt);
            break;
          case 4:
          case 5:
            bStrNCpy(BustedNISString, "ArrestM04b", cnt);
            break;
          default:
            bStrNCpy(BustedNISString, "ArrestF23b", cnt);
            break;
        }
        break;

      case 3:
        switch (BustedNISID) {
          case 0:
            bStrNCpy(BustedNISString, "ArrestM07", cnt);
            break;
          case 1:
            bStrNCpy(BustedNISString, "ArrestM14", cnt);
            break;
          case 2:
          case 3:
            bStrNCpy(BustedNISString, "ArrestF14", cnt);
            break;
          case 4:
            bStrNCpy(BustedNISString, "ArrestM07b", cnt);
            break;
          case 5:
            bStrNCpy(BustedNISString, "ArrestM14b", cnt);
            break;
          default:
            bStrNCpy(BustedNISString, "ArrestF14b", cnt);
            break;
        }
        break;

      default:
        switch (BustedNISID) {
          case 0:
            bStrNCpy(BustedNISString, "ArrestM06", cnt);
            break;
          case 1:
            bStrNCpy(BustedNISString, "ArrestM19", cnt);
            break;
          case 2:
            bStrNCpy(BustedNISString, "ArrestF06", cnt);
            break;
          case 3:
            bStrNCpy(BustedNISString, "ArrestF07", cnt);
            break;
          case 4:
            bStrNCpy(BustedNISString, "ArrestM06b", cnt);
            break;
          case 5:
            bStrNCpy(BustedNISString, "ArrestM19b", cnt);
            break;
          case 6:
            bStrNCpy(BustedNISString, "ArrestF06b", cnt);
            break;
          default:
            bStrNCpy(BustedNISString, "ArrestF07b", cnt);
            break;
        }
        break;
    }

    *a2 = 0;
    return ICEGetNumScene((void*)ADDR_TheICEManager, bStringHash(BustedNISString));
  }

  inline void Init() {
    std::uintptr_t org = 0x0044D770;

    DWORD oldProtect;
    ::VirtualProtect((void*)org, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
    *(std::uint8_t*)org       = 0xE9;
    *(std::int32_t*)(org + 1) = (std::uint32_t)&hkFixedChooseArrestAnimation - (org + 5);
    ::VirtualProtect((void*)org, 5, oldProtect, &oldProtect);
  }
}  // namespace SpeedPlayground