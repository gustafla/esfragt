// Copyright 2014-2016 Lauri Gustafsson
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
                             "uniform sampler2D iChannel3; "
                             "uniform sampler2D iChannel4; "
                             "uniform sampler2D iChannel5; "
                             "uniform sampler2D iChannel6; "
                             "uniform sampler2D iChannel7; ";

const std::string VERSION = "GL ES Fragment Shader Thingy - esfragt 3.0.1\n"
                            "Copyright 2014-2016 Lauri Gustafsson.\n\n"
                            
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

const std::string DOC = "Usage: esfragt [OPTION]... FILE\n"
                        "Load and run a GLSL fragment shader source.\n"
                        "\n"
                        "  -w                window width\n"
                        "  -h                window height\n"
                        "  -x                internal width\n"
                        "  -y                internal height\n"
                        "  -f                print out an FPS reading after every n second(s)\n"
                        "                    (default 2)\n"
                        "  -d                window alpha (default 1.0)\n"
                        "  -i                specify an image file, only TGA supported\n"
                        "                    order of parameter decides iChannelX number\n"
                        "  -p                also run a post processing shader file.\n"
                        "                    \"iChannel0\" is frame input.\n"
                        "  --fullscreen      Start fullscreen\n"
                        "      --help        display this help and exit\n"
                        "      --version     display version information and exit\n"
                        "\n"
                        "With no FILE, try esfragt.frag\n"
                        "\n"
                        "Your shader will be running on two triangles\n"
                        "with a minimal vertex shader, filling the window.\n\n"
                        "Available uniforms:\n"
                        "\n"
                        "uniform vec2 iResolution        window resolution\n"
                        "uniform float iGlobalTime       time in seconds since program start\n"
                        "uniform sampler2D iChannel0-3   optional input data (images for now)\n"
                        "\n"
                        "You can report bugs or send mail/spam/\"offers\" to luutifa@gmail.com\n"
                        "esfragt home page: <http://luutifa.tk/esfragt/>\n";

const std::string SIMPLE_VS = "attribute vec3 a_position;\n"
                              "attribute vec3 a_normal;\n"
                              "attribute vec2 a_texpos;\n"
                              "void main(){gl_Position=vec4(a_position,1.0);}\n";
                              
const std::string SIMPLE_VS_TEXVAR = "attribute vec3 a_position;\n"
                                     "attribute vec3 a_normal;\n"
                                     "attribute vec2 a_texcoord;\n"
                                     "varying vec2 v_texcoord;\n"
                                     "void main(){\n"
                                     "v_texcoord=a_texcoord;\n"
                                     "gl_Position=vec4(a_position,1.0);}\n";
                              
const std::string SIMPLE_FS = "varying vec2 v_texcoord;\n"
                              "uniform sampler2D iChannel0;\n"
                              "void main(){\n"
                              "gl_FragColor=texture2D(iChannel0,v_texcoord);}\n";
