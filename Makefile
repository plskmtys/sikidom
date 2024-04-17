# Variables
CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -g
SRC_DIR = src
BIN_DIR = bin
EXECUTABLE = sikidom

# Find all the .cpp files in the SRC_DIR directory
#SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(SRC_DIR)/sikidom.h $(SRC_DIR)/pont.h $(SRC_DIR)/matek.h
# Replace .cpp extension with .o for object files
OBJECTS = $(BIN_DIR)/main.o $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(HEADERS))

# Generate a list of .d files
#DEPS = $(OBJECTS:.o=.d)

# Default target
all: $(BIN_DIR)/$(EXECUTABLE)
# Find all the .cpp files in the SRC_DIR directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Replace .cpp extension with .o for object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))
# Generate a list of .d files
DEPS = $(OBJECTS:.o=.d)

# Default target
all: $(BIN_DIR)/$(EXECUTABLE)

# Linking the executable from the object files
$(BIN_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Compiling the source files into object files
#$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include the .d files
#-include $(DEPS)

# Phony target to clean the build files
.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*
# Linking the executable from the object files
$(BIN_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Compiling the source files into object files
#$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJECTS): $(HEADERS)
# Include the .d files
#-include $(DEPS)

# Phony target to clean the build files
.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*
