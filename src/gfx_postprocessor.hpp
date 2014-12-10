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

#ifndef GFX_POSTPROCESSOR_HPP
#define GFX_POSTPROCESSOR_HPP

#include "rpi_gfx.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include <string>
#include <vector>

class GfxPostProcessor {
    public:
        GfxPostProcessor(unsigned int w, unsigned int h, float* it, std::string vs);
        ~GfxPostProcessor();
        void draw();
        void bindFramebuffer();
    private:
        GfxTexture2D* iChannel0;
        GfxShader shaderProgram;
        float* t;
        GLfloat vertices[8];
        GLuint frameBuffer;
        GLuint renderBuffer;
};

#endif
