#include "graph.hpp"
#include "rand.hpp"
#include "score.hpp"

enum MARK{
	GAME_STOP = -1,
	GAME_PAUSE = 0,
	GAME_RUN = 1
};


class Game
{
// variable declaration starts
private:
    int m_penal[24][17];
	color m_color[24][17];///////////////////////
    Context* m_graph;

	Context* nextGraph;/////////////////
	MARK mark;//////////////////////////
public:
    int x;
    int y;

private:
    Score s;

//variable declaration ends


//function declaration starts
private:
    //functions that interacts with the context class from graph.hpp and manipulates the shapes
    //
    //recovers 
    bool recoverPenal();
    //checks
    bool isAttachBottom();
    //checks
    bool isAttachLeft();
    //checks
    bool isAttachRight();
    //gets the shape ,as a char
    char getShape();
    //sets
    bool setPenal();
    //erases
    bool erasePenal();
public:
    //constructor
    Game();
    //destrcutor
	~Game();

    //creates cha cubes
    void createCube();
    //moves
    void move(int dir);
    //rolls
    void roll();
    //stops the shapes
    void stop();
    //earases
    void erase();
    //gets down with each level
    void down(int level);
    //prints next cube
	void printNextCube(Context* m_graph);
	void gameInit();

    MARK getMark();

    void setMark( MARK );

    void printHelep();

//function declaration ends

};
