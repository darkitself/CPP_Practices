#include "Maze.h"
#include "MTreeNode.h"
#include <ctime>
#include <iomanip>
#include <queue>
#include <iostream>

using namespace std;

bool isConnected(const Maze& iMaze, const int i, const int j)
{
	return iMaze.hasConnection(i, j, i, j + 1)
		|| iMaze.hasConnection(i, j, i, j - 1)
		|| iMaze.hasConnection(i, j, i + 1, j)
		|| iMaze.hasConnection(i, j, i - 1, j);
}

void shuffle(pair<int, int>* steps, const int size)
{
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		int n = rand() % size;
		if (i != n)
			swap(steps[i], steps[n]);
	}
}

int digitsCount(int n)
{
	int count = 0;
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return count;
}

void buildFullMaze(Maze& iMaze, MTreeNode& tree)
{
	constexpr int directionsCount = 4;
	deque<MTreeNode*> nodes{ &tree };
	srand(time(0));
	pair<int, int> steps[directionsCount] = { pair<int,int> { 0, -1 },
												   pair<int,int> { 0, 1 },
												   pair<int,int> { -1, 0 },
												   pair<int,int> { 1, 0 } };
	while (!nodes.empty())
	{
		MTreeNode* node = nodes.front();
		nodes.pop_front();
		bool canConnect = true;
		bool wasConnected = false;
		while (!wasConnected && canConnect) // main maze generation (connect random neighboring points to each connected point)
		{
			canConnect = false;
			for (int i = 0; i < directionsCount; i++)
			{
				pair<int, int> nextNode(node->i() + steps[i].first, node->j() + steps[i].second);

				if (nextNode.first < 0 || nextNode.first > iMaze.rows() - 1
					|| nextNode.second < 0 || nextNode.second > iMaze.columns() - 1
					|| isConnected(iMaze, nextNode.first, nextNode.second))
					continue;

				canConnect = true;
				if (rand() % 5 == 0)
				{
					iMaze.makeConnection(node->i(), node->j(), nextNode.first, nextNode.second);
					node->addChild(nextNode.first, nextNode.second);
					nodes.push_back(node->hasChild(nextNode.first, nextNode.second));
					wasConnected = true;
				}
			}
		}
	}
	bool wasDisconnected = true;
	while (wasDisconnected) // adding points that were not added during the main generation
	{
		wasDisconnected = false;
		for (int i = 0; i < iMaze.rows(); i++)
			for (int j = 0; j < iMaze.columns(); j++)
			{
				if (isConnected(iMaze, i, j))
					continue;
				wasDisconnected = true;
				shuffle(steps, directionsCount);
				for (int k = 0; k < directionsCount; k++)
					if (isConnected(iMaze, i + steps[k].first, j + steps[k].second))
					{
						iMaze.makeConnection(i, j, i + steps[k].first, j + steps[k].second);
						tree.searchNode(i + steps[k].first, j + steps[k].second)->addChild(i, j);
						break;
					}
			}
	}
}

int main()
{
	Maze m(10, 10);
	MTreeNode* tree = MTreeNode::beginTree(m.startI(), m.startJ());

	buildFullMaze(m, *tree);

	int maxWeight = 0;
	double sumWeight = 0;
	for (int i = 0; i < m.rows(); i++)
		for (int j = 0; j < m.columns(); j++)
		{
			MTreeNode* node = tree->searchNode(i, j);
			if (node->distance() > maxWeight)
				maxWeight = node->distance();
			sumWeight += node->distance();
		}

	m.printMaze();

	for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.columns(); j++)
			cout << setw(digitsCount(maxWeight) + 1) << tree->searchNode(i, j)->distance();
		cout << endl;
	}

	cout << "Max weight: " << maxWeight << endl;
	cout << "Average weight: " << sumWeight/m.columns()/m.rows() << endl;

	delete tree;
	return 0;
}