#include "graph.hpp"
#include "rand.hpp"
#include "score.hpp"

enum MARK
{
    GAME_STOP=-1;
    GAME_PAUSE=0;
    GAME_RUN=1;

};

class Game{
private:
    int m_penal[24][17];
    color m_color[24][17];
    Context* m_graph;

    Context* nextGraph;
    MARK mark;

    Score s;

    //This will explore whether the next position is legal
    bool recoverPanel();

    //Whether it touches the bottom
    bool isAttachBottom();

    //Whether it touches the left
    bool isAttachLeft();

    //Whether it touches the right
    bool isAttachRight();

    //Get the block shape randomly
    char getShape();

    //Assign a value to the panel array with a block array
    bool setPenal();

    //After the square is moved, the remaining panel information must be erased
    bool erasePenal();

public:

    int x;
    int y;
    //The position of the current square
    //this value can be set only after the
    // square has moved or rotated successfully

    Game();

    ~Game();

    //How to create blocks randomly
    void createCube();

    //The method of movement
    void move(int dir);

    //Rotation method
    void roll();

    //Block stop
    void stop();

    //Erase full rows
    void erase();

    //After erasing the above graphics, the whole piece falls
    void down(int level);

	void printNextCube(Context* m_graph);

	void gameInit();

MARK getMark();
void setMark( MARK );

void printHelep();//DEBUGGING Purpose

};














