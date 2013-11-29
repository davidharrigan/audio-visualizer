#
# David Harrigan
# 

PROG = visualizer
MYCPPFLAGS = -std=c++11    

# -------------------- set system-dependent variables ----------------
CC          = gcc 
CCC         = g++
LINKER      = g++
GL_INC      = -I/usr/X11/include/GL
GL_LIBS     = -lglui -lglut -lGLU -lGL 

# -------------- Common specifications ---------------------------------

MAKEFILE    = Makefile
X_INC       = -I/usr/X11/include
XLIBS       = -L/usr/X11/lib 
LIBS = $(XLIBS) $(GL_LIBS) -lportaudio -lsndfile -ljack -lrt -lasound

# -------------- Compiler and Linker flags ---------------
CPPFLAGS    = -Wall $(MYCPPFLAGS) $(GL_INC) $(X_INC) 

#
# If any linker flags are needed, they should be prefixed by "-Wl," 
# This insures that cpp or cc will not confuse these flags with ones
# intended for it.
# 
LDFLAGS     = 

#---------- Application info ------------------------------------------

SRCS = $(wildcard *cpp)

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
	./$(PROG)

clean:
	rm -f *.o $(PROG)
