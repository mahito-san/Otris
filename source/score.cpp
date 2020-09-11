#include "../include/score.hpp"
#include "../include/cur.hpp"
#include "../include/cubePoint.hpp"

void Score::printMessege()
{
    Cur c;
    CubePoint p;
    //cursor and cubepoint
    p.setLocate(2,19); 
    p.setColor(WHITE);
    p.printPoint();

    c.saveCur();
    c.moveCur(2,11);
   // cout<<"              "<<player;
    c.resumeCur();

    p.setLocate(4,19);
    p.setColor(GREEN);
    p.printPoint();

    c.saveCur();
    c.moveCur(4,21);
    cout<<"score : "<<score;
    c.resumeCur();
}