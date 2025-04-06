# Configurações para Windows
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iincludes
EXTENSION := .exe
OBJ_EXT := .o

# Diretórios
SRC_DIR := src
INC_DIR := includes
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
LIB_DIR := lib

# Nome do executável
TARGET := $(BIN_DIR)/seu_programa$(EXTENSION)

# Fontes e objetos
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%$(OBJ_EXT),$(SRCS))
DEPS := $(wildcard $(INC_DIR)/*.h)

# Se tiver main.cpp na raiz
ifneq ("$(wildcard main.cpp)","")
	OBJS += $(OBJ_DIR)/main$(OBJ_EXT)
endif

# Regras principais
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regra para arquivos em src/
$(OBJ_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%.cpp $(DEPS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para main.cpp se existir
ifneq ("$(wildcard main.cpp)","")
$(OBJ_DIR)/main$(OBJ_EXT): main.cpp $(DEPS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

# Cria diretórios
$(BIN_DIR) $(OBJ_DIR) $(LIB_DIR):
	@if not exist "$@" mkdir "$@"

# Empacota os objetos para compartilhar (cria um zip)
package_objs:
	@if not exist "$(LIB_DIR)" mkdir "$(LIB_DIR)"
	powershell Compress-Archive -Path "$(OBJ_DIR)\*" -DestinationPath "$(LIB_DIR)\objs.zip" -Force

# Limpeza
clean:
	rmdir /s /q "$(BUILD_DIR)"
	if exist "$(LIB_DIR)\objs.zip" del "$(LIB_DIR)\objs.zip"

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run package_objs