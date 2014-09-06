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

#include "text.hpp"
#include <string>

const std::string UNIFORMS = "uniform vec2 iResolution; "
                             "uniform float iGlobalTime; "
                             "uniform sampler2D iChannel0; "
                             "uniform sampler2D iChannel1; "
                             "uniform sampler2D iChannel2; "
                             "uniform sampler2D iChannel3; ";

const std::string VERSION = "GL ES Fragment Shader Thingy - esfragt 1.6.3\n"
                            "Copyright 2014 Lauri Gustafsson.\n\n"
                            
                            "esfragt is free software: you can redistribute it and/or modify\n"
                            "it under the terms of the GNU General Public License as published by\n"
                            "the Free Software Foundation, either version 3 of the License, or\n"
                            "(at your option) any later version.\n\n"

                            "esfragt is distributed in the hope that it will be useful,\n"
                            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                            "GNU General Public License for more details.\n\n"

                            "You should have received a copy of the GNU General Public License\n"
                            "along with esfragt, see COPYING. If not, see <http://www.gnu.org/licenses/>.\n";

const std::string ARGERR = "Go fix your parameters.\n"
                           "Try 'esfragt --help' for more information.\n";

const std::string DOC = "Usage: esfragt [OPTION]... FILE\n"
                        "Load a GLSL fragment shader source and run it in a dispmanx window.\n"
                        "\n"
                        "  -w                window width\n"
                        "  -h                window height\n"
                        "  -s                window width and height, a square\n"
                        "  -c                divide backbuffer size by n, prone to rounding error\n"
                        "  -f                print out a FPS reading after every n frame(s)\n"
                        "                    (default 100)\n"
                        "  -d                enable alpha blending with window background\n"
                        "  -u                prepend all uniforms to FILE\n"
                        "                    (first line can't be a preprocessor instruction,\n"
                        "                    recommended leaving it empty)\n"
                        "  -i                specify an image file, only TGA supported\n"
                        "                    order of parameter decides iChannel number\n"
                        "      --help        display this help and exit\n"
                        "      --version     display version information and exit\n"
                        "\n"
                        "With no FILE, try esfragt.frag\n"
                        "\n"
                        "Your shader will be running on two triangles\n"
                        "with a minimal vertex shader, filling the window.\n"
                        "Available uniforms:\n"
                        "\n"
                        "uniform vec2 iResolution        window resolution\n"
                        "uniform float iGlobalTime       time in seconds since program start\n"
                        "uniform sampler2D iChannel0-3   optional input data (images for now)\n"
                        "\n"
                        "You can report bugs or send mail/spam/\"offers\" to luutifa@gmail.com\n"
                        "esfragt home page: <http://luutifa.tk/esfragt/>\n";
