# compiler
CC = g++

# directories
SOURCE_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# creates directories if doesn't exist
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(BUILD_DIR)/Transactions)
$(shell mkdir -p $(BUILD_DIR)/Users)
$(shell mkdir -p $(BIN_DIR))

# flags
CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -std=c++17 -I$(INCLUDE_DIR)

# source files
TRANSACTIONS_SOURCES = $(wildcard $(SOURCE_DIR)/Transactions/*.cpp)
USERS_SOURCES = $(wildcard $(SOURCE_DIR)/Users/*.cpp)
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp) $(TRANSACTIONS_SOURCES) $(USERS_SOURCES)

# object files
TRANSACTIONS_OBJECTS = $(patsubst $(SOURCE_DIR)/Transactions/%.cpp, $(BUILD_DIR)/Transactions/%.o, $(TRANSACTIONS_SOURCES))
USERS_OBJECTS = $(patsubst $(SOURCE_DIR)/Users/%.cpp, $(BUILD_DIR)/Users/%.o, $(USERS_SOURCES))
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# executable
EXECUTABLE = $(BIN_DIR)/auction-system

# make all
all: $(EXECUTABLE)

# make executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# make objects
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/Transactions/%.o: $(SOURCE_DIR)/Transactions/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/Users/%.o: $(SOURCE_DIR)/Users/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# make clean
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/Transactions/*.o $(BUILD_DIR)/Users/*.o $(EXECUTABLE)
