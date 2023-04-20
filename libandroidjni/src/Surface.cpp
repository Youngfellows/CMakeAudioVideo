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
#include "Surface.h"
#include "SurfaceTexture.h"

#include "jutils-details.hpp"

using namespace jni;

int CJNISurface::ROTATION_0;
int CJNISurface::ROTATION_90;
int CJNISurface::ROTATION_180;
int CJNISurface::ROTATION_270;
int CJNISurface::FRAME_RATE_COMPATIBILITY_DEFAULT;
int CJNISurface::FRAME_RATE_COMPATIBILITY_FIXED_SOURCE;
int CJNISurface::CHANGE_FRAME_RATE_ONLY_IF_SEAMLESS;
int CJNISurface::CHANGE_FRAME_RATE_ALWAYS;

const char* CJNISurface::m_classname = "android/view/Surface";

void CJNISurface::PopulateStaticFields()
{
  jhclass clazz = find_class(m_classname);
  ROTATION_0  = get_static_field<int>(clazz, "ROTATION_0");
  ROTATION_90 = get_static_field<int>(clazz, "ROTATION_90");
  ROTATION_180= get_static_field<int>(clazz, "ROTATION_180");
  ROTATION_270= get_static_field<int>(clazz, "ROTATION_270");
  if (GetSDKVersion() >= 30)
  {
    FRAME_RATE_COMPATIBILITY_DEFAULT = get_static_field<int>(clazz, "FRAME_RATE_COMPATIBILITY_DEFAULT");
    FRAME_RATE_COMPATIBILITY_FIXED_SOURCE = get_static_field<int>(clazz, "FRAME_RATE_COMPATIBILITY_FIXED_SOURCE");
  }
  if (GetSDKVersion() >= 31)
  {
    CHANGE_FRAME_RATE_ONLY_IF_SEAMLESS = get_static_field<int>(clazz, "CHANGE_FRAME_RATE_ONLY_IF_SEAMLESS");
    CHANGE_FRAME_RATE_ALWAYS = get_static_field<int>(clazz, "CHANGE_FRAME_RATE_ALWAYS");
  }
}

CJNISurface::CJNISurface()
  : CJNIBase(CJNISurface::m_classname)
{
}

CJNISurface::CJNISurface(const CJNISurfaceTexture &surfaceTexture) : CJNIBase(m_classname)
{
  m_object = new_object(m_classname, "<init>", "(Landroid/graphics/SurfaceTexture;)V", surfaceTexture.get_raw());
  m_object.setGlobal();
}

bool CJNISurface::isValid()
{
  return call_method<jboolean>(m_object,
    "isValid", "()Z");
}

void CJNISurface::release()
{
  call_method<void>(m_object,
    "release", "()V");
}

/*
CJNICanvas CJNISurface::lockCanvas(const CJNIRect &rect)
{
}

void CJNISurface::unlockCanvasAndPost(const CJNICanvas &canvas)
{
}

void CJNISurface::unlockCanvas(const CJNICanvas &canvas)
{
}
*/

void CJNISurface::setFrameRate(float frameRate, int compatibility, int changeFrameRateStrategy)
{
  if (GetSDKVersion() >= 31)
    call_method<void>(m_object,"setFrameRate", "(FII)V", frameRate, compatibility, changeFrameRateStrategy);
  else if (GetSDKVersion() >= 30)
    call_method<void>(m_object,"setFrameRate", "(FI)V", frameRate, compatibility);
}

std::string CJNISurface::toString()
{
  return jcast<std::string>(call_method<jhstring>(m_object,
    "toString", "()Ljava/lang/String;"));
}

int CJNISurface::describeContents()
{
  return call_method<int>(m_object,
    "describeContents", "()I");
}
