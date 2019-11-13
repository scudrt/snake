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
    Position();
    int x, y;
};

class Snake{
public:
    Snake();
    ~Snake();

    void play();

    friend class Painter;
private:
    void init();
    void update();
    void cleanUp();

    void showGameOver();
    void move(DIRECTION);

    void frameDelay();
    void setInterval(int interval = 500);

    bool judge();
    bool wantContinue();

    DIRECTION getInputDirection();

    const int BLOCK_SIZE;
    int frameInterval;

    BLOCK_TYPE** block;
    DIRECTION currentDirection;
    Painter *painter;
};

#endif
