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
#ifndef SPEEDPLAYGROUND_WNDPROCWALKER_H
#define SPEEDPLAYGROUND_WNDPROCWALKER_H

#include "macros.h"
SPEEDPLAYGROUND_DISABLE_VC_WARNINGS()
#include <algorithm>
#include <vector>
#include <windef.h>
#include <winuser.h>
SPEEDPLAYGROUND_RESTORE_VC_WARNINGS()
#pragma warning(push)
#pragma warning(disable : 28183)  // The argument could be one value, and is a copy of the value found in the pointer

class WndProcWalker {
  static inline std::pair<WNDPROC, std::vector<WNDPROC>> WndProc;

  static LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT ret = FALSE;
    for (const auto& wndproc : WndProc.second) ret += wndproc(hWnd, uMsg, wParam, lParam);

    return ret ? FALSE : ::CallWindowProc(WndProc.first, hWnd, uMsg, wParam, lParam);
  }

  HWND mWindowHandle;

  WndProcWalker() : mWindowHandle(nullptr) {}

 public:
  void AddWndProc(WNDPROC fn) {
    if (std::find(WndProc.second.cbegin(), WndProc.second.cend(), fn) == WndProc.second.cend()) WndProc.second.push_back(fn);
  }
  void RemoveWndProc(WNDPROC fn) {
    auto it = std::find(WndProc.second.begin(), WndProc.second.end(), fn);
    if (it != WndProc.second.end()) WndProc.second.erase(it);
  }
  HWND GetWindowHandle() { return mWindowHandle; }

  // Will block
  void Init(HWND* pHwnd) {
    while (!*pHwnd) std::this_thread::sleep_for(std::chrono::seconds(1));

    mWindowHandle = *pHwnd;
    WndProc.first = reinterpret_cast<WNDPROC>(::SetWindowLongPtr(mWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hkWndProc)));
  }

  WndProcWalker(const WndProcWalker&) = delete;
  void operator=(const WndProcWalker&) = delete;

  /// <summary>
  /// Make sure to init with Init(HWND)!
  /// </summary>
  static inline WndProcWalker& Get() {
    static WndProcWalker singleton;
    return singleton;
  }
};

#pragma warning(pop)
#endif