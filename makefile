# roymeoded2512@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

# Folders
SRC_DIRS = Graph Algorithms DataStructures
TEST_DIR = Tests
INCLUDES = -I. $(addprefix -I, $(SRC_DIRS))

# Source Files
SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJS := $(SRCS:.cpp=.o)

# Executables
MAIN_EXE = main
TEST_EXE = test_exe

# Targets
all: $(MAIN_EXE)

$(MAIN_EXE): $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

Main: $(MAIN_EXE)
	./$(MAIN_EXE)

$(TEST_EXE): $(filter-out main.cpp, $(SRCS)) $(TEST_DIR)/test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

test: $(TEST_EXE)
	./$(TEST_EXE)

valgrind: $(MAIN_EXE)
	valgrind --leak-check=full --show-leak-kinds=all ./$(MAIN_EXE)

clean:
	rm -f $(OBJS) $(MAIN_EXE) $(TEST_EXE)

.PHONY: all Main test valgrind clean