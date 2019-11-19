#ifndef _PAINTER_H_
#define _PAINTER_H_

#include "snake.h"

#include <graphics.h>

class Snake;
class Painter{
public:
    Painter(const Snake*);
    ~Painter();
    void update();
    void gameOver();
private:
    void drawAt(int, int, color_t);

    const int WIN_WIDTH, WIN_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT;
    const int BLOCK_SIZE;

    const Snake* bindingSnake;
};

#endif
