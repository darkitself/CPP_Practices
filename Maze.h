#pragma once
#include "MCell.h"
#include <map>

class Maze
{
private:
	static std::map<int, char> symbols;
	MCell* m_field;
	const int m_rows;
	const int m_columns;
	int startPoint[2];
public:
	Maze(const int n, const int m);
	int rows() const;
	int columns() const;
	int startI() const;
	int startJ() const;
	const MCell& cell(const int i, const int j) const;
	bool hasConnection(const int i1, const int j1, const int i2, const int j2) const;
	bool makeConnection(const int i1, const int j1, const int i2, const int j2);
	bool removeConnection(const int i1, const int j1, const int i2, const int j2);
	void printMaze() const;
	~Maze();
};