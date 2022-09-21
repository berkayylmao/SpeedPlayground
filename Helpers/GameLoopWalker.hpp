/*
// clang-format off
//
//    SpeedPlayground
//    Copyright (C) 2022 Berkay Yigit <mail@berkay.link>
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

#pragma once
#ifndef SPEEDPLAYGROUND_GAMELOOPWALKER_H
#define SPEEDPLAYGROUND_GAMELOOPWALKER_H

#include "seh_handler.h"
SPEEDPLAYGROUND_DISABLE_VC_WARNINGS()
#include <cstdint>
#include <functional>
#include <WinUser.h>  // MessageBox

#include <NFSPluginSDK.h>
#include <NFSPluginSDK/Core/MemoryEditor.hpp>
SPEEDPLAYGROUND_RESTORE_VC_WARNINGS()

class GameLoopWalker {
  static inline void(__cdecl* sOriginal)();
  static inline std::function<void()> sFn;

  static constexpr std::uintptr_t CONST_WORLDSERVICE_FROM_MW05     = 0x75AB66;
  static constexpr std::uintptr_t CONST_WORLDSERVICE_ORIGINAL_MW05 = 0x755450;

  static void WORLDSERVICE_HOOK_MW05() {
    __asm {
      push eax
      mov eax, 0x9B0900
      mov ecx, [eax]
      mov esi, ecx
      pop eax
      call sOriginal
    }
    if (sFn) sFn();
  }

  static constexpr std::uintptr_t CONST_WORLDSERVICE_FROM_CARBON     = 0x7DCD9C;
  static constexpr std::uintptr_t CONST_WORLDSERVICE_ORIGINAL_CARBON = 0x7D5010;

  static void WORLDSERVICE_HOOK_CARBON() {
    __asm {
      push eax
      mov eax, 0xB74BF0
      mov ecx, [eax]
      mov esi, ecx
      pop eax
      call sOriginal
    }
    if (sFn) sFn();
  }

  static constexpr std::uintptr_t CONST_WORLDSERVICE_FROM_PROSTREET     = 0x78AF3C;
  static constexpr std::uintptr_t CONST_WORLDSERVICE_ORIGINAL_PROSTREET = 0x77CD60;

  static void WORLDSERVICE_HOOK_PROSTREET() {
    __asm {
      push eax
      mov eax, 0xAEB6A4
      mov ecx, [eax]
      mov esi, ecx
      pop eax
      call sOriginal
    }
    if (sFn) sFn();
  }

  std::uintptr_t mFrom;
  std::uintptr_t mTo;

  GameLoopWalker() : mFrom(0), mTo(0) {}

 public:
  void SetFn(const std::function<void()>& fn) { sFn = fn; }

  void Init(NFSPluginSDK::Game game) {
    SEHHandler _seh;
    try {
      switch (game) {
        case NFSPluginSDK::Game::MW05: {
          sOriginal = reinterpret_cast<void(__cdecl*)()>(CONST_WORLDSERVICE_ORIGINAL_MW05);
          mFrom     = CONST_WORLDSERVICE_FROM_MW05;
          mTo       = reinterpret_cast<std::uintptr_t>(&WORLDSERVICE_HOOK_MW05);
        } break;
        case NFSPluginSDK::Game::Carbon: {
          sOriginal = reinterpret_cast<void(__cdecl*)()>(CONST_WORLDSERVICE_ORIGINAL_CARBON);
          mFrom     = CONST_WORLDSERVICE_FROM_CARBON;
          mTo       = reinterpret_cast<std::uintptr_t>(&WORLDSERVICE_HOOK_CARBON);
        } break;
        case NFSPluginSDK::Game::ProStreet: {
          sOriginal = reinterpret_cast<void(__cdecl*)()>(CONST_WORLDSERVICE_ORIGINAL_PROSTREET);
          mFrom     = CONST_WORLDSERVICE_FROM_PROSTREET;
          mTo       = reinterpret_cast<std::uintptr_t>(&WORLDSERVICE_HOOK_PROSTREET);
        } break;
        default:
          return;
      }
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Call, mFrom, mTo);
    } catch (const SEHException& e) {
      MessageBoxA(nullptr, e.what(), "SpeedPlayground - Error!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
  }

  GameLoopWalker(const GameLoopWalker&) = delete;
  void operator=(const GameLoopWalker&) = delete;

  /// <summary>
  /// Make sure to init with Init(NFSPluginSDK::SpeedGame)!
  /// </summary>
  static inline GameLoopWalker& Get() {
    static GameLoopWalker singleton;
    return singleton;
  }
};

#endif