// Copyright 2014 Lauri Gustafsson
/*
This file is part of esfragt.

    esfragt is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    esfragt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with esfragt, see COPYING. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GFX_EGL_WINDOW_HPP
#define GFX_EGL_WINDOW_HPP

#ifndef ODROID
#include "config.hpp"
#include "rpi_gfx.hpp"
#include <string>

class GfxEGLWindow
{
public:
    GfxEGLWindow(Config* ic);
    void swapBuffers();
    bool createWindow(GLuint flags);

protected:

    Config* c;
    EGLNativeWindowType window;
    EGLDisplay display;
    EGLContext context;
    EGLSurface buffer;
};
#else

#include "config.hpp"
#include "rpi_gfx.hpp"
#include <string>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

class GfxEGLWindow
{
public:
    GfxEGLWindow(Config* ic);
    void swapBuffers();
    bool createWindow(GLuint flags);

protected:

    Config* c;
    EGLNativeWindowType window;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
};
#endif
#endif
