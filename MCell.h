#pragma once

class MCell
{
public:
	bool down() const;
	bool right() const;
	friend class Maze;
private:
	bool m_down;
	bool m_right;
	MCell();
};