#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include "eightPuzzle.h"

using namespace std;

// constructor
eightPuzzle::eightPuzzle()
{
	root = NULL;
}

//creates default puzzle or user input puzzle
void eightPuzzle::makeRoot(int x)
{
	tile* t = new tile;
	t->child1 = NULL;
	t->child2 = NULL;
	t->child3 = NULL;
	t->child4 = NULL;
	t->parent = NULL;
	t->heuristic = 0; 
	t->movementCost = 0;
	goalState = false;
	totalNodesExpanded = 0;
	totalNodesInQueue = 0;

	if(x == 1)
	{
		// pre-set puzzle
		// 1 2 3
		// 4 * 6
		// 7 5 8
		cout << "Default puzzle will be:\n";
		vector<char> vec1;
		vec1.push_back('1');
		vec1.push_back('2');
		vec1.push_back('3');
		vector<char> vec2;
		vec2.push_back('4');
		vec2.push_back('*');
		vec2.push_back('6');
		vector<char> vec3;
		vec3.push_back('7');
		vec3.push_back('5');
		vec3.push_back('8');
		t->puzzle.push_back(vec1);
		t->puzzle.push_back(vec2);
		t->puzzle.push_back(vec3);

		root = t;
		q.push(root);
		list.push_back(root->puzzle);
		displayPuzzle(root);
	}
	else if(x == 2)
	{
		cout << "Enter your puzzle Use a * to represent the blank.\n";

		char val1, val2, val3;
		cout << "Enter the first row. Use space or tabs between numbers.\n";
	    cin >> val1 >> val2 >> val3;
	   	vector<char> vec1;
		vec1.push_back(val1);
		vec1.push_back(val2);
		vec1.push_back(val3);
		t->puzzle.push_back(vec1);

		cout << "Enter the second row. Use space or tabs between numbers.\n";
	    cin >> val1 >> val2 >> val3;
		vector<char> vec2;
		vec2.push_back(val1);
		vec2.push_back(val2);
		vec2.push_back(val3);
		t->puzzle.push_back(vec2);

		cout << "Enter the third row. Use space or tabs between numbers.\n";
	    cin >> val1 >> val2 >> val3;		
		vector<char> vec3;
		vec3.push_back(val1);
		vec3.push_back(val2);
		vec3.push_back(val3);
		t->puzzle.push_back(vec3);

		root = t;
		q.push(root);
		list.push_back(root->puzzle);
	}
	else
	{
		cout << "Invalid response!\n";
		return;
	}
}

// checks if puzzle contains numbers 1-8 and *
bool eightPuzzle::checkValid(tile* curr)
{
	bool isTrue  = false;
	for(int k = 1; k < 9; k++)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(curr->puzzle.at(i).at(j) == (char)k || curr->puzzle.at(i).at(j) == '*')
				{
					isTrue = true;
				}
				if((i == 2) && (j == 2) && isTrue == false)
				{
					return false;
				}
			}

		}
		isTrue = false;
	}
	return true;
}

// makes sure the user inputs 1, 2, or 3 to select algorithm
// also returns if root is NULL or the user input puzzle is not valid
void eightPuzzle::algorithmSelect(int x)
{
	if(root == NULL)
	{
		cout << "Failed to initialize puzzle!" << endl;
		return;
	}
	if(!checkValid(root))
	{
		cout << "Not a valid puzzle!" << endl;
		return;
	}
	algorithmOption = x;
	cout << "Expanding state:\n";

	if(x == 1)
	{
		puzzleSearch(root);
	}
	else if(x == 2)
	{
		puzzleSearch(root);
	}
	else if(x == 3)
	{
		puzzleSearch(root);
	}
	else
	{
		cout << "Invalid response!" << endl;
		return;
	}
}

