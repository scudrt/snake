#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "painter.h"
class Painter;

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
    SnakeBody *last, *next;
};

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
    void setDelayInterval(int);

    bool judge();

    DIRECTION getInputDirection();

    const int BLOCK_SIZE;
    int frameInterval;
    int snakeLength;

    BLOCK_TYPE** block;

    DIRECTION toward;

    SnakeBody *snakeHead;
    Position food;

    Painter *painter;
};

#endif
