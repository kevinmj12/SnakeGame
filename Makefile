all:
	g++ -o main main.cpp Map.cpp Snake.cpp -lncurses
	./main