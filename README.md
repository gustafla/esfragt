**esfragt**

A GLSL shader platform for Raspberry Pi and other OpenGL ES 2.0 devices.

See --help (or src/text.cpp) for help.  
--version for other info.

To build:  
    $ cd src/  
    $ ./build.sh  
    $ sudo make install (optional, copies esfragt to /usr/local/bin)  
    And do what you want with the binary.  

Or for the Raspberry Pi:  
    $ cd src/  
    $ ./build.sh raspi

The point of the build.sh script is to remove my dev symlink to lib3dapp and download an actual copy from github.  
You can do it manually as well and then run make.

Copyright 2014-2016 Lauri Gustafsson.  
Released GNU GPLv3+, see COPYING.

<http://luutifa.tk/esfragt/>  
<https://github.com/luutifa/esfragt>

In case of anything: luutifa@gmail.com
