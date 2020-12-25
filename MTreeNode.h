#pragma once

class MTreeNode
{
public:
	int i() const;
	int j() const;
	const MTreeNode* parent() const;
	const MTreeNode* child(const int i) const;
	int distance() const;
	int childCount() const;
	bool addChild(const int i, const int j);
	MTreeNode* hasChild(const int i, const int j) const;
	MTreeNode* searchNode(const int i, const int j) const;
	static MTreeNode* beginTree(const int i, const int j);
	~MTreeNode();
private:
	int m_i = 0, m_j = 0;
	MTreeNode* m_parent = nullptr;
	MTreeNode* m_children[4];
	int m_childCount = 0;
	int m_distance = 0;
	MTreeNode(MTreeNode* parent);
};

