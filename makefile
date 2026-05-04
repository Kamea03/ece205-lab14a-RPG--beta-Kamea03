# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Name of the executable
TARGET = FishGame

# Source files
SRCS = main.cpp GameCharacter.cpp PlayerCharacter.cpp Octopus.cpp OctopusAssassin.cpp SharkBruiser.cpp PufferfishDefender.cpp JellyfishSorcerer.cpp

# Object files (replaces the .cpp extension with .o)
OBJS = $(SRCS:.cpp=.o)

# Default target when you just run 'make'
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to easily compile and run the code
run: $(TARGET)
	./$(TARGET)

# Target to clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)
