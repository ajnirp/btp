#CPPFLAGS = -g -I./SDL
CPPFLAGS = -O3 -I./SDL
LIBS = -lSDL -lGL -lGLU -lpthread -lm


all: fluid.o main.o genfunc.o viewer.o trackball.o FragmentUtils.o spectrum.o
	g++ $(LIBS) -o fluid main.o fluid.o genfunc.o viewer.o trackball.o FragmentUtils.o spectrum.o

genfunctest: genfunctest.o genfunc.o
	g++ $(LIBS) -o genfunctest genfunctest.o genfunc.o

clean:
	rm *.o
