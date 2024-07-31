CC = g++
C_FLAGS = -MMD -MP -Iinclude
L_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

BIN = raycaster
BUILD_DIR = ./build
SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: run

run: $(BUILD_DIR)/$(BIN)
	@echo "Running the game..."
	@$(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $^ -o $@ $(L_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
