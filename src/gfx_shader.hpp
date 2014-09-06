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

#ifndef GFX_SHADER_HPP
#define GFX_SHADER_HPP

#include <map>
#include <string>
#include "rpi_gfx.hpp"

class GfxShader
{
public:
    GfxShader();
    GLuint getHandle();
    unsigned int getUfmHandle(std::string);
    unsigned int getAtrHandle(std::string);
    GLint compProgram(std::string vsString, std::string fsString);

protected:
    std::map<std::string, unsigned int> uniforms;
    std::map<std::string, unsigned int> attributes;

    GLuint compShader(GLenum type, const char* src);

    GLuint handle;
};

#endif
