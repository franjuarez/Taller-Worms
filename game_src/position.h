#ifndef POSITION_H
#define POSITION_H

class Position {

private:
    int x;
    int y; 
public:
    Position(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    ~Position();
};
#endif
