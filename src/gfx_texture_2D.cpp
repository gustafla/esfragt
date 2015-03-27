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

#include "gfx_texture_2D.hpp"
#include <iostream>

GfxTexture2D::GfxTexture2D(const unsigned char* image, unsigned int w, unsigned int h, unsigned int bind, uint32_t format, uint32_t filter, uint32_t wrap) {
    glActiveTexture(GL_TEXTURE0+bind);
    binding = bind;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
}

GfxTexture2D::~GfxTexture2D() {
    glDeleteTextures(1, &handle);
}

GLuint GfxTexture2D::getHandle()
{
    return handle;
}

void GfxTexture2D::bindToUnit(unsigned int unit) {
    glActiveTexture(GL_TEXTURE0+unit);
    glBindTexture(GL_TEXTURE_2D, handle);
    bound = unit;
}

void GfxTexture2D::bindToOwnUnit() {
    bindToUnit(binding);
}

void GfxTexture2D::image2D(unsigned char* image, unsigned int w, unsigned int h, uint32_t format) {
    bindToUnit(0);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
}

void gfxLoadTexture2D(const unsigned char* image, unsigned int w, unsigned int h, uint32_t format, uint32_t filter, uint32_t wrap)
{
    GLuint handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);
}
