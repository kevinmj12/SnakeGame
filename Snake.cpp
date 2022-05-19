#include <iostream>
#include "Snake.h"
using namespace std;

Snake::Snake(char dir) {
    direction = dir;
    location.push_back(Position(3, 24));
    location.push_back(Position(3, 26));
    location.push_back(Position(3, 28));
}