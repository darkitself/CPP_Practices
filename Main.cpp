#include "Maze.h"
#include "MTreeNode.h"
#include <ctime>
#include <iomanip>
bool isConnected(Maze& iMaze, int i, int j)
{
	return iMaze.hasConnection(i, j, i, j + 1)
		|| iMaze.hasConnection(i, j, i, j - 1)
		|| iMaze.hasConnection(i, j, i + 1, j)
		|| iMaze.hasConnection(i, j, i - 1, j);
}

void shuffle(vector<vector<int>>& array)
{
	srand(time(0));
	for (int i = 0; i < 4; i++)
	{
		int n = rand() % 4;
		vector<int> t = array[i];
		array[i] = array[n];
		array[n] = t;
	}
}

void buildFullMaze(Maze& iMaze, MTreeNode& tree)
{
	queue<MTreeNode*> nodes;
	nodes.push(&tree);
	srand(time(0));
	while (!nodes.empty())
	{
		MTreeNode* node = nodes.front();
		nodes.pop();
		int counter = 0;
		bool canConnect = true;
		while (counter == 0 && canConnect)
		{
			canConnect = false;
			for (int di = -1; di < 2; di++)
				for (int dj = -1; dj < 2; dj++)
					if (di * dj == 0 && di != dj)
						if (!(node->i() + di < 0 || node->i() + di > iMaze.rows() - 1
							|| node->j() + dj < 0 || node->j() + dj > iMaze.columns() - 1))
							if (!isConnected(iMaze, node->i() + di, node->j() + dj))
							{
								canConnect = true;
								if (rand() % 5 < 2)
								{
									iMaze.makeConnection(node->i(), node->j(), node->i() + di, node->j() + dj);
									node->addChild(node->i() + di, node->j() + dj);
									nodes.push(node->searchNode(node->i() + di, node->j() + dj));
									counter++;
								}
							}
		}
	}
	bool wasDisconnected = true;
	vector<vector<int>> steps = { vector<int>{0, -1}, vector<int>{0, 1}, vector<int>{-1, 0}, vector<int>{1, 0 } };
	while (wasDisconnected)
	{
		wasDisconnected = false;
		for (int i = 0; i < iMaze.rows(); i++)
			for (int j = 0; j < iMaze.columns(); j++)
			{
				shuffle(steps);
				if (!isConnected(iMaze, i, j))
				{
					wasDisconnected = true;
					for (int k = 0; k < 4; k++)
						if (isConnected(iMaze, i + steps[k][0], j + steps[k][1]))
						{
							iMaze.makeConnection(i, j, i + steps[k][0], j + steps[k][1]);
							tree.searchNode(i + steps[k][0], j + steps[k][1])->addChild(i, j);
							break;
						}
				}
			}
	}
}

int main()
{
	Maze m(10, 10);
	MTreeNode* tree = MTreeNode::beginTree(m.startPoint[0], m.startPoint[1]);
	int maxWeight = 0;
	double sumWeight = 0;
	buildFullMaze(m, *tree);
	for (int i = 0; i < m.rows(); i++)
		for (int j = 0; j < m.columns(); j++)
		{
			MTreeNode* node = tree->searchNode(i, j);
			if (node->distance() > maxWeight)
				maxWeight = node->distance();
			sumWeight += node->distance();
		}
	int t = maxWeight;
	int n = 0;
	while (t > 0)
	{
		n++;
		t = t / 10;
	}
	m.printMaze();
	for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.columns(); j++)
			cout << setw(n + 1) << tree->searchNode(i, j)->distance();
		cout << endl;
	}
	cout << "Max weight: " << maxWeight << endl;
	cout << "Average weight: " << sumWeight/m.columns()/m.rows() << endl;
	return 0;
}