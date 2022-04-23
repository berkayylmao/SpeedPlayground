/*
// clang-format off
//
//    NFS Chaos Mod (NFS-Chat-Chaos-Mod)
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

#pragma once
#include "macros.h"
__DISABLE_VC_WARNINGS__()

// Win32 targeting
#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0601  // _WIN32_WINNT_WIN7
#include <SDKDDKVer.h>
// Win32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
// Commonly used headers
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>  // size_t
#include <cstdint>  // integer types
#include <cstdlib>  // atexit()
#include <deque>
#include <filesystem>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// DirectInput8
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// d3dx9
#include <d3dx9.h>

// Dear ImGui
#include "Helpers/Dear ImGui/imgui.h"
#include "Helpers/Dear ImGui/imgui_internal.h"
#include "Helpers/Dear ImGui/backends/imgui_impl_dx9.h"
#include "Helpers/Dear ImGui/backends/imgui_impl_win32.h"

// fmt
#include "Helpers/fmt/format.h"

// MirrorHook
#include <MirrorHook.hpp>

// OpenSpeed
#include <OpenSpeed.h>
#include <OpenSpeed/Core/MemoryEditor/MemoryEditor.hpp>

using namespace std::chrono_literals;

__RESTORE_VC_WARNINGS__()
