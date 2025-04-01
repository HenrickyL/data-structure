# Nome do executável
TARGET = build/meu_programa

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -I$(INC_DIR) -std=c++17
LDFLAGS = 

# Encontra todos os .cpp em src e adiciona main.cpp
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJ_FILES := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Regra padrão: compilar tudo
$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regra para compilar .cpp para .o
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria a pasta build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra para rodar o programa após a compilação
run: $(TARGET)
	./$(TARGET)

# Limpeza
clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)
