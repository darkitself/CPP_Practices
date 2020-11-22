#pragma once
#include "MCell.h"
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
class Maze
{
private:
	static map<int, char> symbols;
	MCell* m_field;
	int m_rows;
	int m_columns;
public:
	Maze(int n, int m);
	int rows() const;
	int columns() const;
	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int j1, int i2, int j2) const;
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze() const;
	~Maze();
};