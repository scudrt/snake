//c++ main.cpp snake.cpp painter.cpp -Wall -lgraphics64 -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -std=c++17
#include "painter.h"
#include <graphics.h>
#include <fstream>

Painter::Painter(const Snake* snake):   WIN_WIDTH(500),
                                        WIN_HEIGHT(500),
                                        BLOCK_WIDTH(WIN_WIDTH / snake->BLOCK_SIZE),
                                        BLOCK_HEIGHT(WIN_HEIGHT / snake->BLOCK_SIZE),
                                        BLOCK_SIZE(snake->BLOCK_SIZE){
    this->bindingSnake = snake;
    initgraph(WIN_WIDTH, WIN_HEIGHT);
    this->update();
}

Painter::~Painter(){
    closegraph();
}

void Painter::update(){
    BLOCK_TYPE temp;
    color_t tempcolor;
    for (int i=0;i<this->BLOCK_SIZE;++i){
        for (int j=0;j<this->BLOCK_SIZE;++j){
            temp = this->bindingSnake->block[i][j];
            if (temp == BLOCK_TYPE::EMPTY_BLOCK){
                tempcolor = BLACK;
            }else if (temp == BLOCK_TYPE::FOOD){
                tempcolor = RED;
            }else if (temp == BLOCK_TYPE::BODY){
                tempcolor = BLUE;
            }else if (temp == BLOCK_TYPE::TAIL){
                tempcolor = WHITE;
            }else if (temp == BLOCK_TYPE::HEAD){
                tempcolor = GREEN;
            }
            this->drawAt(j, i, tempcolor);
        }
    }
    /*
    setcolor(EGERGB(0x0, 0xFF, 0x0));
    setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
    setfont(12, 0, "宋体");
    if (this->bindingSnake->toward == DIRECTION::UP){
        outtextxy(10, 10, "up");
    }else if (this->bindingSnake->toward == DIRECTION::DOWN){
        outtextxy(10, 10, "down");
    }else if (this->bindingSnake->toward == DIRECTION::LEFT){
        outtextxy(10, 10, "left");
    }else if (this->bindingSnake->toward == DIRECTION::RIGHT){
        outtextxy(10, 10, "right");
    }*/
}

void Painter::drawAt(int x, int y, color_t color){
    setfillcolor(color);
    bar(
        x*BLOCK_HEIGHT, y*BLOCK_WIDTH,
        (x+1)*BLOCK_HEIGHT, (y+1)*BLOCK_WIDTH
    );
}

void Painter::gameOver(){
    setfillcolor(RED);
    bar(0, 0, WIN_WIDTH, WIN_HEIGHT);
}
