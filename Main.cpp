#include "Maze.h"
#include "MTreeNode.h"

void addChildren(MTreeNode* node, Maze& maze, int weights[5][5])
{
	int i = node->i();
	int j = node->j();
	MCell cell = maze.cell(i, j);
	if (cell.right())
	{
		node->addChild(i, j + 1);
		weights[i][j + 1] = node->distance() + 1;
		addChildren(node->hasChild(i + 1 - 1, j + 1), maze, weights);
	}
	if (cell.down())
	{
		node->addChild(i + 1, j);
		weights[i + 1][j] = node->distance() + 1;
		addChildren(node->hasChild(i + 1, j), maze, weights);
	}
}

int main()
{
	Maze maze(5, 5);
	int weights[5][5];
	weights[0][0] = 0;
	for (int i = 0; i < maze.rows() - 1; i++)
	{
		for (int j = 0; j < maze.rows() - 1 - i; j++)
		{
			maze.makeConnection(i, i + j, i, i + j + 1);
			maze.makeConnection(i + j, i, i + j + 1, i);
		}
		maze.makeConnection(i, i + 1, i + 1, i + 1);
	}
	MTreeNode* tree = MTreeNode::beginTree(0, 0);
	addChildren(tree, maze, weights);
	maze.printMaze();
	cout << endl;
	for (int i = 0; i < maze.rows(); i++)
	{
		for (int j = 0; j < maze.rows(); j++)
		{
			cout << weights[i][j];
		}
		cout << endl;
	}
	delete tree;
	return 0;
}