// recursive function to call the first node in priority queue and find its children nodes
// if goal node is found, output conclusion remarks
// switch function is used to direct to the correct swap tile depending on the index * is in
void eightPuzzle::puzzleSearch(tile* curr)
{	
	int index = 10; //change if 4x4 puzzle
	int tempIndex = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(curr->puzzle.at(i).at(j) == '*')
			{
				index = tempIndex;
			}
			else
			{
				tempIndex++;
			}
		}
	}
	if(index == 10) //change if 4x4 puzzle
	{
		cout << "Invalid response!" << endl;
		return;
	}

	if(checkComplete(curr->puzzle))
	{
		goalState = true;
		goalNode = curr;
	}
	else
	{
		q.pop();
	}

	switch(index)
	{
		case 0 : 
		{
			topLeftSwap(curr);
			break;
		}

		case 1:
		{
			topMiddleSwap(curr);
			break;
		}

		case 2:
		{
			topRightSwap(curr);
			break;
		}

		case 3:
		{
			middleLeftSwap(curr);
			break;
		}

		case 4:
		{
			middleMiddleSwap(curr);
			break;
		}

		case 5:
		{
			middleRightSwap(curr);
			break;
		}

		case 6:
		{
			bottomLeftSwap(curr);
			break;
		}

		case 7:
		{
			bottomMiddleSwap(curr);
			break;
		}

		case 8:
		{
			bottomRightSwap(curr);
			break;
		}

		default:
		{
			cout << "Something went wrong" << endl;
			return;
		}
	}
	if(goalState)
	{
		while(q.top() != goalNode)
		{
			q.pop();
		}
		displayPuzzle(q.top());
		cout << "Goal!" << endl;

		cout << "To solve this problem the search algorithm expanded a total of ";
		cout << totalNodesExpanded << " nodes." << endl;

		cout << "The maximum nodes in the queue at any one time was ";
		cout << totalNodesInQueue << "." << endl;

		cout << "The depth of the goal node was ";
		cout << q.top()->movementCost << "." << endl;

		string response;
		cout << "Would you like to see the final solution? (Type Y or Yes)" << endl;
		cin >> response;
		if(response == "Y" || response == "Yes" || response == "y" || response == "yes")
		{
			reorderPath(q.top());
		}
		return;
	}
	else
	{
		if(q.top() != NULL)
		{
			displayPuzzle(q.top());
			puzzleSearch(q.top());
		}
	}

}

// swap functions depending on the index of the blank tile, *
// nine different possibilities

void eightPuzzle::topLeftSwap(tile* curr)
{
	// 2 possible children
	// * 1 2
	// 3 4 5
	// 6 7 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;

	swap(tempvector1.at(0).at(0), tempvector1.at(0).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(0).at(0), tempvector2.at(1).at(0));
	assignChild2(curr, tempvector2);
}
void eightPuzzle::topMiddleSwap(tile* curr)
{
	// 3 possible children
	// 0 * 2
	// 3 4 5
	// 6 7 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(0).at(1), tempvector1.at(0).at(0));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(0).at(1), tempvector2.at(0).at(2));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(0).at(1), tempvector3.at(1).at(1));
	assignChild3(curr, tempvector3);
}
void eightPuzzle::topRightSwap(tile* curr)
{
	// 2 possible children
	// 0 1 *
	// 3 4 5
	// 6 7 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;

	swap(tempvector1.at(0).at(2), tempvector1.at(0).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(0).at(2), tempvector2.at(1).at(2));
	assignChild2(curr, tempvector2);
}
void eightPuzzle::middleLeftSwap(tile* curr)
{
	// 3 possible children
	// 0 1 2
	// * 4 5
	// 6 7 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(1).at(0), tempvector1.at(0).at(0));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(1).at(0), tempvector2.at(1).at(1));
	assignChild2(curr, tempvector2);
	

	swap(tempvector3.at(1).at(0), tempvector3.at(2).at(0));
	assignChild3(curr, tempvector3);
}

void eightPuzzle::middleMiddleSwap(tile* curr)
{
	// 4 possible children
	// 0 1 2
	// 3 * 5
	// 6 7 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;
	vector< vector<char> > tempvector4 = curr->puzzle;

	swap(tempvector1.at(1).at(1), tempvector1.at(0).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(1).at(1), tempvector2.at(1).at(0));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(1).at(1), tempvector3.at(1).at(2));
	assignChild3(curr, tempvector3);

	swap(tempvector4.at(1).at(1), tempvector4.at(2).at(1));
	assignChild4(curr, tempvector4);
}

