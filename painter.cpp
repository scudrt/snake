//c++ *.cpp -g -Wall -lgraphics -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid -mwindows
#include "painter.h"
#include "graphics.h"

Painter::Painter(){
    ;
}

Painter::~Painter(){
    ;
}

void Painter::bindSnake(const Snake* snake){
    this->bindingSnake = snake;
}

void Painter::update(){
    ;
}
