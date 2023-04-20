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
#include "MediaCodecInfo.h"

class CJNIMediaCodecList : public CJNIBase
{
public:
  CJNIMediaCodecList(const jni::jhobject &object) : CJNIBase(object) {};
  CJNIMediaCodecList(int kind);

  static void PopulateStaticFields();

  static int ALL_CODECS;
  static int REGULAR_CODECS;

  // Deprecated in API level 21
  static int   getCodecCount();
  // Deprecated in API level 21
  static const CJNIMediaCodecInfo getCodecInfoAt(int index);
  std::vector<CJNIMediaCodecInfo> getCodecInfos();

private:
  CJNIMediaCodecList();

  static const char *m_classname;
};

using CJNIMediaCodecInfos = std::vector<CJNIMediaCodecInfo>;

