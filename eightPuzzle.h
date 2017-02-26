#ifndef _EIGHTPUZZLE_H_
#define _EIGHTPUZZLE_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <list>

using namespace std;

struct tile
{
	//maximum amount of 4 children per node and one parent
	tile* child1;
	tile* child2;
	tile* child3;
	tile* child4;
	tile* parent;
	vector< vector<char> > puzzle; //store vector of puzzles here
	int heuristic;
	int movementCost;
};

// operator overload class to reverse order of nodes in priority queue
class Tile_Compare {
public:
    bool operator()(tile* t1, tile* t2)
    {
       if ((t1->movementCost + t1->heuristic) > (t2->movementCost + t2->heuristic)) return true;
       return false;
    }
};

class eightPuzzle
{
    private:
    // root node for traversal
    tile* root;

    // node to store goal node
    tile* goalNode;

    // vector of puzzles to compare repeat states
    vector< vector< vector<char> > >list;

    // reverse priorty queue to call the lowest heuristic+movementCost node
    priority_queue<tile*, vector<tile*>, Tile_Compare > q; 

    // keeps track if goal state is found
    bool goalState;

    // keeps track of total nodes expanded to reach goal
    int totalNodesExpanded;

    // keeps track of the max number of total nodes in the priority queue
    int totalNodesInQueue;

    // keeps track of the algorithm the user selects to calculate heuristic
    int algorithmOption;

    //a linked list to store the path from root node to the goal node
    std::list<tile*> finalSolution;
    
    public:
    eightPuzzle();
    void makeRoot(int x);
    bool checkValid(tile* curr);
    void algorithmSelect(int x);
    void puzzleSearch(tile* curr);

	void topLeftSwap(tile* curr);
	void topMiddleSwap(tile* curr);
	void topRightSwap(tile* curr);
	void middleLeftSwap(tile* curr);
	void middleMiddleSwap(tile* curr);
    void middleRightSwap(tile* curr);
    void bottomLeftSwap(tile* curr);
    void bottomMiddleSwap(tile* curr);
    void bottomRightSwap(tile* curr);

    void assignChild1(tile* curr, vector< vector<char> > tempvector1);
    void assignChild2(tile* curr, vector< vector<char> > tempvector2);
    void assignChild3(tile* curr, vector< vector<char> > tempvector3);
    void assignChild4(tile* curr, vector< vector<char> > tempvector4);

    int heuristicCalc(vector< vector<char> > puzzle);
    void maxQueueCalc();
    bool comparePuzzle(vector< vector<char> > puzzle);
    bool checkComplete(vector< vector<char> > puzzle);
    void displayPuzzle(tile* curr);
    void reorderPath(tile* curr);
    void displayPath();
};

#endif