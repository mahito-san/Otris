#include "../include/score.h"
#include "../include/cur.h"
#include "../include/cur.h"

void Score::printMessege()
{
    Cur C;
    CubePoint p;

    p.setLocate(2,19);
    p.setColor(WHITE);
    p.printPoint();

    c.saveCur();
    c.moveCur(2,11);
    cout<<"Player: "<<player;
    c.resumeCur();

    p.setLocate(4,19);
    p.setColor(GREEN);
    p.printPoint();

    c.saveCur();
    c.moveCur();
    cout<<"score : "<<score;
    c.resumeCur();
}