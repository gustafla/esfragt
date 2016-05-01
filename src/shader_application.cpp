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

#include "shader_application.hpp"
#include "geo_primitives.hpp"
#include "text.hpp"
#include "tga_file.hpp"
#include <string>
#include <cstring>

void setEsfragtTextureUniforms(Program& shader, unsigned int n) {
    shader.use();
    char tmpNum[8];
    std::string tmp;
    for (int i=0; i<n; i++) {
        tmp = "iChannel";
        sprintf(tmpNum, "%d", i);
        tmp += std::string(tmpNum);
        glUniform1i(shader.getUfmHandle(tmp), i);
    }
}

ShaderApplication::ShaderApplication(Window& win, ApplicationConfig& conf):
Application(win),
config(conf),
shader(Program(Shader(SIMPLE_VS, GL_VERTEX_SHADER, "SIMPLE_VS"), Shader::loadFromFile(conf.fsName))),
SHScaler(Program(Shader(SIMPLE_VS_TEXVAR, GL_VERTEX_SHADER, "SIMPLE_VS_TEXVAR"), Shader(SIMPLE_FS, GL_FRAGMENT_SHADER, "SIMPLE_FS"))),
SHPost(NULL),
FBScaler(conf.internalW, conf.internalH),
FBPost(conf.internalW, conf.internalH),
SCRectScaler(vec2(conf.internalW, conf.internalH), vec2(conf.w, conf.h)) {
    if (conf.ppName.length()) {
        SHPost = new Program(Shader(SIMPLE_VS, GL_VERTEX_SHADER, "SIMPLE_VS"), Shader::loadFromFile(conf.ppName));
        SHPost->use();
        setEsfragtTextureUniforms(*SHPost, 1);
        glUniform2f(SHPost->getUfmHandle("iResolution"), conf.internalW, conf.internalH);
    }
    if (conf.inames.size()) {
        textures = new Texture*[conf.inames.size()];
        for (int i=0; i<conf.inames.size(); i++) {
            textures[i] = new Texture(loadTGAFile(conf.inames[i]));
        }
    }
    
    setEsfragtTextureUniforms(SHScaler, 1);
    setEsfragtTextureUniforms(shader, 4);
    glUniform2f(shader.getUfmHandle("iResolution"), conf.internalW, conf.internalH);
}

ShaderApplication::~ShaderApplication() {
    if (SHPost)
        delete SHPost;
    for (int i=0; i<config.inames.size(); i++) {
        delete textures[i];
    }
    if (config.inames.size()) {
        delete textures;
    }
}

void ShaderApplication::draw() {
    if (SHPost) {
        FBPost.bind();
    } else {
        FBScaler.bind();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i=0; i<config.inames.size(); i++) {
        textures[i]->bindToUnit(i);
    }
    shader.use();
    glUniform1f(shader.getUfmHandle("iGlobalTime"), window.getTime());
    GeoPrimitives::singleton().quad.draw(shader);
    
    if (SHPost) {
        FBScaler.bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        FBPost.getTexture().bindToUnit(0);
        SHPost->use();
        glUniform1f(SHPost->getUfmHandle("iGlobalTime"), window.getTime());
        GeoPrimitives::singleton().quad.draw(*SHPost);
    }
    
    window.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    FBScaler.getTexture().bindToUnit(0);
    SHScaler.use();
    SCRectScaler.draw(SHScaler);
    
    window.swapBuffers();
}
