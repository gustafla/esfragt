**esfragt**

A GLSL shader platform for Raspberry Pi and other OpenGL ES 2.0 devices.

See --help (or src/text.cpp) for help.  
--version for other info.

To build from a fresh clone:  
    $ cd src/  
    $ ./build.sh  
    $ sudo make install (optional, copies esfragt to /usr/local/bin)  
    And do what you want with the binary.  

Or for the Raspberry Pi:  
    $ cd src/  
    $ ./build.sh raspi

The purpose of the build.sh script is to download lib3dapp from github,  
and update it if it has already been cloned.
You can do it manually as well and then run make.
The script will most likely fail if lib3dapp is not in a clean state.
In that case, commit your changes and next time you run build.sh,
it will be merged.

Copyright 2014-2016 Lauri Gustafsson.  
Released GNU GPLv3+, see COPYING.

<http://luutifa.tk/esfragt/>  
<https://github.com/luutifa/esfragt>

In case of anything: luutifa@gmail.com
