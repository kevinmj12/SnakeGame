#include <iostream>
#include "Map.h"
#include <vector>
#include <unistd.h>

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

void Map::getInput(Snake &snake) {
    while (true) {
        if (userInput == KEY_UP) {
            if (snake.getDirection() != 'd') {
                snake.setDirection('u');
            }
            else {
                cout << "GAME OVER" << endl;
            }
        }
        else if (userInput == KEY_DOWN) {
            if (snake.getDirection() != 'u') {
                snake.setDirection('d');

            }
            else {
                cout << "GAME OVER" << endl;
            }
        }
        else if (userInput == KEY_LEFT) {
            if (snake.getDirection() != 'r') {
                snake.setDirection('l');

            }
            else {
                cout << "GAME OVER" << endl;
            }
        }
        else if (userInput == KEY_RIGHT) {
            if (snake.getDirection() != 'l') {
                snake.setDirection('r');
            }
            else {
                cout << "GAME OVER" << endl;
            }
        }
    }
}

void Map::updateSnake(Snake &snake) {
    while (true) {
        // ************** 0.5초씩 쉬면서 업데이트 ***************

        // paint head
        int r = snake.location[0].row;
        int c = snake.location[0].col;
        attron(COLOR_PAIR(4));
        board[r][c] = '3'; 
        board[r][c+1] = '3';
        mvprintw(r, c, "3");
        mvprintw(r, c+1, "3");
        attroff(COLOR_PAIR(4));

        if (snake.getDirection() == 'l') {
            // paint body
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
            // 머리 추가
            snake.location.insert(snake.location.begin(), Position(snake.location[0].row, snake.location[0].col -2 ));
            // 꼬리 삭제하기 전 잔상 삭제 위한 좌표 받기
            // int tail_row = snake.location.back().row;
            // int tail_col = snake.location.back().col;
            snake.location.pop_back();
            // 몸통 앞으로 한칸씩 밀어주기. 굳이 해야되나??
            // for (int i=1; i<snake.getLength(); i++) {
            //     snake.location[i].row = snake.location[i+1].row;
            //     snake.location[i].col = snake.location[i+1].col;
            // }
            for (int i=0; i<snake.getLength(); i++) {
                // cout << snake.location[i].col << " " << endl;
            }
        }
        else if (snake.getDirection() == 'r') {

        }
        else if (snake.getDirection() == 'u') {

        }
        else if (snake.getDirection() == 'd') {

        }
        refresh();
        // 잔상 삭제
        attron(COLOR_PAIR(1));
        board[r][c] = '0'; 
        board[r][c+1] = '0'; 
        mvprintw(r, c, "0"); 
        mvprintw(r, c+1, "0");
        attroff(COLOR_PAIR(1));

        // 1초 대기
        // sleep(1);

        // 0.5초 대기
        usleep(500000);
    }
}

void Map::printMap() {
    for (int i=0; i<20; i++) {
        for (int j=0; j<40; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}