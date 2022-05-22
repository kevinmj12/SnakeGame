#include <iostream>
#include "Map.h"
#include <vector>
// #include <unistd.h>

using namespace std;

extern int userInput;

void Map::initMap() {
    for (int i=0; i<20; i++) {
        for (int j=0; j<40; j++) {
            if (board[i][j] == '0') {
                attron(COLOR_PAIR(1));
                printw("0");
                attroff(COLOR_PAIR(1));
            }
            else if (board[i][j] == '1') {
                attron(COLOR_PAIR(2));
                printw("1");
                attroff(COLOR_PAIR(2));
            }
            else {
                attron(COLOR_PAIR(3));
                printw("2");
                attroff(COLOR_PAIR(3));
            }
        }
        printw("\n");
    }
    refresh();
}

bool Map::isCrashWithWall(Position head) {
    bool crash = false;
    int headRow = head.row;
    int headCol = head.col;
    for (int i=0; i<20; i++) {
        for (int j=0; j<40; j++) {
            if (board[i][j] == '1') {
                if (headRow == i && headCol == j) {
                    return true;
                }
            }
        }
    }
    return crash;
}

void Map::getInput(Snake &snake) {
    // **** 입력을 안 하면 그냥 넘어감 halfdelay() ****
    halfdelay(2);
    userInput = getch();
    if (userInput == KEY_UP) {
        if (snake.getDirection() != 'd') {
            snake.setDirection('u');
        }
        else {
            cout << "GAME OVER" << endl;
            terminate();
        }
    }
    else if (userInput == KEY_DOWN) {
        if (snake.getDirection() != 'u') {
            snake.setDirection('d');
        }
        else {
            cout << "GAME OVER" << endl;
            terminate();
        }
    }
    else if (userInput == KEY_LEFT) {
        if (snake.getDirection() != 'r') {
            snake.setDirection('l');
        }
        else {
            cout << "GAME OVER" << endl;
            terminate();
        }
    }
    else if (userInput == KEY_RIGHT) {
        if (snake.getDirection() != 'l') {
            snake.setDirection('r');
        }
        else {
            cout << "GAME OVER" << endl;
            terminate();
        }
    }
}

void Map::updateSnake(Snake &snake) {
    if (snake.getDirection() == 'l') {
        snake.location.insert(snake.location.begin(), Position(snake.location[0].row, snake.location[0].col - 2));
    }
    else if (snake.getDirection() == 'r') {
        snake.location.insert(snake.location.begin(), Position(snake.location[0].row, snake.location[0].col + 2));
    }
    else if (snake.getDirection() == 'u') {
        snake.location.insert(snake.location.begin(), Position(snake.location[0].row - 1, snake.location[0].col));
    }
    else if (snake.getDirection() == 'd') {
        snake.location.insert(snake.location.begin(), Position(snake.location[0].row + 1, snake.location[0].col));
    }
    snake.location.pop_back();
    if (snake.isCrashMySelf() || isCrashWithWall(snake.location[0])) {
        cout << "game Over" << endl;
        terminate();
    }

    // paint head
    int r = snake.location[0].row;
    int c = snake.location[0].col;
    attron(COLOR_PAIR(4));
    board[r][c] = '3'; 
    board[r][c+1] = '3';
    mvprintw(r, c, "3");
    mvprintw(r, c+1, "3");
    attroff(COLOR_PAIR(4));

    for (int i=1; i<snake.getLength()+1; i++) {
        r = snake.location[i].row;
        c = snake.location[i].col;
        attron(COLOR_PAIR(5));
        board[r][c] = '4'; 
        board[r][c+1] = '4'; 
        mvprintw(r, c, "4"); 
        mvprintw(r, c+1, "4");
        attroff(COLOR_PAIR(5));
    }

    refresh();
    // 잔상 삭제
    attron(COLOR_PAIR(1));
    board[r][c] = '0';
    board[r][c+1] = '0'; 
    mvprintw(r, c, "0"); 
    mvprintw(r, c+1, "0");
    attroff(COLOR_PAIR(1));

    // 0.5초 대기
    // usleep(500000);
}

void Map::printMap() {
    for (int i=0; i<20; i++) {
        for (int j=0; j<40; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}