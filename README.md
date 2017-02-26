### Eight-Puzzle Solver

####Written by Samuel Hwang

Attachments:
- main.cpp
- eightPuzzle.h
- eightPuzzle.cpp
- Makefile
- README.md

This program solves the eight-puzzle with three methods: 
 1. Uniform Cost Search
 2. A* with Misplaced Tile Heuristic
 3. A* with Manhattan Distance Heuristic

This code is in C++.
To run, compile with Makefile (`make`) and run with `./a.out`.

Follow the instructions that appear on the terminal. 
Input `1` to use default puzzle or `2` to enter your own puzzle.

When entering your own puzzle, there is no need to separate numbers with spaces or tabs as the vector uses *char* to store tile value, but makes it easier for visibility. 
Please use an asterisk `*` to represent the empty tile.

Then, input `1` for Uniform Cost Search, `2` for A* Search with Misplaced Tile Heuristic, or `3` for A* Search with Manhattan Distance Heuristic. 

If user input puzzle is valid, the search for the goal node with begin. After goal node is found, there will be an option to display the path from the initial state to the goal node. Input `Y` or `Yes` to see the path.