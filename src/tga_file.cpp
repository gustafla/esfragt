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
#include <cstring>

void TGAFile::errorPrint(std::string filename)
{
    std::cout << filename << ": Failed to load TGA file\n";
}

bool TGAFile::load(std::string filename)
{
    unsigned char uTGAcompare[12]={0,0,2,0,0,0,0,0,0,0,0,0};
    unsigned char cTGAcompare[12]={0,0,10,0,0,0,0,0,0,0,0,0};
    unsigned char formatHeader[12];

    file.open(filename.c_str());
    if (!file.is_open())
    {
        std::cout << filename << ": No such file or directory\n";
        return false;
    }

    file.read((char*)formatHeader, sizeof(formatHeader));
    if (file.eof() || file.fail())
    {
        errorPrint(filename);
        return false;
    }

    if (!loadHeader())
    {
        errorPrint(filename);
        return false;
    }

    //imageData = (unsigned char*)malloc(imageSize);
    imageData = new unsigned char[imageSize];
    if (imageData == NULL)
    {
        errorPrint(filename);
        return false;
    }

    if (memcmp(uTGAcompare, formatHeader, sizeof(formatHeader))==0)
        if (!loadUncompressed())
        {
            errorPrint(filename);
            return false;
        }
    else if (memcmp(cTGAcompare, formatHeader, sizeof(formatHeader))==0)
        if (!loadCompressed())
        {
            errorPrint(filename);
            return false;
        }
    else
    {
        errorPrint(filename);
        return false;
    }

    return true;
}

unsigned int TGAFile::getWidth()
{
    return width;
}

unsigned int TGAFile::getHeight()
{
    return height;
}

unsigned int TGAFile::getBpp()
{
    return bpp;
}

unsigned char* TGAFile::getImage()
{
    return imageData;
}

bool TGAFile::loadHeader()
{
    file.read((char*)header, sizeof(header));
    if (file.eof() || file.fail())
        return false;

    width = header[1] * 256 + header[0];
    height = header[3] * 256 + header[2];
    bpp = header[4];

    if ((width <= 0) || (height <= 0) || ((bpp != 24) && (bpp != 32)))
        return false;

    imageSize = (bpp/8) * width * height;

    return true;
}

bool TGAFile::loadUncompressed()
{
    const unsigned short bytespp = bpp/8;

    file.read((char*)imageData, imageSize);
    if (file.fail())
        return false;

    for (unsigned int cswap = 0; cswap < imageSize; cswap+=bytespp)
    {
        imageData[cswap] ^= imageData[cswap+2] ^=
        imageData[cswap] ^= imageData[cswap+2];
    }

    file.close();
    return true;
}

bool TGAFile::loadCompressed()
{
    const unsigned short bytespp = bpp/8;

    const unsigned int pixelCount = width * height;
    unsigned int curPixel = 0;
    unsigned int curByte = 0;
    unsigned char* colBuf = (unsigned char*)malloc(bytespp);

    do
    {
        unsigned char chunkheader = 0;

        file.read((char*)&chunkheader, sizeof(unsigned char));
        if (file.fail())
            return false;

        if (chunkheader < 128)
        {
            chunkheader++;

            for (unsigned short counter = 0; counter < chunkheader; counter++)
            {
                file.read((char*)colBuf, bytespp);
                if (file.fail())
                    return false;

                imageData[curByte] = colBuf[2];
                imageData[curByte+1] = colBuf[1];
                imageData[curByte+2] = colBuf[0];
                if (bytespp == 4)
                    imageData[curByte+3] = colBuf[3];
                curByte += bytespp;
                curPixel++;
            }
        }
        else
        {
            chunkheader -= 127;

            file.read((char*)colBuf, bytespp);
            if (file.fail())
                return false;

            for (unsigned short counter = 0; counter < chunkheader; counter++)
            {
                imageData[curByte] = colBuf[2];
                imageData[curByte+1] = colBuf[1];
                imageData[curByte+2] = colBuf[0];
                if (bytespp == 4)
                    imageData[curByte+3] = colBuf[3];

                curByte += bytespp;
                curPixel++;
            }
        }
    } while (curPixel < pixelCount);

    file.close();
    delete colBuf;
    return true;
}

TGAFile::~TGAFile()
{
    delete[] imageData;
}
