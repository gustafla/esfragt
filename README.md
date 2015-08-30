**esfragt**

A GLSL shader platform for Raspberry Pi and other GL ES 2.0 devices.

See --help (or text.cpp) for help.  
--version for other info.

To build:  
    $ make  
    $ sudo make install (optional, copies esfragt to /usr/local/bin)  
    And do what you want with the binary.  

**OR**  
if you have a device that doesn't have dispmanx and can use X instead,  
    $ make xwin  
    # cp esfragt.xwin /usr/local/bin/esfragt

**OR**
if you feel lucky about this sdl hack and want a better windowing support
    $ make sdlwin
    $ sudo make install

Some PC distros offer libgles2.0-mesa-dev and libegl1-mesa-dev  
(or similar), those can be used to build the xwin version.  
If you're running Windows, check my esfragt-win repository.

Copyright 2014, 2015 Lauri Gustafsson.  
Released GNU GPLv3+, see COPYING.

<http://luutifa.tk/esfragt/>  
<https://github.com/luutifa/esfragt>

In case of anything: luutifa@gmail.com
