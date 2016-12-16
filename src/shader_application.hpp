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

#include "3dapp_window.hpp"
#include "3dapp_application.hpp"
#include "application_config.hpp"
#include "3dapp_program.hpp"
#include "3dapp_scaling_rectangle.hpp"
#include "3dapp_framebuffer.hpp"
#include "3dapp_texture.hpp"

class ShaderApplication: public Lib3dapp::Application {
    public:
        ShaderApplication(Lib3dapp::Window& win, ApplicationConfig& conf);
        ~ShaderApplication();
        virtual void draw();
    
    private:
        Lib3dapp::Program shader;
        ApplicationConfig& config;
        Lib3dapp::Program SHScaler;
        Lib3dapp::Program* SHPost;
        Lib3dapp::ScalingRectangle SCRectScaler;
        Lib3dapp::Framebuffer FBScaler;
        Lib3dapp::Framebuffer FBPost;
        Lib3dapp::Texture** textures;
};
