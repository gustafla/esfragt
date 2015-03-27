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
#ifndef GFX_TEXTURE_HPP
#define GFX_TEXTURE_HPP

#include "rpi_gfx.hpp"

class GfxTexture2D
{
    public:
        GfxTexture2D(const unsigned char* image, unsigned int w, unsigned int h, unsigned int bind=0, uint32_t format=GL_RGB, uint32_t filter=GL_NEAREST, uint32_t wrap=GL_REPEAT);
        ~GfxTexture2D();
        GLuint getHandle();
        void image2D(unsigned char* image, unsigned int w, unsigned int h, uint32_t format=GL_RGB);
        void bindToUnit(unsigned int unit);
        void bindToOwnUnit();
    private:
        GLuint handle;
        GLuint bound;
        unsigned int binding;
};

void gfxLoadTexture2D(const unsigned char* image, unsigned int w, unsigned int h, uint32_t format=GL_RGB, uint32_t filter=GL_NEAREST, uint32_t wrap=GL_REPEAT);

#endif
