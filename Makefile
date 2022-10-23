CC = g++
CFLAGS = -Wall -g -std=c++17 -fPIC -I . -I include -L lib `pkg-config --cflags glew glfw3`
LDFLAGS = `pkg-config --libs glew glfw3`
LIBRARY = Renderer
TARGET = run
SHADER_FILE = shader.h

LIBRARY_FILE = lib/lib$(LIBRARY).so

# $(wildcard src/*.cpp): get all .cpp files from the current directory and dir "src/"
SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(SRC_FILES))

$(TARGET): $(SHADER_FILE) $(LIBRARY_FILE)
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(LDFLAGS) -l $(LIBRARY)
	LD_LIBRARY_PATH=lib ./$(TARGET)

$(SHADER_FILE):
	rm -f shader.h
	touch shader.h
	echo "#ifndef __SHADER_H__" >> shader.h
	echo "#define __SHADER_H__" >> shader.h
	xxd -i -n shader data/shaders/image2d.shader >> shader.h
	echo "#endif // __SHADER_H__" >> shader.h

$(LIBRARY_FILE): $(OBJ_FILES)
	mkdir -p lib
	$(CC) $(CFLAGS) -shared -o $(LIBRARY_FILE) obj/*.o $(LDFLAGS)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(LIBRARY_FILE) $(SHADER_FILE) $(OBJ_FILES)
	
.PHONY: $(TARGET) clean