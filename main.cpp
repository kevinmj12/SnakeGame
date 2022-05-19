#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <iostream>
#include "Map.h"
#include <thread>
// #include "Snake.h"

using namespace std;
// 방향키 input은 전역변수로
int userInput;

int main() {
    Map *map = new Map();
    Snake *snake = new Snake('l'); // 처음엔 왼쪽방향으로 출발

    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK); // floor - black
    init_pair(2, COLOR_WHITE, COLOR_WHITE); // wall - white
    init_pair(3, COLOR_CYAN, COLOR_CYAN); // wall corner - cyan
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW); // snake head
    init_pair(5, COLOR_BLUE, COLOR_BLUE); // snake body
    
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    // thread
    // thread t1(&Map::getInput, map);
    // thread t2(&Map::updateSnake, map, *snake);

    // init map
    map->initMap();

    // map->getInput(*snake);
    map->updateSnake(*snake);
    
    // 무한으로 사용자 입력 받음
    map->getInput(*snake);


    getch();
    endwin();

    // 🔳🔲 🔴🔵🔳🔲🔶🔷🔘💛💚💙💜🖤💥💣
}