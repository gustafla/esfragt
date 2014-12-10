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

#include "gfx_postprocessor.hpp"
#include "util.hpp"
#include "text.hpp"
#include <string>

GfxPostProcessor::GfxPostProcessor(unsigned int w, unsigned int h, float* it, std::string fs):
t(it) {
    //Load, compile, enable shaders
    std::string* fsTemp = new std::string;
    if (!loadFile(fs, *fsTemp))
        exit(40);
    if(shaderProgram.compProgram(SIMPLE_VS, *fsTemp) == GL_FALSE)
        exit(1);
    delete fsTemp;
    glUseProgram(shaderProgram.getHandle());
    
    GLfloat res[2] = {
        w,
        h
    };

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    //Set miscellanous shader uniform pointers
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, t);

    check();

    iChannel0 = new GfxTexture2D(NULL, res[0], res[1], 0, GL_RGBA, GL_LINEAR, GL_CLAMP_TO_EDGE);
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, iChannel0->getHandle(), 0);
    
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, res[0], res[1]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

    //Here's our screen rectangle
    vertices[0] = -1.0f;
    vertices[1] = -1.0f;
    vertices[2] = -1.0f;
    vertices[3] = 1.0f;
    vertices[4] = 1.0f;
    vertices[5] = 1.0f;
    vertices[6] = 1.0f;
    vertices[7] = -1.0f;
}

GfxPostProcessor::~GfxPostProcessor() {
    delete iChannel0;
    glDeleteRenderbuffers(1, &renderBuffer);
    glDeleteFramebuffers(1, &frameBuffer);
}

void GfxPostProcessor::draw() {
    //Drawing will happen with this shader, and these (this) texture
    glUseProgram(shaderProgram.getHandle());
    iChannel0->bindToUnit(0);
    //Update time
    glUniform1fv(shaderProgram.getUfmHandle("iGlobalTime"), 1, t);

    //YOU NEED TO CALL UNIFORM AND ATTRIBUTE UPDATES ON EVERY FRAME, EVEN IF IT WAS THE POINTER VARIANT "...v(*)"!

    //Drawing happens here
    glVertexAttribPointer(shaderProgram.getAtrHandle("v"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(shaderProgram.getAtrHandle("v"));

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void GfxPostProcessor::bindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}
