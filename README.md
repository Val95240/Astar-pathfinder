
# Astar Pathfinder

This repository contains a basic C++ implementation of the [A* algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) that finds an optimal path in a graph using a distance heuristic.


## Installation

The code needs the following libraries to compile:
- [Qt5](https://www.qt.io/)

To compile, simply clone the directoy and run the `build` script.


## Usage

This program gives the shortest path between a starting point (in red) and a target point (in green) in a grid using the A* algorithm.
The grid can be interacted with using the `Ctrl` and `Shift` keys: when hovering above a cell while pressing `Ctrl`, the cell will become black which indicates that the algorithm can't go through this cell for the final path.
Hovering while pressing `Shift` will remove these black cells.

Once the grid is done, just press `Solve` to see the shortest path appear, as well as each considered cell during the algorithm search.
The `Reset` button will remove every black cell, and the `New` button will randomize the position of the starting and target cells.

If no path exists between the two points, the message "No path !" will be printed in the terminal.


