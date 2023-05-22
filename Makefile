LIBS = sfml-graphics sfml-system sfml-window

OS = $(shell uname)

CFLAGS = -std=c++11 -g -ggdb -Iinclude -Wall $(shell pkg-config --cflags $(LIBS))
LFLAGS = $(shell pkg-config --libs $(LIBS)) -lm
ifeq ($(OS),Darwin)
	CFLAGS += -DGL_SILENCE_DEPRECATION
	LFLAGS += -framework OpenGL
endif

OBJS := $(patsubst  src/%.cpp, obj/%.o, $(wildcard src/*.cpp))
DEPS := $(wildcard include/*.hpp)
CXX = g++
EXEC = main

all: $(EXEC)

obj:
	[ -d obj ] || mkdir obj

obj/%.o: src/%.cpp $(DEPS) | obj
	$(CXX) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS) $(LFLAGS)
