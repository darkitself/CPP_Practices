#pragma once
class MCell
{
private:
	bool m_down;
	bool m_right;
	MCell();
public:
	bool down() const;
	bool right() const;
	friend class Maze;
};