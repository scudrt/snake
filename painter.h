#ifndef _PAINTER_H_
#define _PAINTER_H_

class Snake;
class Painter{
public:
    void init()const;
    void bindSnake(const Snake*);
    void cleanUp();
    void update();
private:
    const Snake* bindingSnake;
};

#endif
