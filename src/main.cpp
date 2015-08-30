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

#include "tga_file.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "rpi_gfx.hpp"
#include "gfx_EGL_window.hpp"
#include "gfx_shader.hpp"
#include "gfx_texture_2D.hpp"
#include "gfx_postprocessor.hpp"
#include "util.hpp"
#include "config.hpp"
#include "text.hpp"

/*     (some :D) ERROR CODES:
 *
 *  1 - Shader program failed to compile/link
 *  2 - Failed to create window
 */

int main(int argc, char *argv[])
{
    #ifndef USE_X
		#ifndef USE_SDL
			bcm_host_init();
		#else
			int err;
			if ((err=SDL_Init(SDL_INIT_EVERYTHING)) < 0) {
				std::cout << "SDL_Init() failed.\n";
				exit(err);
			}
		#endif
    #endif
    Config c(argc, argv);
    GfxEGLWindow window(&c);
    if(!window.createWindow(GFX_WINDOW_RGB))
        exit(2);
    std::cout << "Compiling primary shader...\n";
    std::string* fsTemp = new std::string;
    if (c.prepend)
        *fsTemp = UNIFORMS;
    if (!loadFile(c.fsName, *fsTemp))
        exit(40);
    GfxShader shaderProgram;
    if(shaderProgram.compProgram(SIMPLE_VS, fsTemp->c_str()) == GL_FALSE)
        exit(1);
    delete fsTemp;

    glUseProgram(shaderProgram.getHandle());

    TGAFile* image;
    std::vector<GfxTexture2D*> textures;
    for (unsigned short counter = 0; counter < c.imgs; counter++)
    {
        std::cout << "Image " << counter << ": " << c.inames[counter] << std::endl;
        image = new TGAFile;
        image->load(c.inames[counter]);
        textures.push_back(new GfxTexture2D(image->getImage(), image->getWidth(), image->getHeight(), counter, ((image->getBpp() == 32) ? GL_RGBA : GL_RGB)));
        delete image;
    }
    glUniform1i(shaderProgram.getUfmHandle("iChannel0"), 0);
    glUniform1i(shaderProgram.getUfmHandle("iChannel1"), 1);
    glUniform1i(shaderProgram.getUfmHandle("iChannel2"), 2);
    glUniform1i(shaderProgram.getUfmHandle("iChannel3"), 3);
    glUniform1i(shaderProgram.getUfmHandle("iChannel4"), 4);
    glUniform1i(shaderProgram.getUfmHandle("iChannel5"), 5);
    glUniform1i(shaderProgram.getUfmHandle("iChannel6"), 6);
    glUniform1i(shaderProgram.getUfmHandle("iChannel7"), 7);
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

    GfxPostProcessor* pp = NULL;
    if (c.ppName != "") {
        std::cout << "Compiling post processor shader...\n";
        pp = new GfxPostProcessor(c.w, c.h, &t, c.ppName);
    }

    glReleaseShaderCompiler();

    for(;;)
    {
        check();
        #ifdef USE_X
			glClear(GL_COLOR_BUFFER_BIT);
		#endif
        glUseProgram(shaderProgram.getHandle());
        if (pp) {
            pp->bindFramebuffer();
            if (c.clearPp)
                glClear(GL_COLOR_BUFFER_BIT);
        }
        gettimeofday(&tTmp, &tz);
        t = static_cast<float>(tTmp.tv_sec - startT.tv_sec + ((tTmp.tv_usec - startT.tv_usec) * 1e-6));
        glUniform1f(shaderProgram.getUfmHandle("iGlobalTime"), t);

        if (c.resetTime > 0.01) {
            if (t>c.resetTime) {
                gettimeofday(&startT, &tz);
            }
        }

        for (int n=0; n<c.imgs; n++) {
            textures[n]->bindToOwnUnit();
        }
        
        glVertexAttribPointer(shaderProgram.getAtrHandle("v"), 3, GL_FLOAT, GL_FALSE, 0, rectangle);
        glEnableVertexAttribArray(shaderProgram.getAtrHandle("v"));

        glDrawArrays(GL_TRIANGLES, 0, 3*2);
        if (pp) {
            gfxBindFB0();
            pp->draw();
        }
        window.swapBuffers();
        glClear(GL_COLOR_BUFFER_BIT);
        
        if (pp)
            glClear(GL_COLOR_BUFFER_BIT);

        if (c.fpsCounter)
        {
            frames++;
            if (frames > c.fpsIn)
            {
                std::cout << "FPS=" << (c.fpsIn / (t - fpsLastT)) << std::endl;
                fpsLastT = t;
                frames = 0;
            }
        }
    }
    return 0;
}
