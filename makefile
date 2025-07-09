# roymeoded2512@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

all: main

main:
	$(CXX) $(CXXFLAGS) -I. -IGraph -IAlgorithms -IDataStructures \
		Graph/*.cpp Algorithms/*.cpp DataStructures/*.cpp main.cpp -o main

test:
	$(CXX) $(CXXFLAGS) -I. -IGraph -IAlgorithms -IDataStructures \
		Graph/*.cpp Algorithms/*.cpp DataStructures/*.cpp Tests/test.cpp -o test

valgrind: main test			
	valgrind --leak-check=full --show-leak-kinds=all ./main
	valgrind --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -f main test

.PHONY: all main test valgrind clean