# Copyright 2014-2016 Lauri Gustafsson
#
# This file is part of esfragt.
#
#     esfragt is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     esfragt is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with esfragt, see COPYING. If not, see <http://www.gnu.org/licenses/>.
#

# A makefile to build esfragt.

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
TARGET=esfragt
CFLAGS+=-O3 -MMD -MP
debug:CFLAGS=-g
raspi:CFLAGS+=-DRASPI_BUILD
INCLUDES=-I./lib3dapp/src/include
raspi:INCLUDES+=-I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -I./ -I/opt/vc/src/hello_pi/libs/ilclient -I/opt/vc/src/hello_pi/libs/vgfont
LFLAGS=-L./lib3dapp/src/
raspi:LFLAGS+=-L/opt/vc/lib/
LIBS=-lGL -lSDL2 -lGLEW -l3dapp
raspi:LIBS=-lGLESv2 -lEGL -lbcm_host -lSDL -l3dapp
CC=g++

default: $(TARGET)
	strip --strip-all $(TARGET)
	@echo "Finished."

raspi: $(TARGET)
	strip --strip-all $(TARGET)
	@echo "Finished."

debug: $(TARGET)
	@echo "Finished"

$(TARGET): $(OBJS)
	cd lib3dapp/src; $(MAKE) $(MAKECMDGOALS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS) $(LIBS_CUSTOM)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	cd lib3dapp/src; $(MAKE) clean
	find ./ -type f -name "*.o" -delete
	find ./ -type f -name "*.d" -delete
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/


-include *.d
