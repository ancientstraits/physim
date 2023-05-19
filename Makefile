LIBS = sfml-all

CFLAGS = -g -ggdb -Iinclude -Wall $(shell pkg-config --cflags $(LIBS))
LFLAGS = $(shell pkg-config --libs $(LIBS)) -lm

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
