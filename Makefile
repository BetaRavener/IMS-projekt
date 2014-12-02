# Variables
PROJECT = dol
BIN_MAIN = $(PROJECT)

CXX = g++
RM = rm -rf
ZIP = zip -r

CFLAGS = -Wall -Wextra -c --std=c++11
CFLAGS_RELEASE = -O2
CFLAGS_DEBUG = -O0 -g -DDEBUG

LFLAGS = -lm -lsimlib
LFLAGS += $(shell command -v g++-4.8 >/dev/null 2>&1 && echo -n "-static-libstdc++")

SRC_FOLDER = src
BIN_FOLDER = bin
OBJ_FOLDER = obj

ZIP_FILE = 02_xsevci50_xstrak25.zip
PACKED_FILES = src/* inc/* Makefile README.md doc-DOL.pdf

INCLUDES = -Iinc

MAIN_SRCS = $(wildcard $(SRC_FOLDER)/*.cpp)
MAIN_OBJS = $(addprefix $(OBJ_FOLDER)/, $(notdir $(patsubst %.cpp, %.o, $(MAIN_SRCS))))

# Targets
release: CFLAGS += $(CFLAGS_RELEASE)
release: build

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: build

build: main

main: $(MAIN_OBJS)
	$(CXX) $^ -o $(BIN_FOLDER)/$(BIN_MAIN) $(LFLAGS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	@mkdir -p $(BIN_FOLDER) $(OBJ_FOLDER)
	$(CXX) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	$(RM) $(BIN_FOLDER) $(OBJ_FOLDER) $(ZIP_FILE)

pack:
	$(ZIP) $(ZIP_FILE) $(PACKED_FILES)

.PHONY: build release debug main clean pack
