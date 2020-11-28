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
	cout << endl;

	Maze maze2(5, 5);
	for (int i = 0; i < maze.rows() - 1; i++)
	{
		maze2.makeConnection(i, i + 1, i, i);
		maze2.makeConnection(i + 1, i + 1, i, i + 1);
	}
	maze2.printMaze();
	return 0;
}