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

#include "config.hpp"
#include "util.hpp"
#include "text.hpp"
#include <cstdlib>
#include <iostream>
#include <cstring>

Config::Config(int argc, char* argv[]):
fsName("esfragt.frag"),
w(256),
h(256),
stretch(1),
devmode(false),
prepend(false),
fpsCounter(false),
fpsIn(100),
imgs(0)
{
    /*YAY crappy parameter checking ^__^*/
    bool gotName = false;
    for (int n=1; n<argc; n++)
    {
        if (!strcmp(argv[n], "-w"))
        {
            n++;
            checkValueParam(n, argc, argv);
            w = atoi(argv[n]);
        }
            else if (!strcmp(argv[n], "-h"))
            {
                n++;
                checkValueParam(n, argc, argv);
                h = atoi(argv[n]);
            }
                else if (!strcmp(argv[n], "-s"))
                {
                    n++;
                    checkValueParam(n, argc, argv);
                    w = h = atoi(argv[n]);
                }
                    else if (!strcmp(argv[n], "--help"))
                    {
                        std::cout << DOC;
                        exit(0);
                    }
                        else if (!strcmp(argv[n], "--version"))
                        {
                            std::cout << VERSION;
                            exit(0);
                        }
                            else if (!strcmp(argv[n], "-f"))
                            {
                                fpsCounter = true;
                                if ((n+1)!=argc)
                                {
                                    std::string tmp = argv[n+1];
                                    if (isdigits(tmp))
                                    {
                                        n++;
                                        fpsIn = atoi(argv[n]);
                                    }
                                }
                            }
                                else if (!strcmp(argv[n], "-d"))
                                {
                                    devmode = true;
                                }
                                    else if (!strcmp(argv[n], "-u"))
                                    {
                                        prepend = true;
                                    }
                                        else if (!strcmp(argv[n], "-c"))
                                        {
                                            n++;
                                            checkValueParamf(n, argc, argv);
                                            stretch = atof(argv[n]);
                                            if (stretch < 1)
                                            {
                                                std::cout << ARGERR;
                                                exit(4);
                                            }
                                        }
                                            else if (!strcmp(argv[n], "-i"))
                                            {
                                                if (imgs >= 4)
                                                {
                                                    std::cout << "Too many images\n" << ARGERR;
                                                    exit(6);
                                                }
                                                n++;
                                                if (n==argc)
                                                {
                                                    std::cout << ARGERR;
                                                    exit(20);
                                                }
                                                inames[imgs]=argv[n];
                                                imgs++;
                                            }
                                                else if (!gotName)
                                                {
                                                    fsName = argv[n];
                                                    gotName = true;
                                                }
                                                    else
                                                    {
                                                        std::cout << ARGERR;
                                                        exit(5);
                                                    }
    }

    h /= stretch;
    w /= stretch;
}
