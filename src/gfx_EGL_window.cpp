// Copyright 2014, 2015 Lauri Gustafsson
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

#ifdef USE_X

void GfxEGLWindow::swapBuffers()
{
    eglSwapBuffers(display, surface);
}

// X11 related local variables
static Display *x_display = NULL;

bool GfxEGLWindow::createWindow(GLuint flags)
{
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
    
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    EGLConfig ecfg;
    EGLint num_config;
    Window win;

    /*
     * X11 native display initialization
     */

    x_display = XOpenDisplay(NULL);
    if ( x_display == NULL ) {
        return false;
    }

    root = DefaultRootWindow(x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(
               x_display, root,
               0, 0, c->w, c->h, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa );

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (x_display, win);
    XStoreName (x_display, win, "esfragt 2.1"); //WIN NAME

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (x_display, "_NET_WM_STATE", FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = FALSE;
    XSendEvent (
       x_display,
       DefaultRootWindow ( x_display ),
       FALSE,
       SubstructureNotifyMask,
       &xev );
    
    //hWnd = (EGLNativeWindowType) win;
   //xdisplay = win;
    
   EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;
   //EGLDisplay display;
   //EGLContext context;
   //EGLSurface surface;
   EGLConfig config;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Get Display
   display = eglGetDisplay((EGLNativeDisplayType)x_display);
   if ( display == EGL_NO_DISPLAY ) {
      return false;
   }

   // Initialize EGL
   if ( !eglInitialize(display, &majorVersion, &minorVersion) ) {
      return false;
   }

   // Get configs
   if ( !eglGetConfigs(display, NULL, 0, &numConfigs) ) {
      return false;
   }

   // Choose config
   if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) ) {
      return false;
   }

   // Create a surface
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)win, NULL);
   if ( surface == EGL_NO_SURFACE ) {
      return false;
   }

   // Create a GL context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
   if ( context == EGL_NO_CONTEXT ) {
      return false;
   }   
   
   // Make the context current
   if ( !eglMakeCurrent(display, surface, surface, context) ) {
      return false;
   }
   
   /*eglDisplay = display;
   *eglSurface = surface;
   *eglContext = context;*/

   return true;
}

#else
#ifdef USE_SDL

void GfxEGLWindow::swapBuffers()
{
    SDL_GL_SwapBuffers();
    SDL_PollEvent(&events);
    if (events.type == SDL_QUIT)
		exit(0);
	else if (events.type == SDL_KEYDOWN)
		if (events.key.keysym.sym == SDLK_ESCAPE)
			exit(0);
}

bool GfxEGLWindow::createWindow(GLuint flags)
{
	int err;
	
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    if (SDL_SetVideoMode(c->w, c->h, 24, SDL_OPENGL|(c->fullscreen ? SDL_FULLSCREEN : 0)) == 0) {
		std::cout << "Video mode set failed.\n" << SDL_GetError << std::endl;
		exit(2);
	}
	
	SDL_WM_SetCaption("esfragt 2.1 (SDL)", NULL);
	if (c->fullscreen)
		SDL_ShowCursor(false);
	
    return true;
}

#else

void GfxEGLWindow::swapBuffers()
{
    eglSwapBuffers(display, buffer);
}

bool GfxEGLWindow::createWindow(GLuint flags)
{
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
    uint32_t x;
    uint32_t y;

    w = c->w;
    h = c->h;
    x = c->x;
    y = c->y;

    dst_rect.x = x;
    dst_rect.y = y;
    dst_rect.width = w * c->stretch;
    dst_rect.height = h * c->stretch;

    src_rect.x = x;
    src_rect.y = y;
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
    
    if (c->swInterval0)
        eglSwapInterval(eglDisplay, 0);

    return true;
}
#endif
#endif