void eightPuzzle::middleRightSwap(tile* curr)
{
	// 3 possible children
	// 0 1 2
	// 3 4 *
	// 6 7 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(1).at(2), tempvector1.at(0).at(2));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(1).at(2), tempvector2.at(1).at(1));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(1).at(2), tempvector3.at(2).at(2));
	assignChild3(curr, tempvector3);
}

void eightPuzzle::bottomLeftSwap(tile* curr)
{
	// 2 possible children
	// 0 1 2
	// 3 4 5
	// * 7 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;

	swap(tempvector1.at(2).at(0), tempvector1.at(1).at(0));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(2).at(0), tempvector2.at(2).at(1));
	assignChild2(curr, tempvector2);
}
void eightPuzzle::bottomMiddleSwap(tile* curr)
{
	// 3 possible children
	// 0 1 2
	// 3 4 5
	// 6 * 8

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;
	vector< vector<char> > tempvector3 = curr->puzzle;

	swap(tempvector1.at(2).at(1), tempvector1.at(1).at(1));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(2).at(1), tempvector2.at(2).at(0));
	assignChild2(curr, tempvector2);

	swap(tempvector3.at(2).at(1), tempvector3.at(2).at(2));
	assignChild3(curr, tempvector3);

}
void eightPuzzle::bottomRightSwap(tile* curr)
{
	// 2 possible children
	// 0 1 2
	// 3 4 5
	// 6 7 *

	vector< vector<char> > tempvector1 = curr->puzzle;
	vector< vector<char> > tempvector2 = curr->puzzle;

	swap(tempvector1.at(2).at(2), tempvector1.at(1).at(2));
	assignChild1(curr, tempvector1);

	swap(tempvector2.at(2).at(2), tempvector2.at(2).at(1));
	assignChild2(curr, tempvector2);
	
}

// 4 assign functions depending on the number of children the node creates after expanding it
// there can only be a maximum of four nodes created

void eightPuzzle::assignChild1(tile* curr, vector< vector<char> > tempvector1)
{
	// cout << "Child1" << endl;
	tile* tempStruct1 = new tile;
	//tempStruct1->movementCost = curr->movementCost;
	//tempStruct1->heuristic = curr->heuristic;

	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector1))
	{
		goalState = true;

		list.push_back(tempvector1);

		tempStruct1->movementCost = curr->movementCost + 1;
		tempStruct1->puzzle = tempvector1;
		tempStruct1->heuristic = heuristicCalc(tempvector1);

		curr->child1 = tempStruct1;
		curr->child1->parent = curr;
		q.push(curr->child1);
		totalNodesExpanded++;
		maxQueueCalc();

		goalNode = curr->child1;

		return;
	}
	if(comparePuzzle(tempvector1))
	{
		curr->child1 = NULL;
	}
	else if(!comparePuzzle(tempvector1))
	{
		// if not seen before,
		// add to list vector, add one to movement cost, add struct to child
		list.push_back(tempvector1);

		tempStruct1->movementCost = curr->movementCost + 1;
		tempStruct1->puzzle = tempvector1;
		tempStruct1->heuristic = heuristicCalc(tempvector1);

		curr->child1 = tempStruct1;
		curr->child1->parent = curr;
		q.push(curr->child1);
		totalNodesExpanded++;
		maxQueueCalc();
		// displayPuzzle(curr->child1);
	}
	
}

