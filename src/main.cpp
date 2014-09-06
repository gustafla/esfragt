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

#include "tga_file.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "rpi_gfx.hpp"
#include "gfx_EGL_window.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "util.hpp"
#include "config.hpp"
#include "text.hpp"

/*     (some :D) ERROR CODES:
 *
 *  1 - Shader program failed to compile/link
 *  2 - Failed to create window
 */

using namespace std;

int main(int argc, char *argv[])
{
    Config c(argc, argv);
    GfxEGLWindow window(&c);
    if(!window.createWindow(GFX_WINDOW_RGB))
        exit(2);

    std::string* fsTemp = new std::string;
    if (c.prepend)
        *fsTemp = UNIFORMS;
    if (!loadFile(c.fsName, *fsTemp))
        exit(40);
    GfxShader shaderProgram;
    if(shaderProgram.compProgram("attribute vec4 v;\nvoid main(){gl_Position=v;}\n", *fsTemp) == GL_FALSE)
        exit(1);
    delete fsTemp;

    glReleaseShaderCompiler();
    glUseProgram(shaderProgram.getHandle());

    TGAFile* image;
    for (unsigned short counter = 0; counter < c.imgs; counter++)
    {
        std::cout << "Image " << counter << ": " << c.inames[counter] << std::endl;
        image = new TGAFile;
        image->load(c.inames[counter]);
        glActiveTexture(GL_TEXTURE0+counter);
        gfxLoadTexture2D(image->getImage(), image->getWidth(), image->getHeight(), ((image->getBpp() == 32) ? GL_RGBA : GL_RGB));
        delete image;
    }
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
    glUniform1i(shaderProgram.getUfmHandle("iChannel1"), 1);
    glUniform1i(shaderProgram.getUfmHandle("iChannel2"), 2);
    glUniform1i(shaderProgram.getUfmHandle("iChannel3"), 3);

    check();

    glEnable(GL_BLEND);
    if (!c.devmode)
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    else
        glBlendFunc(GL_ONE, GL_SRC_ALPHA);

    glViewport(0, 0, c.w, c.h);

    check();

    GLfloat rectangle[3*3*2] =
    {
        1.0f, -1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
       -1.0f, -1.0f,  0.0f,

       -1.0f, -1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
       -1.0f,  1.0f,  0.0f
    };

    GLfloat* res = new GLfloat[2];
    res[0] = c.w;
    res[1] = c.h;
    glUniform2fv(shaderProgram.getUfmHandle("iResolution"), 1, res);
    delete res;

    struct timeval tTmp;
    struct timeval startT;
    struct timezone tz;
    float t = 0.0f;
    float fpsLastT = 0.0f;
    unsigned int frames = 0;

    gettimeofday(&tTmp, &tz);
    gettimeofday(&startT, &tz);

    for (;;)
    {
        check();

        gettimeofday(&tTmp, &tz);
        t = static_cast<float>(tTmp.tv_sec - startT.tv_sec + ((tTmp.tv_usec - startT.tv_usec) * 1e-6));
        glUniform1f(shaderProgram.getUfmHandle("iGlobalTime"), t);

        glVertexAttribPointer(shaderProgram.getAtrHandle("v"), 3, GL_FLOAT, GL_FALSE, 0, rectangle);
        glEnableVertexAttribArray(shaderProgram.getAtrHandle("v"));

        glDrawArrays(GL_TRIANGLES, 0, 3*2);

        window.swapBuffers();

        if (c.fpsCounter)
        {
            frames++;
            if (frames > c.fpsIn)
            {
                cout << "FPS=" << (c.fpsIn / (t - fpsLastT)) << endl;
                fpsLastT = t;
                frames = 0;
            }
        }
    }
    return 0;
}
