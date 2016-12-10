SHELL      = /bin/sh
CXX        = g++
CXXFLAGS   = -Wall -Werror -O3 -std=c++11
LD         = g++
LDFLAGS    =

TARGET     = ./eckert
SOURCE_DIR = ./src/

SOURCES    = $(shell find $(SOURCE_DIR) -type f -name '*.cpp')
OBJECTS    = $(patsubst %.cpp,%.o,$(SOURCES))


all: $(TARGET)

$(TARGET): $(OBJECTS) $(COMMON)
	$(LD) -o$(TARGET) $(OBJECTS)

.c.o:
	$(CXX) -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJECTS) $(TARGET)
