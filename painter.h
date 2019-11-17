#ifndef _PAINTER_H_
#define _PAINTER_H_

class Snake;
class Painter{
public:
    Painter();
    ~Painter();
    void bindSnake(const Snake*);
    void update();
private:
    const Snake* bindingSnake;
};

#endif
