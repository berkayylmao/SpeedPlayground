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
#ifndef SPEEDPLAYGROUND_DIRECTXWALKER_H
#define SPEEDPLAYGROUND_DIRECTXWALKER_H

#include "seh_handler.h"
SPEEDPLAYGROUND_DISABLE_VC_WARNINGS()
#include <d3d9.h>
#include <memoryapi.h>
#include <thread>
#include <utility>
#include <Winuser.h>  // MessageBox

#include <NFSPluginSDK/Core/MemoryEditor.hpp>
SPEEDPLAYGROUND_RESTORE_VC_WARNINGS()
using D3DCreate_t           = LPDIRECT3D9(__stdcall*)(UINT);
using D3D9CreateDevice_t    = HRESULT(__stdcall*)(LPDIRECT3D9, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*, LPDIRECT3DDEVICE9*);
using D3D9Reset_t           = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
using D3D9BeginScene_t      = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9);
using D3D9EndScene_t        = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9);
using D3D9BeginStateBlock_t = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9);

class DirectXWalker {
  static inline LPDIRECT3D9                                   sInterface;
  static inline D3DCreate_t                                   sCreateInterface;
  static inline LPDIRECT3DDEVICE9                             sDevice;
  static inline D3D9CreateDevice_t                            sCreateDevice;
  static inline D3D9BeginStateBlock_t                         sBeginStateBlock;
  static inline std::pair<D3D9Reset_t, D3D9Reset_t>           sBeforeReset;
  static inline std::pair<D3D9Reset_t, D3D9Reset_t>           sAfterReset;
  static inline std::pair<D3D9BeginScene_t, D3D9BeginScene_t> sBeginScene;
  static inline std::pair<D3D9EndScene_t, D3D9EndScene_t>     sEndScene;

