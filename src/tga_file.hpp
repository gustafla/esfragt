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

#ifndef TGA_FILE_HPP
#define TGA_FILE_HPP

#include <fstream>
#include <string>

class TGAFile
{
public:
    bool load(std::string filename);
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getBpp(); //bits per pixel
    unsigned char* getImage();

    ~TGAFile();
protected:
    void errorPrint(std::string);
    bool loadUncompressed();
    bool loadCompressed();
    bool loadHeader();
    std::ifstream file;
    unsigned char header[6];
    unsigned char* imageData;
    unsigned int imageSize;
    unsigned int bpp;
    unsigned int width;
    unsigned int height;
};

#endif
