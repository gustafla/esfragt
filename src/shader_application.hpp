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

#pragma once

#include "window.hpp"
#include "application.hpp"
#include "application_config.hpp"
#include "program.hpp"
#include "scaling_rectangle.hpp"
#include "framebuffer.hpp"
#include "texture.hpp"

class ShaderApplication: public Application {
    public:
        ShaderApplication(Window& win, ApplicationConfig& conf);
        ~ShaderApplication();
        virtual void draw();
    
    private:
        Program shader;
        ApplicationConfig& config;
        Program SHScaler;
        Program* SHPost;
        ScalingRectangle SCRectScaler;
        Framebuffer FBScaler;
        Framebuffer FBPost;
        Texture** textures;
};