void eightPuzzle::assignChild2(tile* curr, vector< vector<char> > tempvector2)
{
	// cout << "Child2" << endl;
	tile* tempStruct2 = new tile;
	//tempStruct2->movementCost = curr->movementCost;
	//tempStruct2->heuristic = curr->heuristic;

	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector2))
	{
		goalState = true;

		list.push_back(tempvector2);

		tempStruct2->movementCost = curr->movementCost + 1;
		tempStruct2->puzzle = tempvector2;
		tempStruct2->heuristic = heuristicCalc(tempvector2);

		curr->child2 = tempStruct2;
		curr->child2->parent = curr;
		q.push(curr->child2);
		totalNodesExpanded++;
		maxQueueCalc();

		goalNode = curr->child2;

		return;
	}
	if(comparePuzzle(tempvector2))
	{
		curr->child2 = NULL;
	}
	else if(!comparePuzzle(tempvector2))
	{
		// if not seen before,
		// add to list vector, add one to movement cost, add struct to child
		list.push_back(tempvector2);

		tempStruct2->movementCost = curr->movementCost + 1;
		tempStruct2->puzzle = tempvector2;
		tempStruct2->heuristic = heuristicCalc(tempvector2);

		curr->child2 = tempStruct2;
		curr->child2->parent = curr;
		q.push(curr->child2);
		totalNodesExpanded++;
		maxQueueCalc();
		// displayPuzzle(curr->child2);
	}
	
}

void eightPuzzle::assignChild3(tile* curr, vector< vector<char> > tempvector3)
{
	// cout << "Child3" << endl;
	tile* tempStruct3 = new tile;
	//tempStruct3->movementCost = curr->movementCost;
	//tempStruct3->heuristic = curr->heuristic;

	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector3))
	{
		goalState = true;

		list.push_back(tempvector3);

		tempStruct3->movementCost = curr->movementCost + 1;
		tempStruct3->puzzle = tempvector3;
		tempStruct3->heuristic = heuristicCalc(tempvector3);

		curr->child3 = tempStruct3;
		curr->child3->parent = curr;
		q.push(curr->child3);
		totalNodesExpanded++;
		maxQueueCalc();

		goalNode = curr->child3;

		return;
	}
	if(comparePuzzle(tempvector3))
	{
		curr->child3 = NULL;
	}
	else if(!comparePuzzle(tempvector3))
	{
		// if not seen before,
		// add to list vector, add one to movement cost, add struct to child
		list.push_back(tempvector3);

		tempStruct3->movementCost = curr->movementCost + 1;
		tempStruct3->puzzle = tempvector3;
		tempStruct3->heuristic = heuristicCalc(tempvector3);

		curr->child3 = tempStruct3;
		curr->child3->parent = curr;
		q.push(curr->child3);
		totalNodesExpanded++;
		maxQueueCalc();
		// displayPuzzle(curr->child3);
	}
	
}

void eightPuzzle::assignChild4(tile* curr, vector< vector<char> > tempvector4)
{
	// cout << "Child4" << endl;
	tile* tempStruct4 = new tile;
	//tempStruct4->movementCost = curr->movementCost;
	//tempStruct4->heuristic = curr->heuristic;

	if(goalState)
	{
		return;
	}
	if(checkComplete(tempvector4))
	{
		goalState = true;

		list.push_back(tempvector4);

		tempStruct4->movementCost = curr->movementCost + 1;
		tempStruct4->puzzle = tempvector4;
		tempStruct4->heuristic = heuristicCalc(tempvector4);

		curr->child4 = tempStruct4;
		curr->child4->parent = curr;
		q.push(curr->child4);
		totalNodesExpanded++;
		maxQueueCalc();

		goalNode = curr->child4;

		return;
	}
	if(comparePuzzle(tempvector4))
	{
		curr->child4 = NULL;
	}
	else if(!comparePuzzle(tempvector4))
	{
		// if not seen before,
		// add to list vector, add one to movement cost, add struct to child
		list.push_back(tempvector4);

		tempStruct4->movementCost = curr->movementCost + 1;
		tempStruct4->puzzle = tempvector4;
		tempStruct4->heuristic = heuristicCalc(tempvector4);

		curr->child4 = tempStruct4;
		curr->child4->parent = curr;
		q.push(curr->child4);
		totalNodesExpanded++;
		maxQueueCalc();
		// displayPuzzle(curr->child4);
	}
}

