#include "snake.h"
#include "graphics.h"

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <fstream>

Position::Position(int _x = 0, int _y = 0):x(_x), y(_y){}

SnakeBody::SnakeBody(int _x, int _y):x(_x), y(_y), last(nullptr), next(nullptr){}

Snake::Snake():BLOCK_SIZE(40){
    setDelayInterval(100);
    srand(time(0));

    //new a 2D array
    this->block = new BLOCK_TYPE* [BLOCK_SIZE];
    this->block[0] = new BLOCK_TYPE[BLOCK_SIZE * BLOCK_SIZE];
    for (int i=1;i<BLOCK_SIZE;++i){
        this->block[i] = this->block[i-1] + BLOCK_SIZE;
    }
    memset(this->block[0], 0, sizeof(BLOCK_TYPE) * BLOCK_SIZE*BLOCK_SIZE);

    //generate snake in the map
    this->snakeLength = 3;
    int mid = BLOCK_SIZE / 2;
    this->block[mid][mid+1] = BLOCK_TYPE::HEAD;
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
    this->toward = DIRECTION::RIGHT;

    //generate foods
    this->makeNewFood();

    //generate walls(to be done)

    //initialize painter
    this->painter = new Painter(this);
}
Snake::~Snake(){
    delete[] this->block[0];
    delete[] this->block;
    delete this->painter;
    SnakeBody *temp;
    while (this->snakeHead != nullptr){
        temp = this->snakeHead->next;
        delete this->snakeHead;
        this->snakeHead = temp;
    }
}

void Snake::setDelayInterval(int interval){ //ms
    this->frameInterval = interval;
}

void Snake::delay(){
    delay_ms(this->frameInterval);
}

void Snake::gameOver(){
    this->painter->gameOver();
}

DIRECTION Snake::getInputDirection(){
    if (kbmsg()){ //keyboard message appears
        key_msg k = getkey();
        if (k.key == VK_UP){
            return DIRECTION::UP;
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
    this->turnTo(this->getInputDirection());
    this->move();
    this->painter->update();
    this->delay();
}

void Snake::turnTo(DIRECTION dir){
    if (dir == DIRECTION::NO_DIRECTION){
        return;
    }else if (dir == DIRECTION::UP && this->toward != DIRECTION::DOWN){
        this->toward = dir;
    }else if (dir == DIRECTION::DOWN && this->toward != DIRECTION::UP){
        this->toward = dir;
    }else if (dir == DIRECTION::LEFT && this->toward != DIRECTION::RIGHT){
        this->toward = dir;
    }else if (dir == DIRECTION::RIGHT && this->toward != DIRECTION::LEFT){
        this->toward = dir;
    }
}

void Snake::move(){
    //move or eat-grow
    int posx = this->snakeHead->x,
        posy = this->snakeHead->y;
    //get next position
    if (this->toward == DIRECTION::LEFT){
        --posy;
    }else if (this->toward == DIRECTION::RIGHT){
        ++posy;
    }else if (this->toward == DIRECTION::DOWN){
        ++posx;
    }else if (this->toward == DIRECTION::UP){
        --posx;
    }
    if (posx >= BLOCK_SIZE || posx < 0){
        posx = (posx + BLOCK_SIZE) % BLOCK_SIZE;
    }else if (posy >= BLOCK_SIZE || posy < 0){
        posy = (posy + BLOCK_SIZE) % BLOCK_SIZE;
    }

    BLOCK_TYPE nextBlock = this->block[posx][posy];
    if (nextBlock == BLOCK_TYPE::FOOD){ //grow up
        this->snakeHead->last = new SnakeBody(posx, posy);
        this->snakeHead->last->next = this->snakeHead;
        this->block[posx][posy] = BLOCK_TYPE::HEAD;
        this->block[this->snakeHead->x][this->snakeHead->y] = BLOCK_TYPE::BODY;
        this->snakeHead = this->snakeHead->last;
        this->makeNewFood();
        return;
    }else if (nextBlock == BLOCK_TYPE::BODY){ //game over
        this->snakeHead->x = posx;
        this->snakeHead->y = posy;
        return;
    }

    //nothing forward
    SnakeBody *now = this->snakeHead;
    while (now != nullptr){ //while now is not tail
        std::swap(block[now->x][now->y], block[posx][posy]);
        std::swap(now->x, posx);
        std::swap(now->y, posy);
        now = now->next;
    }
}

void Snake::makeNewFood(){
    int posx, posy;
    do{
        posx = rand() % BLOCK_SIZE;
        posy = rand() % BLOCK_SIZE;
    }while (block[posx][posy] != BLOCK_TYPE::EMPTY_BLOCK);
    this->block[posx][posy] = BLOCK_TYPE::FOOD;
    this->food = Position(posx, posy);
}

bool Snake::judge(){
    int x = this->snakeHead->x, y = this->snakeHead->y;
    return (this->block[x][y] != BLOCK_TYPE::BODY);
}

void Snake::play(){
    while (this->judge() == true){
        this->update();
    }
    this->gameOver();
}
