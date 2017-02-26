#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include "eightPuzzle.h"

using namespace std;

int main()
{
	eightPuzzle x;

	int puzzleChoice = 0;
    cout << "Welcome to Samuel Hwang's (861152953) 8-puzzle solver.\n";
    cout << "Type \"1\" to enter a default puzzle, or \"2\" to enter your own puzzle\n";
    cin >> puzzleChoice;
	x.makeRoot(puzzleChoice);

	int algorithmChoice = 0;
	cout << "Enter your choice of algorithm:\n";
	cout << "\t1) Uniform Cost Search\n";
	cout << "\t2) A* with Misplaced Tile Heuristic\n";
	cout << "\t3) A* with Manhattan Distance Heuristic\n";
	cin >> algorithmChoice;
	x.algorithmSelect(algorithmChoice);
    
    return 0;
}