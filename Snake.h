#include <iostream>
#include "Position.h"
#include <vector>
using namespace std;

class Snake {
private:
    int locationRow;
    int locationCol;
    int length = 3;
    char direction;
    // vector<Position> location;
public:
    Snake(char dir);
    vector<Position> location;

    void setDirection(char dir) {
        direction = dir;
    }
    char getDirection() {
        return direction;
    }
    int getLength() {
        return length;
    }
    void move_up() {
        locationRow--;
    }
    void move_down() {
        locationRow++;
    }
    void move_right() {
        locationCol++;
    }
    void move_left() {
        locationCol--;
    }
    void eatApple() {
        length++;
    }
    void eatPoision() {
        length--;
    }
};