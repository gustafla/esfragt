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

#include "graphics.hpp"
#include "application_config.hpp"
#include "window.hpp"
#include "shader_application.hpp"
#include <string>
#include <iostream>

void cleanup() {
    cleanupGraphics();
}

int main(int argc, char* argv[]) {
    initializeGraphics();
    atexit(cleanup);

    ApplicationConfig conf(argc, argv);
    std::string cap = "esfragt | ";
    cap += conf.fsName;
    Window win(conf, cap, vec2(conf.internalW, conf.internalH), conf.alpha);
    ShaderApplication application(win, conf);
    
    float tLast = win.getTime();
    float fps = 0.0f;
    unsigned int frames = 0;
    
    while (application.isRunning()) {
        application.draw();
        
        if (conf.fpsCounter) {
            frames++;
            if (win.getTime() >= tLast+conf.fpsCounterInterval) {
                fps = (float(frames)/conf.fpsCounterInterval);
                std::cout << "FPS: " << fps << "\n";
                frames=0;
                tLast=win.getTime();
            }
        }
    }
    return 0;
};
