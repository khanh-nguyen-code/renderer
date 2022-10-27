# declaration
UNAME = $(shell uname)

COMMON_FLAGS = -g -std=c++17 -I include -L lib

ifeq ($(UNAME), Linux)
	# specific for Linux
	CC = gcc
	CFLAGS = $(COMMON_FLAGS) -Wall -fPIC `pkg-config --cflags glew glfw3`
	LDFLAGS = -l stdc++ `pkg-config --libs glew glfw3`
endif
ifeq ($(UNAME), Darwin)
	# specific for MacOS
	CC = clang
	CFLAGS = $(COMMON_FLAGS) -Wall -fPIC 
	LDFLAGS = -l stdc++
endif


# compile object
OBJECT_SRC_LIST = $(shell find src -name "*.cpp") # recursive wildcard
OBJECT_OUT_LIST = $(patsubst src/%.cpp,obj/%.o,$(OBJECT_SRC_LIST))
obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# link library
LIBRARY_SRC_LIST = $(wildcard src/*)
LIBRARY_OUT_LIST = $(patsubst src/%,lib/lib%.so,$(LIBRARY_SRC_LIST))
lib/lib%.so: # not sure how to put in the dependencies here
	@mkdir -p lib
	$(CC) $(CFLAGS) -shared -o $@ obj/$*/*.o $(LDFLAGS)

# compile and link target
TARGET_SRC_LIST = $(wildcard target/*.cpp)
TARGET_OUT_LIST = $(patsubst target/%.cpp,bin/%,$(TARGET_SRC_LIST))
THIS_LDFLAGS = $(patsubst src/%,-l %,$(LIBRARY_SRC_LIST))
bin/%: target/%.cpp
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(THIS_LDFLAGS)

all: $(OBJECT_OUT_LIST) $(LIBRARY_OUT_LIST) $(TARGET_OUT_LIST)

clean:
	rm -rf obj lib bin

.PHONY: clean all
