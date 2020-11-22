#include "Maze.h"

int main()
{
	Maze maze(5, 5);
	for (int i = 0; i < maze.rows() - 1; i++)
	{
		maze.makeConnection(i, i, i, i + 1);
		maze.makeConnection(i, i + 1, i + 1, i + 1);
	}
	maze.printMaze();
	return 0;
}