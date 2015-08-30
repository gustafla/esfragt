# Copyright 2014, 2015 Lauri Gustafsson
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

SRCS=rpi_gfx.cpp main.cpp util.cpp config.cpp text.cpp gfx_EGL_window.cpp gfx_shader.cpp gfx_texture_2D.cpp tga_file.cpp gfx_postprocessor.cpp
TARGET=../esfragt
xwin:TARGET=../esfragt.xwin
OBJS=$(SRCS:.cpp=.o)
CFLAGS+=-O3 -fomit-frame-pointer -MMD -MP
xwin:CFLAGS=-O3 -fomit-frame-pointer -DUSE_X -MMD -MP
sdlwin:CFLAGS=-O3 -fomit-frame-pointer -DUSE_SDL -MMD -MP
debug:CFLAGS=-g
INCLUDES+=-I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux -I./ -I/opt/vc/src/hello_pi/libs/ilclient -I/opt/vc/src/hello_pi/libs/vgfont
xwin:INCLUDES=
sdlwin:INCLUDES=
LFLAGS=-L/opt/vc/lib/ -L/opt/vc/src/hello_pi/lib/ilclient -L/opt/vc/src/hello_pi/lib/vgfont
xwin:LFLAGS=
sdlwin:LFLAGS=
LIBS=-lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt
xwin:LIBS=-lGLESv2 -lEGL -lpthread -lX11
sdlwin:LIBS=-lGLESv2 -lSDL -lpthread
LIBS_CUSTOM =
CC=g++

all: $(TARGET)
	strip --strip-all $(TARGET)
	@echo "Finished."
	
xwin: $(TARGET)
	strip --strip-all $(TARGET)
	@echo "Finished."
	
sdlwin: $(TARGET)
	strip --strip-all $(TARGET)
	@echo "Finished."

debug: $(TARGET)
	@echo "Finished"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS) $(LIBS_CUSTOM)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o *.d *~ $(TARGET)
	rm -f $(TARGET).xwin

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/


-include *.d