// reads in struct and assigns heuristic based on # of misplaced tiles
int eightPuzzle::heuristicCalc(vector< vector<char> > puzzle)
{
	int tempHeuristic = 0;
	vector< vector<char> > solvedPuzzle;
	static const char arr1[] = {'1', '2', '3'};
	static const char arr2[] = {'4', '5', '6'};
	static const char arr3[] = {'7', '8', '*'};
	vector<char> vec1 (arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );
	vector<char> vec2 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
	vector<char> vec3 (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );
	solvedPuzzle.push_back(vec1);
	solvedPuzzle.push_back(vec2);
	solvedPuzzle.push_back(vec3);
	// solvedPuzzle filled with complete 2D vector

	if(algorithmOption == 1) // uniform cost heuristic
	{
		return tempHeuristic;
	}
	else if(algorithmOption == 2) // misplaced tile heuristic
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(puzzle.at(i).at(j) != solvedPuzzle.at(i).at(j))
				{
					tempHeuristic++;
				}
			}
		}
		return tempHeuristic;
	}
	else if(algorithmOption == 3) // Manhattan heuristic
	{	
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				for(int k = 0; k < 3; k++)
				{
					for(int l = 0; l < 3; l++)
					{
						if(solvedPuzzle.at(i).at(j) == puzzle.at(k).at(l))
						{
							tempHeuristic += abs(i - k);
							tempHeuristic += abs(j - l);
						}
					}
				}
			}
		}

		return tempHeuristic;
	}
	return 0;
}

// calculates if the number of nodes in the queue has increased
void eightPuzzle::maxQueueCalc()
{
	if(q.size() > totalNodesInQueue)
	{
		totalNodesInQueue = q.size();
	}
}

// compares the puzzle to see if it has been represented already
bool eightPuzzle::comparePuzzle(vector< vector<char> > puzzle)
{
	for(int i = 0; i < list.size(); i++)
	{
		if(puzzle == list.at(i))
		{
			return true;
		}

	}
	return false;
}

// checks if the puzzle is the goal state
bool eightPuzzle::checkComplete(vector< vector<char> > puzzle)
{
	vector< vector<char> > solvedPuzzle;
	static const char arr1[] = {'1', '2', '3'};
	static const char arr2[] = {'4', '5', '6'};
	static const char arr3[] = {'7', '8', '*'};
	vector<char> vec1 (arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );
	vector<char> vec2 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
	vector<char> vec3 (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );
	solvedPuzzle.push_back(vec1);
	solvedPuzzle.push_back(vec2);
	solvedPuzzle.push_back(vec3);
	// tempPuzzle filled with complete 2D vector

	if(puzzle == solvedPuzzle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// displays the puzzle along with the heuristic and movement cost
void eightPuzzle::displayPuzzle(tile* curr)
{
	if(curr != root)
	{
		cout << "The best state to expand with a g(n) = ";
		cout << curr->movementCost;
		cout << " and h(n) = ";
		cout << curr->heuristic;
		cout << " is..." << endl;
	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << curr->puzzle.at(i).at(j) << " ";
		}
		cout << endl;
		
	}
	cout << endl;
}

// goal node to root node are represented backward so this reorders in a linked list for outputting
void eightPuzzle::reorderPath(tile* curr)
{
	if(curr == root)
	{
		finalSolution.push_front(curr);
		displayPath();
	}
	else
	{
		finalSolution.push_front(curr);
		reorderPath(curr->parent);
	}
}

// outputs the root node to the goal node as well as outputting the amount of moves it takes to get to the state
void eightPuzzle::displayPath()
{
	int finalSolutionSize = finalSolution.size();
	for(int i = 0; i < finalSolutionSize; i++)
	{
		if(finalSolution.front() == root)
			cout << "Start State:" << endl;
		else
			cout << "Step " << i << ":" << endl;

		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				cout << finalSolution.front()->puzzle.at(i).at(j) << " ";
			}
			cout << endl;
		}
		cout << endl;
		finalSolution.pop_front();
	}
	cout << "Finished!\n";
	return;
}