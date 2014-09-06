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

#include "rpi_gfx.hpp"

void check()
{
    static GLenum error;
    error = glGetError();

    if (error)
    {
        if (error == GL_OUT_OF_MEMORY)
            std::cout << "GPU OUT OF MEMORY! ;__;\n";
        if (error == GL_INVALID_OPERATION)
            std::cout << "Invalid GL operation. Fix your/my code.\n";
        exit(error);
    }
}
