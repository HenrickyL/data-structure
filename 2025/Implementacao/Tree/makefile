# Detectar sistema operacional
ifeq ($(OS),Windows_NT)
    PLATFORM := windows
else
    PLATFORM := linux
endif

SRC_DIR := src
INC_DIR := includes
OBJ_DIR := build/obj
BIN_DIR := build/bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

ifeq ($(PLATFORM),windows)
    TARGET := $(BIN_DIR)/programa.exe
else
    TARGET := $(BIN_DIR)/programa
endif

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

ifeq ($(PLATFORM),windows)
    VCPKG_INCLUDE := -IC:/vcpkg/installed/x64-windows/include
    VCPKG_LIB := -LC:/vcpkg/installed/x64-windows/lib
    ICU_LIBS := -licuuc -licuin -licudt -lstdc++fs
    MKDIR_P = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    LDFLAGS := -mconsole
else
    VCPKG_INCLUDE :=
    VCPKG_LIB :=
    ICU_LIBS := -licuuc -licui18n -licudata
    MKDIR_P = mkdir -p $1
    LDFLAGS :=
endif

INCLUDES := -I$(INC_DIR) $(VCPKG_INCLUDE)
LIBS := $(VCPKG_LIB) $(ICU_LIBS)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(call MKDIR_P,$(BIN_DIR))
	$(CXX) -o $@ $^ $(LIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(call MKDIR_P,$(OBJ_DIR))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
