#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "painter.h"

enum DIRECTION{
    NO_DIRECTION, UP, DOWN, LEFT, RIGHT
};

enum BLOCK_TYPE{
    EMPTY_BLOCK, WALL, FOOD, BODY, HEAD, TAIL
};

struct Position{
    Position(int, int);
    int x, y;
};

struct SnakeBody{
    SnakeBody(int, int);

    int x, y;
    SnakeBody* last, next;
}

class Snake{
public:
    Snake();
    ~Snake();

    void play();

    friend class Painter;
private:
    void gameOver();
    void turnTo(DIRECTION);
    void move();
    void makeNewFood();
    void update();

    void delay();
    void setInterval(int interval = 500);

    bool judge();

    DIRECTION getInputDirection();

    const int BLOCK_SIZE;
    int frameInterval;

    BLOCK_TYPE** block;

    DIRECTION toward;

    SnakeBody *snakeHead;

    Painter *painter;
};

#endif
