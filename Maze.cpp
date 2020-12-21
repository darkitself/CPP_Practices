#include "Maze.h"
#include <ctime>
#include <algorithm>
#include <iostream>

std::map<int, char> Maze::symbols = { {0, 176}, {1, '0'}, {4, '0'}, {5, 179},
								 {2, '0'}, {8, '0'}, {10, 196}, {3, 192},
								 {6, 218}, {12, 191}, {9, 217}, {7, 195},
								 {14, 194}, {13, 180}, {11, 193}, {15, 197} };

Maze::Maze(int n, int m) : m_rows(n), m_columns(m), m_field(new MCell[n * m])
{
	srand(time(0));
	switch (rand() % 4)
	{
		case 0:
		{
			this->startPoint[0] = 0;
			this->startPoint[1] = rand() % m;
			break;
		}
		case 1:
		{
			this->startPoint[0] = n - 1;
			this->startPoint[1] = rand() % m;
			break;
		}
		case 2:
		{
			this->startPoint[0] = rand() % n;
			this->startPoint[1] = 0;
			break;
		}
		case 3:
		{
			this->startPoint[0] = rand() % n;
			this->startPoint[1] = m - 1;
			break;
		}
	}
}

int Maze::rows() const
{
	return this->m_rows;
}

int Maze::columns() const
{
	return this->m_columns;
}

int Maze::startI() const
{
	return this->startPoint[0];
}

int Maze::startJ() const
{
	return this->startPoint[1];
}

const MCell& Maze::cell(int i, int j) const
{
	return this->m_field[i * this->m_columns + j];
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2) const
{
	if (i1 < 0 || i1 > this->m_rows - 1 || i2 < 0 || i2 > this->m_rows - 1 ||
		j1 < 0 || j1 > this->m_columns - 1 || j2 < 0 || j2 > this->m_columns - 1)
		return false;
	if (i1 == i2)
		return this->m_field[i1 * this->m_columns + std::min(j1, j2)].right();
	if (j1 == j2)
		return this->m_field[std::min(i1, i2) * this->m_columns + j1].down();
	return false;
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2)
{
	if (i1 < 0 || i1 > this->m_rows - 1 || i2 < 0 || i2 > this->m_rows - 1 ||
		j1 < 0 || j1 > this->m_columns - 1 || j2 < 0 || j2 > this->m_columns - 1)
		return false;
	if (i1 == i2)
		return (this->m_field[i1 * this->m_columns + std::min(j1, j2)].m_right = true);
	if (j1 == j2)
		return (this->m_field[std::min(i1, i2) * this->m_columns + j1].m_down = true);
	return false;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2)
{
	if (i1 < 0 || i1 > this->m_rows - 1 || i2 < 0 || i2 > this->m_rows - 1 ||
		j1 < 0 || j1 > this->m_columns - 1 || j2 < 0 || j2 > this->m_columns - 1)
		return false;
	if (i1 == i2)
		return !(this->m_field[i1 * this->m_columns + std::min(j1, j2)].m_right = false);
	if (j1 == j2)
		return !(this->m_field[std::min(i1, i2) * this->m_columns + j1].m_down = false);
	return false;
}

void Maze::printMaze() const
{
	for (int i = 0; i < this->m_rows; i++)
	{
		for (int j = 0; j < this->m_columns; j++)
			std::cout << symbols[(hasConnection(i, j, i - 1, j) ? 1 : 0) +
							(hasConnection(i, j, i, j - 1) ? 8 : 0) +
							(this->cell(i, j).right() ? 2 : 0) +
							(this->cell(i, j).down() ? 4 : 0)];
		std::cout << std::endl;
	}
}

Maze::~Maze()
{
	delete[] this->m_field;
}