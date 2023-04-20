#pragma once
/*
 * Copyright (C) 2014 Team Kodi
 * http://xbmc.org
 *
 * This Program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This Program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Kodi; see the file COPYING. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

#include <vector>

#include "JNIBase.h"

class CJNIDisplayMode : public CJNIBase
{
public:
  ~CJNIDisplayMode() {};
  CJNIDisplayMode(const jni::jhobject &object) : CJNIBase(object) {};

  int getModeId();
  int getPhysicalHeight();
  int getPhysicalWidth();
  float getRefreshRate();

protected:
  CJNIDisplayMode();
};


class CJNIDisplayHdrCapabilities : public CJNIBase
{
public:
  ~CJNIDisplayHdrCapabilities() {};
  CJNIDisplayHdrCapabilities(const jni::jhobject &object) : CJNIBase(object) {};

  std::vector<int> getSupportedHdrTypes();

protected:
  CJNIDisplayHdrCapabilities();
};


class CJNIDisplay : public CJNIBase
{
public:
  CJNIDisplay();
  CJNIDisplay(const jni::jhobject &object) : CJNIBase(object) {};
  ~CJNIDisplay() {};

  long getAppVsyncOffsetNanos();
  float getRefreshRate();
  // Deprecated in API level 23
  std::vector<float> getSupportedRefreshRates();
  CJNIDisplayMode getMode();
  // Deprecated in API level 15
  int getWidth();
  // Deprecated in API level 15
  int getHeight();
  std::vector<CJNIDisplayMode> getSupportedModes();
  CJNIDisplayHdrCapabilities getHdrCapabilities();
  int getState();
  bool isHdr();
};

typedef std::vector<CJNIDisplayMode> CJNIDisplayModes;