  static HRESULT __stdcall hkBeginScene(LPDIRECT3DDEVICE9 pDevice) {
    SEHHandler _seh;
    try {
      HRESULT ret = D3D_OK;
      if (sBeginScene.second) ret |= sBeginScene.second(pDevice);
      if (sBeginScene.first) ret |= sBeginScene.first(pDevice);

      return ret;
    } catch (const SEHException&) {
      return D3DERR_DEVICENOTRESET;
    }
  }
  static HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
    SEHHandler _seh;
    try {
      HRESULT ret = D3D_OK;
      if (sEndScene.second) ret |= sEndScene.second(pDevice);
      if (sEndScene.first) ret |= sEndScene.first(pDevice);

      return ret;
    } catch (const SEHException&) {
      return D3DERR_DEVICENOTRESET;
    }
  }
  static HRESULT __stdcall hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) {
    SEHHandler _seh;
    try {
      HRESULT ret = D3D_OK;
      if (sBeforeReset.second) ret |= sBeforeReset.second(pDevice, pPresentationParameters);
      if (sBeforeReset.first)
        ret |= sBeforeReset.first(pDevice, pPresentationParameters);
      else if (sAfterReset.first)
        ret |= sAfterReset.first(pDevice, pPresentationParameters);
      if (sAfterReset.second) ret |= sAfterReset.second(pDevice, pPresentationParameters);

      return ret;
    } catch (const SEHException&) {
      return D3DERR_DEVICENOTRESET;
    }
  }
  static HRESULT __stdcall hkBeginStateBlock(LPDIRECT3DDEVICE9 pDevice) {
    SEHHandler _seh;
    try {
      HRESULT ret = D3D_OK;

      unhook(pDevice);
      if (sBeginStateBlock) ret = sBeginStateBlock(pDevice);

      hook(pDevice);
      return ret;
    } catch (const SEHException&) {
      return D3DERR_DEVICENOTRESET;
    }
  }

  static void hook(LPDIRECT3DDEVICE9 pDevice) {
    SEHHandler _seh;
    try {
      std::uintptr_t* vt = *reinterpret_cast<std::uintptr_t**>(pDevice);
      // Reset
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[16]));
        if (rw.GetValue<D3D9Reset_t>() != &hkReset) {
          sBeforeReset.first = rw.GetValue<D3D9Reset_t>();
          sAfterReset.first  = rw.GetValue<D3D9Reset_t>();
        }
        rw.SetValue(&hkReset);
      }
      // BeginScene
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[41]));
        if (rw.GetValue<D3D9BeginScene_t>() != &hkBeginScene) sBeginScene.first = rw.GetValue<D3D9BeginScene_t>();
        rw.SetValue(&hkBeginScene);
      }
      // EndScene
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[42]));
        if (rw.GetValue<D3D9EndScene_t>() != &hkEndScene) sEndScene.first = rw.GetValue<D3D9EndScene_t>();
        rw.SetValue(&hkEndScene);
      }
      // BeginStateBlock
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[60]));
        if (rw.GetValue<D3D9BeginStateBlock_t>() != &hkBeginStateBlock) sBeginStateBlock = rw.GetValue<D3D9BeginStateBlock_t>();
        rw.SetValue(&hkBeginStateBlock);
      }
    } catch (const SEHException&) {
    }
  }
  static void unhook(LPDIRECT3DDEVICE9 pDevice) {
    SEHHandler _seh;
    try {
      std::uintptr_t* vt = *reinterpret_cast<std::uintptr_t**>(pDevice);
      // Reset
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[16]));
        if (sBeforeReset.first)
          rw.SetValue(sBeforeReset.first);
        else if (sAfterReset.first)
          rw.SetValue(sAfterReset.first);
      }
      // BeginScene
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[41]));
        if (sBeginScene.first) rw.SetValue(sBeginScene.first);
      }
      // EndScene
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[42]));
        if (sEndScene.first) rw.SetValue(sEndScene.first);
      }
      // BeginStateBlock
      {
        auto rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[60]));
        if (sBeginStateBlock) rw.SetValue(sBeginStateBlock);
      }
    } catch (const SEHException&) {
    }
  }

  static HRESULT __stdcall hkCreateDevice(LPDIRECT3D9 iinterface, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags,
                                          D3DPRESENT_PARAMETERS* pPresentationParameters, LPDIRECT3DDEVICE9* ppReturnedDeviceInterface) {
    SEHHandler _seh;
    try {
      auto ret = sCreateDevice(iinterface, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
      if (ret == D3D_OK) {
        sDevice = *ppReturnedDeviceInterface;
        hook(*ppReturnedDeviceInterface);
      }

      return ret;
    } catch (const SEHException& e) {
      MessageBoxA(nullptr, e.what(), "SpeedPlayground - Error in hkCreateDevice!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
      return D3DERR_INVALIDCALL;
    }
  }
  static LPDIRECT3D9 __stdcall hkDirect3DCreate9(UINT SDKVersion) {
    SEHHandler _seh;
    try {
      auto ret = sCreateInterface(SDKVersion);
      if (ret) {
        sInterface = ret;

        auto* vt = *reinterpret_cast<std::uintptr_t**>(ret);
        auto  rw = MemoryEditor::Get().GetRawMemory(reinterpret_cast<std::uintptr_t>(&vt[16]));

        if (rw.GetValue<D3D9CreateDevice_t>() != &hkCreateDevice) sCreateDevice = rw.GetValue<D3D9CreateDevice_t>();
        rw.SetValue(&hkCreateDevice);
      }

      return ret;
    } catch (const SEHException& e) {
      MessageBoxA(nullptr, e.what(), "SpeedPlayground - Error in hkDirect3DCreate9!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
      return nullptr;
    }
  }

  DirectXWalker() = default;

 public:
  LPDIRECT3DDEVICE9 GetDevice() { return sDevice; }

  void SetBeforeReset(D3D9Reset_t fn) { sBeforeReset.second = fn; }
  void SetAfterReset(D3D9Reset_t fn) { sAfterReset.second = fn; }
  void SetBeginScene(D3D9BeginScene_t fn) { sBeginScene.second = fn; }
  void SetEndScene(D3D9EndScene_t fn) { sEndScene.second = fn; }

  void Init(NFSPluginSDK::Game game) {
    SEHHandler _seh;
    try {
      std::uintptr_t mFrom;

      switch (game) {
        case NFSPluginSDK::Game::MW05: {
          mFrom = 0x7E7D52;
        } break;
        case NFSPluginSDK::Game::Carbon: {
          mFrom = 0x86B28A;
        } break;
        case NFSPluginSDK::Game::ProStreet: {
          mFrom = 0x80AC64;
        } break;
        default: {
          throw std::runtime_error("Game not supported.");
        } break;
      }
      {
        auto to = reinterpret_cast<std::uintptr_t>(&hkDirect3DCreate9);
        auto rw = MemoryEditor::Get().GetRawMemory(mFrom);
        if (rw.GetValue<std::uint16_t>() == 0x25FF) {
          sCreateInterface = *reinterpret_cast<D3DCreate_t*>((rw + 2).GetValue<std::uintptr_t>());
          (rw + 2).SetValue(&to);
        } else {
          sCreateInterface = &::Direct3DCreate9;
          MemoryEditor::Get().Make(MemoryEditor::MakeType::JumpAbsolute, mFrom, to);
        }
      }
      MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, mFrom, reinterpret_cast<std::uintptr_t>(&hkDirect3DCreate9));
    } catch (const SEHException& e) {
      MessageBoxA(nullptr, e.what(), "SpeedPlayground - Error in DirectXWalker!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
  }

  DirectXWalker(const DirectXWalker&)  = delete;
  void operator=(const DirectXWalker&) = delete;

  /// <summary>
  /// Make sure to init with Init(NFSPluginSDK::SpeedGame)!
  /// </summary>
  static inline DirectXWalker& Get() {
    static DirectXWalker singleton;
    return singleton;
  }
};

#endif