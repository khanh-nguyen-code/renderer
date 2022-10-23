CC = gcc
CFLAGS = -Wall -g -std=c++17 -fPIC -I . -I include -L lib `pkg-config --cflags glew glfw3`
LDFLAGS = -l stdc++ `pkg-config --libs glew glfw3`
LIBRARY = Renderer
TARGET = run

LIBRARY_FILE = lib/lib$(LIBRARY).so

# $(wildcard src/*.cpp): get all .cpp files from the current directory and dir "src/"
SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(SRC_FILES))

$(TARGET): shader $(LIBRARY_FILE)
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(LDFLAGS) -l $(LIBRARY)
	LD_LIBRARY_PATH=lib ./$(TARGET)

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

$(LIBRARY_FILE): $(OBJ_FILES)
	mkdir -p lib
	$(CC) $(CFLAGS) -shared -o $(LIBRARY_FILE) obj/*.o $(LDFLAGS)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(LIBRARY_FILE) $(OBJ_FILES)
	
.PHONY: $(TARGET) shader clean
