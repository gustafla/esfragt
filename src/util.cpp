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

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "text.hpp"

using namespace std;

bool isdigits(std::string &s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

bool isfloat(std::string &s)
{
    return s.find_first_not_of("0123456789.") == std::string::npos;
}

void checkValueParam(int n, int argc, char* argv[])
{
    if (n==argc)
    {
        cout << ARGERR;
        sleep(5);
        exit(20);
    }

    string tmps = argv[n];

    if (!isdigits(tmps))
    {
        cout << ARGERR;
        sleep(5);
        exit(30);
    }
}

bool loadFile(std::string inFileName, std::string& outString, int linesize)
{
    std::ifstream inFile(inFileName.c_str());
    if (!inFile.is_open())
    {
        std::cout << inFileName << ": No such file\n";
        return false;
    }

    char tmp[(linesize)];

    while (!inFile.eof())
    {
        inFile.getline(tmp, linesize);
        outString += tmp;
        outString += "\n";
    }
    return true;
}

void checkValueParamf(int n, int argc, char* argv[])
{
    if (n==argc)
    {
        cout << ARGERR;
        sleep(5);
        exit(21);
    }

    string tmps = argv[n];

    if (!isfloat(tmps))
    {
        cout << ARGERR;
        sleep(5);
        exit(31);
    }
}

