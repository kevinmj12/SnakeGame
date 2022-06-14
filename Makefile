all:
	g++ -o main main.cpp Map.cpp Snake.cpp -lncurses -std=c++11
	./main
