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
#ifndef SPEEDPLAYGROUND_PCH_H
#define SPEEDPLAYGROUND_PCH_H

#include "macros.h"
SPEEDPLAYGROUND_DISABLE_VC_WARNINGS()

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
#include <array>
#include <cassert>
#include <chrono>
#include <cinttypes>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <format>
#include <functional>
#include <map>
#include <shellapi.h>  // ShellExecute
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// di8
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
// d3dx9
#include <d3dx9.h>

#ifdef GetObject
// see https://stackoverflow.com/questions/3223854/getobject-getobjecta-linker-error
#undef GetObject
#endif

// Dear ImGui
#include "Helpers/Dear ImGui/imgui.h"
#include "Helpers/Dear ImGui/imgui_internal.h"
#include "Helpers/Dear ImGui/backends/imgui_impl_dx9.h"
#include "Helpers/Dear ImGui/backends/imgui_impl_win32.h"
#include "Helpers/Dear ImGui/misc/freetype/imgui_freetype.h"

// NFSPluginSDK
#include <NFSPluginSDK.h>
#include <NFSPluginSDK/Game.MW05/MW05.h>
#include <NFSPluginSDK/Game.MW05/MW05.h>
namespace MW = NFSPluginSDK::MW05;

using namespace std::chrono_literals;

SPEEDPLAYGROUND_RESTORE_VC_WARNINGS()
#pragma warning(disable : 26813)  // Use 'bitwise and' to check if a flag is set

#include "Helpers/DirectXWalker.hpp"
#include "Helpers/GameLoopWalker.hpp"
#include "Helpers/WndProcWalker.hpp"

#include "seh_handler.h"

#endif