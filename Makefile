#
# David Harrigan
# 
# install_name_tool -change ./libfmodex.dylib fmod/lib/fmodex.dylib visualizer

PROG = visualizer
MYCPPFLAGS = -std=c++11 

# -------------------- set system-dependent variables ----------------
OS := $(shell uname)

ifeq ($(OS), Darwin)
    CC = clang
    CCC = clang++
    LINKER = clang++
    GL_INC      = -I/Library/Frameworks/GLUI.framework/Headers \
                  -I/System/Library/Frameworks/GLUT.framework/Headers \
                  -I/System/Library/Frameworks/OpenGL.framework/Headers 
    GL_LIBS     = -framework OpenGL -framework GLUT
    FMOD        = fmod/lib/libfmodex.dylib
else
    CC          = gcc 
    CCC         = g++
    LINKER      = g++
    GL_INC      = -I/usr/X11/include/GL
    GL_LIBS     = -lglut -lGLU -lGL -lm -lGLEW
    FMOD        = fmod/lib/libfmodex.so
endif

# -------------- Common specifications ---------------------------------

MAKEFILE    = Makefile
X_INC       = -I/usr/X11/include
XLIBS       = -L/usr/X11/lib 
LIBS = $(XLIBS) $(GL_LIBS) $(FMOD_LIBS)
#-lportaudio -lsndfile -ljack -lrt -lasound

# -------------- Compiler and Linker flags ---------------
CPPFLAGS    = -Wall $(MYCPPFLAGS) $(GL_INC) $(X_INC) 

#
# If any linker flags are needed, they should be prefixed by "-Wl," 
# This insures that cpp or cc will not confuse these flags with ones
# intended for it.
# 
LDFLAGS     = 

#---------- Application info ------------------------------------------

SRCS = $(wildcard *cpp) $(FMOD)

# for every .cpp input, need to produce a .o
OBJS = $(SRCS:.cpp=.o) 

#------------------- dependencies/actions ------------------------
# dependency: need1 need2 ...  
#         action(s)
#
all:	build 
    

build: compile $(PROG)

compile: $(OBJS) 

new:	clean all

%.o : %.cpp %.h
	$(CCC) -c $(CPPFLAGS) $*.cpp

%.o : %.cpp
	$(CCC) -c $(CPPFLAGS) $*.cpp

$(PROG): $(OBJS) $(COBJS)
	$(LINKER) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROG)

run:
	./$(PROG) title-theme.mp3 transmission.mp3 kokiri-forest.mp3 get-lucky.mp3

clean:
	rm -f *.o $(PROG)
