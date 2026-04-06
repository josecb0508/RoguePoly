# Nombre del binario final
TARGET = bin/Roguepoly

# Compilador y Estándar
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Ilib/include

# Librerías SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Directorios de la nueva estructura
SRC_DIR = lib/src
MAIN_DIR = main
OBJ_DIR = lib/obj
BIN_DIR = bin

# Localizar todos los archivos .cpp (en main y en lib/src)
SRCS = $(wildcard $(MAIN_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

# Generar la lista de archivos .o dentro de la carpeta lib/obj
# Usamos 'notdir' para quitar la ruta original y luego le anteponemos OBJ_DIR
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# Regla principal
all: $(TARGET)

# Vinculación del ejecutable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regla para compilar los .cpp de la carpeta 'main' a 'lib/obj'
$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar los .cpp de 'lib/src' a 'lib/obj'
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos temporales y binarios
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Compilar y ejecutar
run: all
	./$(TARGET)

.PHONY: all clean run