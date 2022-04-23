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

#ifndef __DISABLE_VC_WARNINGS__
#define __DISABLE_VC_WARNINGS__()              \
  __pragma(warning(push, 0)) __pragma(warning( \
      disable : 4244 4265 4267 4350 4472 4509 4548 4623 4710 4985 6001 6011 6255 6285 6387 6031 6320 6258 4755 4625 4626 4702 26812 26439 26451 26495 26819 26498))
#endif
#ifndef __RESTORE_VC_WARNINGS__
#define __RESTORE_VC_WARNINGS__() __pragma(warning(pop))
#endif

#ifndef __STR_MACROS__
#define __STR__(x)             #x
#define __STR_EXPAND__(x)      __STR__(x)
#define __CONCAT_INNER__(a, b) a##b
#define __CONCAT__(a, b)       __CONCAT_INNER__(a, b)
#define __STR_MACROS__
#endif

#ifndef __EXECUTE_EVERY_X_SECONDS__
// Requires ImGui
#define __EXECUTE_EVERY_X_SECONDS__(fSecond)                            \
  static float __CONCAT__(__seconds_passed__, __LINE__) = fSecond;      \
  __CONCAT__(__seconds_passed__, __LINE__) += ImGui::GetIO().DeltaTime; \
  if (__CONCAT__(__seconds_passed__, __LINE__) < fSecond) return;       \
  __CONCAT__(__seconds_passed__, __LINE__) = 0.0f
#endif
