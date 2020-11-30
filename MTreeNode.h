#pragma once
class MTreeNode
{
private:
	int m_i = 0, m_j = 0;
	MTreeNode* m_parent = nullptr;
	MTreeNode* m_children = nullptr;
	int m_childCount = 0;
	int m_distance = 0;
	MTreeNode();
	MTreeNode(MTreeNode* parent);
public:
	int i() const;
	int j() const;
	const MTreeNode* parent() const;
	const MTreeNode* child(int i) const;
	int distance() const;
	int childCount() const;
	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);
	static MTreeNode* beginTree(int i, int j);
	~MTreeNode();
};

