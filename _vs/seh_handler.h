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
#ifndef SPEEDPLAYGROUND_SEHHANDLER_H
#define SPEEDPLAYGROUND_SEHHANDLER_H

#include "macros.h"
SPEEDPLAYGROUND_DISABLE_VC_WARNINGS()
#include <cstdint>
#include <eh.h>
#include <stdexcept>
#include <string>
#include <wtypes.h>
#include <windef.h>
SPEEDPLAYGROUND_RESTORE_VC_WARNINGS()

class SEHException : public std::exception {
  const std::uint32_t mCode;

 public:
  virtual const char* what() const noexcept override {
    thread_local std::string str;
    str = std::to_string(mCode);
    return str.c_str();
  }

  std::uint32_t GetCode() const noexcept { return mCode; }

  explicit SEHException(std::uint32_t code) noexcept : mCode(code) {}
  explicit SEHException() noexcept : mCode(0) {}
};

class SEHHandler {
  static void translator(std::uint32_t code, EXCEPTION_POINTERS*) { throw SEHException(code); }

  const _se_translator_function mOld;

 public:
  explicit SEHHandler() noexcept : mOld(_set_se_translator(translator)) {}
  ~SEHHandler() noexcept { _set_se_translator(mOld); }
};

#endif