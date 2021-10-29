#include "Astar.hpp"


vector_pair astar(int width, int height, Square* grid[],
        int startX, int startY, int goalX, int goalY)
{
    std::vector<Square*> openList;
    std::vector<Square*> seen;

    Square* start = grid[startX*width+startY];
    Square* goal = grid[goalX*width+goalY];
    Square* current;

    start->setCost(0);
    openList.push_back(start);

    while (!openList.empty())
    {
        // Choose the node with the minimum f-value
        int idx = 0, min_val = 1000000;
        for (int i=0; i<openList.size(); ++i) {
            int f_value = openList[i]->getCost() + heuristic(goalX, goalY, openList[i]);
            if (f_value < min_val) {
                min_val = f_value;
                idx = i;
            }
        }
        // Remove it from the list and add it to seen
        current = openList[idx];
        openList.erase(openList.begin() + idx);
        seen.push_back(current);

        if (current->getX() == goalX && current->getY() == goalY)
            return vector_pair(seen, reconstruct(current, startX, startY));

        // Look at its neighbour
        for (Square* neighbour : neighbours(width, height, grid, current))
        {
            if (std::find(seen.begin(), seen.end(), neighbour) != seen.end())
                continue;

            if (std::find(openList.begin(), openList.end(), neighbour) == openList.end()) {
                openList.push_back(neighbour);
            } else if (current->getCost() + 1 >= neighbour->getCost()) {
                continue;
            }
            neighbour->setCost(current->getCost() + 1);
            neighbour->setParent(current);
        }
    }
    return vector_pair(seen, std::vector<Square*>());
}


int heuristic(int goalX, int goalY, Square* node)
{
    return abs(goalX - node->getX()) + abs(goalY - node->getY());
}


std::vector<Square*> reconstruct(Square* node, int startX, int startY)
{
    std::vector<Square*> path;
    path.push_back(node);

    while (node->getX() != startX || node->getY() != startY) {
        node = node->getParent();
        path.push_back(node);
    }
    return path;
}


std::vector<Square*> neighbours(int width, int height, Square* grid[], Square* node)
{
    std::vector<Square*> nbs;
    int x = node->getX(), y = node->getY();
    int up    = (x - 1) * width + y;
    int down  = (x + 1) * width + y;
    int left  = x * width + y - 1;
    int right = x * width + y + 1;
    if (x > 0 && grid[up]->getState() != WALL) {
        nbs.push_back(grid[up]);
    }
    if (x < height-1 && grid[down]->getState() != WALL) {
        nbs.push_back(grid[down]);
    }
    if (y > 0 && grid[left]->getState() != WALL) {
        nbs.push_back(grid[left]);
    }
    if (y < width-1 && grid[right]->getState() != WALL) {
        nbs.push_back(grid[right]);
    }
    return nbs;
}
