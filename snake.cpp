#include "snake.h"
#include "graphics.h"

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <windows.h>

Position::Position(int _x = 0, int _y = 0):x(_x), y(_y){}

SnakeBody::SnakeBody(int _x=0, int _y=0):x(_x), y(_y), last(nullptr), next(nullptr){}

Snake::Snake():BLOCK_SIZE(10){
    setInterval(60);
    srand(time(0));

    //memory allocation
    block[0] = new BLOCK_TYPE[BLOCK_SIZE * BLOCK_SIZE];
    for (int i=1;i<BLOCK_SIZE;++i){
        block[i] = block[i * BLOCK_SIZE];
    }
    memset(block, 0, sizeof(BLOCK_TYPE) * BLOCK_SIZE*BLOCK_SIZE);

    //put snake in the middle of map
    int mid = BLOCK_SIZE / 2;
    SnakeBody *now;
    block[mid][mid+1] = HEAD;
    this->snakeHead = new SnakeBody(mid, mid+1);

    block[mid][mid] = BODY;
    SnakeBody *body = new SnakeBody(mid, mid);
    this->snakeHead->next = body;
    body->last = this->snakeHead;

    block[mid][mid-1] = TAIL;
    SnakeBody *tail = new SnakeBody(mid, mid-1);
    body->next = tail;
    tail->last = body;

    //set initial direction
    toward = DIRECTION::RIGHT;

    //generate foods
    int x, y;
    do{
        x = rand() % BLOCK_SIZE;
        y = rand() % BLOCK_SIZE;
    }while (block[x][y] != EMPTY_BLOCK);
    block[x][y] = FOOD;

    //generate walls(to be done)

    //initialise painter
    this->painter = new Painter;
    painter->bindSnake(this);
}
Snake::~Snake(){
    //remember to release memory of SnakeBody pointer
    if (this->block != nullptr){
        for (int i=0;i<BLOCK_SIZE;++i){
            delete this->block[i];
        }
        this->block = nullptr;
    }
    if (this->painter != nullptr){
        delete this->painter;
        this->painter = nullptr;
    }
}

void Snake::setInterval(int interval){ //ms
    if (interval <= 10){ //too short
        return;
    }
    this->frameInterval = interval;
}

void Snake::delay(){
    static int lastTime = clock();
    int delta = clock() - lastTime;
    if (delta < frameInterval){
        delay_ms(frameInterval - delta);
    }
    lastTime = clock();
}

void Snake::init(){
}

void Snake::gameOver(){
    ;//to be done
}

DIRECTION Snake::getInputDirection(){
    if (kbmsg()){ //keyboard message appears
        key_msg k = getkey();
        if (k.key == VK_UP){
            return DIRECTION::DIRECTION::UP;
        }else if (k.key == VK_DOWN){
            return DIRECTION::DOWN;
        }else if (k.key == VK_LEFT){
            return DIRECTION::LEFT;
        }else if (k.key == VK_RIGHT){
            return DIRECTION::RIGHT;
        }else{ //not a direction key
            return NO_DIRECTION;
        }
    }else{
        return NO_DIRECTION;
    }
}

void Snake::update(){
    //get input, judge and delay every frame
    turnTo(getInputDirection());
    move();
    painter->update();
    this->delay();
}

void Snake::turnTo(DIRECTION dir){
    if (dir != NO_DIRECTION){
        this->toward = dir;
    }else{}
}

void Snake::move(){
    //move or eat-grow
    int posx = this->head->x, posy = this->head->y;

    //get next position
    if (this->toward == DIRECTION::LEFT){
        --posy;
    }else if (this->toward == DIRECTION::RIGHT){
        ++posy;
    }else if (this->toward == DIRECTION::DOWN){
        ++posx;
    }else if (this->toward == DIRECTION::UP{
        --posx;
    }
    if (posx >= BLOCK_SIZE || posx < 0){
        posx = (posx + BLOCK_SIZE) % BLOCK_SIZE;
    }else if (posy >= BLOCK_SIZE || posy < 0){
        posy = (posy + BLOCK_SIZE) % BLOCK_SIZE;
    }

    BLOCK_TYPE nextBlock = this->block[posx][posy];
    if (nextBlock == BLOCK_TYPE::FOOD){ //grow up
        ;
        this->makeNewFood();
    }else if (nextBlock == BLOCK_TYPE::BODY){ //game over
        this->snakeHead->x = posx;
        this->snakeHead->y = posy;
        return;
    }

    //move all segments of snake
    SnakeBody *now = this->head;
    while (now->next != nullptr){ //while now is not tail
        swap(now->x, posx);
        swap(now->y, posy);
        now = now->next;
    }
}

void Snake::makeNewFood(){
    ;
}

bool Snake::judge(){
    int x = this->snakeHead->x, y = this->snakeHead->y;
    return (this->block[x][y] == BLOCK_TYPE::BODY);
}

void Snake::play(){
    init();
    while (judge() == true){
        update();
    }
    gameOver();
}
