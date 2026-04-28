TARGET = bin/Roguepoly

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Ilib/include

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = lib/src
MAIN_DIR = main
OBJ_DIR = lib/obj
BIN_DIR = bin

SRCS = $(wildcard $(MAIN_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
