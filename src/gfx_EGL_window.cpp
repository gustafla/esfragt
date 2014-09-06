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

#include "gfx_EGL_window.hpp"

GfxEGLWindow::GfxEGLWindow(Config* ic):
c(ic)
{

}

void GfxEGLWindow::swapBuffers()
{
    eglSwapBuffers(display, buffer);
}

bool GfxEGLWindow::createWindow(GLuint flags)
{
    bcm_host_init();

    EGLint attribList[] =
    {
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     6,
        EGL_BLUE_SIZE,      5,
        EGL_ALPHA_SIZE,     (flags & GFX_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,     (flags & GFX_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   (flags & GFX_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & GFX_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    /*
    Confusing :)
    I pretty much stole all of this EGL code somewhere :D
    */
    static EGL_DISPMANX_WINDOW_T nativewindow;

    DISPMANX_ELEMENT_HANDLE_T dispman_element;
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;

    uint32_t w;
    uint32_t h;

    if (graphics_get_display_size(0 /*LCD*/, &w, &h) < 0)
        return false;

    w = c->w;
    h = c->h;

    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = w * c->stretch;
    dst_rect.height = h * c->stretch;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = w << 16;
    src_rect.height = h << 16;

    dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
    dispman_update = vc_dispmanx_update_start( 0 );

    dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
    0/*layer*/, &dst_rect, 0/*src*/,
    &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, (DISPMANX_TRANSFORM_T)0/*transform*/);

    nativewindow.element = dispman_element;
    nativewindow.width = w;
    nativewindow.height = h;
    vc_dispmanx_update_submit_sync( dispman_update );

    window = &nativewindow;

    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay eglDisplay;
    EGLContext eglContext;
    EGLSurface eglBuffer;
    EGLConfig config;

    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if ( eglDisplay == EGL_NO_DISPLAY )
        return false;

    // Initialize EGL
    if ( !eglInitialize(eglDisplay, &majorVersion, &minorVersion) )
        return false;

    // Get configs
    if ( !eglGetConfigs(eglDisplay, NULL, 0, &numConfigs) )
        return false;

    // Choose config
    if ( !eglChooseConfig(eglDisplay, attribList, &config, 1, &numConfigs) )
        return false;

    // Create a surface
    eglBuffer = eglCreateWindowSurface(eglDisplay, config, (EGLNativeWindowType)window, NULL);
    if ( eglBuffer == EGL_NO_SURFACE )
        return false;

    // Create a GL context
    eglContext = eglCreateContext(eglDisplay, config, EGL_NO_CONTEXT, contextAttribs );
    if ( eglContext == EGL_NO_CONTEXT )
        return false;

    // Make the context current
    if ( !eglMakeCurrent(eglDisplay, eglBuffer, eglBuffer, eglContext) )
        return false;

    display = eglDisplay;
    buffer = eglBuffer;
    context = eglContext;

    return true;
}
