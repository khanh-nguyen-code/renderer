CC = g++
CFLAGS = -Wall -g -std=c++17 -fPIC -I . -I include -L lib `pkg-config --cflags glew glfw3`
LDFLAGS = `pkg-config --libs glew glfw3`
LIBRARY = Renderer
TARGET = run.out

# $(wildcard src/*.cpp): get all .cpp files from the current directory and dir "src/"
SRCS := $(wildcard src/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst src/%.cpp,obj/%.o,$(SRCS))

$(TARGET): shader build
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(LDFLAGS) -l $(LIBRARY)
	LD_LIBRARY_PATH=lib ./$(TARGET)

shader:
	rm -f shader.h
	touch shader.h
	echo "#ifndef __SHADER_H__" >> shader.h
	echo "#define __SHADER_H__" >> shader.h
	xxd -i -n shader data/shaders/image2d.shader >> shader.h
	echo "#endif // __SHADER_H__" >> shader.h

build: $(OBJS)
	mkdir -p lib
	$(CC) $(CFLAGS) -shared -o lib/lib$(LIBRARY).so obj/*.o $(LDFLAGS)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) lib obj
	
.PHONY: run build clean