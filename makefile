# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -L/usr/local/lib -lpqxx -lpq

# Source files
SOURCES = NBA.cpp players.cpp simulator.cpp teams.cpp
# Output binary
OUTPUT = NBA

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CXX) $(SOURCES) $(CXXFLAGS) -o $(OUTPUT)


run: $(OUTPUT)
	./$(OUTPUT)
	
clean:
	rm -f $(OUTPUT)
