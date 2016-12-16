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

#include "application_config.hpp"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "text.hpp"
#include "3dapp_util.hpp"
#include "3dapp_consts.hpp"

using namespace Lib3dapp;

ApplicationConfig::ApplicationConfig(int argc, char* argv[]):
Config(argc, argv),
alpha(1.0f),
fsName("esfragt.frag"),
ppName(""),
fpsCounter(false),
fpsCounterInterval(2.0f){
    int i;
    bool gotFileName = false;
    
    internalW = w;
    internalH = h;
    
    bool pass;
    for(i=1; i<argc; i++) {
        pass=false;
        for (int j=0; j<Config::NUM_RESERVED_PARAMS; j++) {
            if (strcmp(argv[i], Config::reservedParams[j].parameter.c_str()) == 0) {
                i+=reservedParams[j].extra;
                pass = true;
            }
        }
        if (pass) {
            continue;
        } else if (strcmp(argv[i], "--help") == 0) {
            std::cout << DOC;
            exit(0);
        } else if (strcmp(argv[i], "--version") == 0) {
            std::cout << VERSION;
            exit(0);
        } else if (strcmp(argv[i], "-d") == 0) {
            if (i+1 < argc) {
                i++;
                if (isfloat(argv[i])) {
                    alpha = atof(argv[i]);
                } else {
                    argErr(argv[i]);
                }
            } else {
                argErr(argv[i]);
            }
        } else if (strcmp(argv[i], "-x") == 0) {
            if (i+1 < argc) {
                i++;
                if (isfloat(argv[i])) {
                    internalW = atof(argv[i]);
                } else {
                    argErr(argv[i]);
                }
            } else {
                argErr(argv[i]);
            }
        } else if (strcmp(argv[i], "-y") == 0) {
            if (i+1 < argc) {
                i++;
                if (isfloat(argv[i])) {
                    internalH = atof(argv[i]);
                } else {
                    argErr(argv[i]);
                }
            } else {
                argErr(argv[i]);
            }
        } else if (strcmp(argv[i], "-p") == 0) {
            if (i+1 < argc) {
                i++;
                ppName = argv[i];
            } else {
                argErr(argv[i]);
            }
        } else if (strcmp(argv[i], "-f") == 0) {
            fpsCounter = true;
            if (i+1 < argc) {
                if (isfloat(argv[i+1])) {
                    i++;
                    fpsCounterInterval = atof(argv[i]);
                }
            }
        } else if (strcmp(argv[i], "-i") == 0) {
            if (inames.size() < 4) {
                if (i+1 < argc) {
                    i++;
                    inames.push_back(std::string(argv[i]));
                } else {
                    argErr(argv[i]);
                }
            } else {
                std::cout << "Too many images. Maximum is 4.\n";
                exit(ERR_INVALID_ARGUMENT);
            }
        } else if (!gotFileName) {
            fsName = argv[i];
            gotFileName = true;
        } else {
            argErr(argv[i]);
        }
    }
}
