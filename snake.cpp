#include "snake.h"
#include "graphics.h"

#include <ctime>
#include <windows.h>

Position::Position(int _x = 0, int _y = 0):x(_x), y(_y){}

Snake::Snake():BLOCK_SIZE(10){
    this->frameInterval = 500;
    this->painter = NULL;
    this->block = NULL;
}
Snake::~Snake(){
    cleanUp();
}

void Snake::setInterval(int interval){ //ms
    if (interval <= 10){ //too short
        return;
    }
    this->frameInterval = interval;
}

void Snake::frameDelay(){
    //...
    static int lastTime = clock();
    int delta = clock() - lastTime;
    if (delta < frameInterval){
        delay_ms(frameInterval - delta);
    }
    lastTime = clock();
}

void Snake::cleanUp(){
    //release memory
    if (block != NULL){
        for (int i=0;i<BLOCK_SIZE;++i){
            delete block[i];
        }
        block = NULL;
    }
    if (painter != NULL){
        painter->cleanUp();
        delete painter;
        painter = NULL;
    }
}

void Snake::init(){
    setInterval(60);
    srand(time(0));
    cleanUp();

    //memory allocation
    block[0] = new BLOCK_TYPE[BLOCK_SIZE * BLOCK_SIZE];
    for (int i=1;i<BLOCK_SIZE;++i){
        block[i] = block[i * BLOCK_SIZE];
    }

    //generate snake
    int mid = BLOCK_SIZE / 2;
    block[mid][mid-1] = TAIL;
    block[mid][mid] = BODY;
    block[mid][mid+1] = HEAD;
    //set initial direction
    currentDirection = RIGHT;

    //generate foods
    int x, y;
    do{
        x = rand() % BLOCK_SIZE;
        y = rand() % BLOCK_SIZE;
    }while (block[x][y] != EMPTY_BLOCK);
    block[x][y] = FOOD;

    //generate walls(to be done)

    //initialise painter
    painter = new Painter;
    painter->bindSnake(this);
    painter->init();
}

void Snake::showGameOver(){
    ;//to be done
}

DIRECTION Snake::getInputDirection(){
    if (kbmsg()){
        key_msg k = getkey();
        if (k.key == VK_UP){
            return UP;
        }else if (k.key == VK_DOWN){
            return DOWN;
        }else if (k.key == VK_LEFT){
            return LEFT;
        }else if (k.key == VK_RIGHT){
            return RIGHT;
        }else{
            return NO_DIRECTION;
        }
    }else{
        return NO_DIRECTION;
    }
}

void Snake::update(){
    //get input, judge and delay every frame
    move(getInputDirection())
    painter->update();
    frameDelay();
}

void Snake::move(DIRECTION inputDir){
    //needs snake's head  pointer
    //...
}

bool Snake::judge(){
    //calculate and return if game is over
    //...
    return true;
}

void Snake::play(){
    init();
    while (judge() == true){
        update();
    }
    showGameOver();
}
