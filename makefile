# Compiler settings
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# Target executable
TARGET = MovieApp

# Source files
SOURCES = main.cpp movieMap.cpp movieMapReducer.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Rule for making the target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for making object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Rule for cleaning the workspace
clean:
	rm -f $(TARGET) $(OBJECTS)

# Rule for running the program (optional)
run: $(TARGET)
	./$(TARGET)
