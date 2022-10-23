CC = cc

CFLAGS = -Wall -g -std=c++17 -fPIC -I . -I include -L lib `pkg-config --cflags glew glfw3`
LDFLAGS = -l stdc++ `pkg-config --libs glew glfw3`
LIBRARY = Renderer

LIBRARY_FILE = lib/lib$(LIBRARY).so

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
LDFLAGS += -framework OpenGL
endif

# $(wildcard src/*.cpp): get all .cpp files from current dir
TRG_FILES = $(wildcard *.cpp)
# $(patsubst %.cpp,%, $(TRG_FILES)): change all .cpp files in current dir into exec files
TRG_EXECS = $(patsubst %.cpp,%, $(TRG_FILES))
# $(wildcard src/*.cpp): get all .cpp files from "src/"
SRC_FILES = $(wildcard src/*.cpp)
# $(patsubst src/%.cpp,obj/%.o,$(SRC_FILES)): change all .cpp files in "src/" into "obj/.o"
OBJ_FILES = $(patsubst src/%.cpp,obj/%.o,$(SRC_FILES))

build: dir shader $(LIBRARY_FILE) $(TRG_EXECS)
	echo "done"

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -l $(LIBRARY)

shader:
	rm -rf include/shaders
	mkdir -p include/shaders
	touch include/shaders/image2d.h
	echo "#ifndef __IMAGE2D_SHADER_H__" >> include/shaders/image2d.h
	echo "#define __IMAGE2D_SHADER_H__" >> include/shaders/image2d.h
	echo "namespace shader {" >> include/shaders/image2d.h
	xxd -i -n image2d data/shaders/image2d.shader >> include/shaders/image2d.h
	echo "}" >> include/shaders/image2d.h
	echo "#endif // __IMAGE2D_SHADER_H__" >> include/shaders/image2d.h

$(LIBRARY_FILE): dir $(OBJ_FILES)
	$(CC) $(CFLAGS) -shared -o $(LIBRARY_FILE) $(OBJ_FILES) $(LDFLAGS)

dir:
	mkdir -p lib obj

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TRG_EXECS) lib obj
	
.PHONY: build shader dir clean
