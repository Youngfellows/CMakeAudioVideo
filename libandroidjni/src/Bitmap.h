#pragma once
/*
 *      Copyright (C) 2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "JNIBase.h"

class CJNIBitmap : public CJNIBase
{
public:
  CJNIBitmap() : CJNIBase() {}
  CJNIBitmap(const jni::jhobject &object) : CJNIBase(object) {}
  ~CJNIBitmap() {}

  enum Config
  {
    ALPHA_8,
    ARGB_4444,
    ARGB_8888,
    HARDWARE,
    RGBA_1010102,
    RGBA_F16,
    RGB_565,
  };

  static CJNIBitmap createBitmap(int width, int height, CJNIBitmap::Config config);
};
