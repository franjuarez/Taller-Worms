#ifndef POSITION_H
#define POSITION_H

class Position {

private:
    float x;
    float y; 
public:
    Position(float x, float y);
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);
    ~Position();
};
#endif
