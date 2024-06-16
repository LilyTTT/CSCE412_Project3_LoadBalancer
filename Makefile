# Compiler options
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Target executable
TARGET = output

# Source files
SRCS = *cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Default rule
all: $(TARGET)

# Rule to link the target executable
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean rule
clean:
    rm -f $(OBJS) $(DEPS) $(TARGET)

.PHONY: all clean
