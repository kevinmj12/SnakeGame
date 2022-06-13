#include <iostream>
#include "Map.h"
#include <vector>
#include <time.h>
// #include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

extern int userInput;
extern int appleCount;
extern int poisonCount;

void Map::initMap() {
    for (int i=0; i<25; i++) {
        for (int j=0; j<50; j++) {
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
    for (int i=0; i<25; i++) {
        for (int j=0; j<50; j++) {
            if (board[i][j] == '1') {
                if (headRow == i && headCol == j) {
                    return true;
                }
            }
        }
    }
    return crash;
}
// static time_t input_time = time(NULL);

void Map::getInput(Snake &snake) {
    // **** 입력을 안 하면 그냥 넘어감 halfdelay() ****
    halfdelay(1);
    userInput = getch();

    // while (true) {
    // cout << time(NULL) - input_time << endl;
    // if (time(NULL) - input_time > 0.2) {
    //     cout << "qwe" << endl;
    //     return;
    // }
    // else {
    //     // halfdelay(2);
    //     // userInput = getch();
    // }
    // }
    // input_time = time(NULL);

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
    // 머리가 아이템이랑 부딪혔나?
    // int r = snake.location[0].row;
    // int c = snake.location[0].col;
    attron(COLOR_PAIR(4));
    board[r][c] = '3';
    board[r][c+1] = '3';
    mvprintw(r, c, "3");
    mvprintw(r, c+1, "3");
    attroff(COLOR_PAIR(4));

    if (r == appleLocation.first && c == appleLocation.second) {
        snake.eatApple(appleLocation.first, appleLocation.second);
        appleCount--;
    }
    if (r == poisonLocation.first && c == poisonLocation.second) {
        r = snake.location[snake.location.size()-1].row;
        c = snake.location[snake.location.size()-1].col;
        attron(COLOR_PAIR(1));
        board[r][c] = '0';
        board[r][c+1] = '0';
        mvprintw(r, c, "0"); 
        mvprintw(r, c+1, "0");
        attroff(COLOR_PAIR(1));
        snake.eatPoison(poisonLocation.first, poisonLocation.second);
        poisonCount--;
    }
    

    // 몸통 출력
    for (int i=1; i<snake.getLength(); i++) {
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

    if (snake.getLength() == 4) {
        cout << "GAME OVER" << endl;
        terminate();
    }

    // 0.5초 대기
    // usleep(500000);
}

void Map::printMap() {
    for (int i=0; i<25; i++) {
        for (int j=0; j<50; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}


time_t appleStart;
time_t poisonStart;
void Map::generateApple(Snake &snake) {
    srand(time(NULL));
    bool ableToGenerate = false;
    int r, c;

    time_t now = time(NULL);

    if (appleCount == 1 && (double)(now - appleStart) > 5) {
        attron(COLOR_PAIR(1));
        r = appleLocation.first;
        c = appleLocation.second;
        board[r][c] = '0';
        board[r][c+1] = '0';
        mvprintw(r, c, "0"); 
        mvprintw(r, c+1, "0");
        attroff(COLOR_PAIR(1));
        ableToGenerate = false;
        appleCount--;
    }

    if (appleCount < 1) {
        while (!ableToGenerate) {
            r = rand() % 23 + 1;
            c = rand() % 46 + 1;
            if (c % 2 != 0) {
                c++;
            }

            for (int i=0; i<snake.location.size(); i++) {
                if (r != snake.location[i].row && c != snake.location[i].col) {
                    ableToGenerate = true;
                }
                else {
                    ableToGenerate = false;
                    break;
                }
            }
            if (r == poisonLocation.first && c == poisonLocation.second) {
                ableToGenerate = false;
            }
        }
        attron(COLOR_PAIR(4));
        board[r][c] = '5';
        board[r][c+1] = '5';
        mvprintw(r, c, "5");
        mvprintw(r, c+1, "5");
        attroff(COLOR_PAIR(4));
        appleCount++;

        appleLocation.first = r;
        appleLocation.second = c;
        appleStart = time(NULL);
    }
}

void Map::generatePoison(Snake &snake) {
    // srand(time(NULL));
    bool ableToGenerate = false;
    int r, c;

    time_t now = time(NULL);

    if (poisonCount == 1 && (double)(now - poisonStart) > 5) {
        attron(COLOR_PAIR(1));
        r = poisonLocation.first;
        c = poisonLocation.second;
        board[r][c] = '0';
        board[r][c+1] = '0';
        mvprintw(r, c, "0"); 
        mvprintw(r, c+1, "0");
        attroff(COLOR_PAIR(1));
        ableToGenerate = false;
        poisonCount--;
    }

    if (poisonCount < 1) {
        while (!ableToGenerate) {
            r = rand() % 23 + 1;
            c = rand() % 46 + 1;
            if (c % 2 != 0) {
                c++;
            }

            for (int i=0; i<snake.location.size(); i++) {
                if (r != snake.location[i].row && c != snake.location[i].col) {
                    ableToGenerate = true;
                }
                else {
                    ableToGenerate = false;
                    break;
                }
            }
            if (r == appleLocation.first && c == appleLocation.second) {
                ableToGenerate = false;
            }
        }
        attron(COLOR_PAIR(3));
        board[r][c] = '3'; 
        board[r][c+1] = '3';
        mvprintw(r, c, "3");
        mvprintw(r, c+1, "3");
        attroff(COLOR_PAIR(3));
        poisonCount++;

        poisonLocation.first = r;
        poisonLocation.second = c;
        poisonStart = time(NULL);
    }
}