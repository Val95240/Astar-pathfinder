#ifndef HEADER_ASTAR
#define HEADER_ASTAR

#include <utility>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "Square.hpp"

using vector_pair = std::pair<std::vector<Square*>, std::vector<Square*>>;

vector_pair astar(int width, int height, Square* grid[],
        int startx, int starty, int goalx, int goaly);

int heuristic(int goalX, int goalY, Square* node);

std::vector<Square*> reconstruct(Square* node, int startX, int startY);

std::vector<Square*> neighbours(int width, int height, Square* grid[], Square* node);

#endif //HEADER_ASTAR
