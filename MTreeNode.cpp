#include "MTreeNode.h"

MTreeNode::MTreeNode(MTreeNode* parent)
{
	m_parent = parent;
	m_distance = parent != nullptr ? parent->distance() + 1 : 0;
}

int MTreeNode::i() const
{
	return m_i;
}

int MTreeNode::j() const
{
	return m_j;
}

const MTreeNode* MTreeNode::parent() const
{
	return m_parent;
}

const MTreeNode* MTreeNode::child(int i) const
{
	return m_children[i];
}

int MTreeNode::distance() const
{
	return m_distance;
}

int MTreeNode::childCount() const
{
	return m_childCount;
}

bool MTreeNode::addChild(int i, int j)
{
	if (!(this->m_i - i == 0 && (this->m_j - j == 1 || this->m_j - j == -1)
		|| this->m_j - j == 0 && (this->m_i - i == 1 || this->m_i - i == -1)))
		return false;
	this->m_children[this->m_childCount] = new MTreeNode(this);
	this->m_children[this->m_childCount]->m_i = i;
	this->m_children[this->m_childCount]->m_j = j;
	this->m_childCount++;
	return true;
}

MTreeNode* MTreeNode::hasChild(int ci, int cj)
{
	for (int i = 0; i < this->m_childCount; i++)
		if (this->m_children[i]->m_i == ci && this->m_children[i]->m_j == cj)
			return m_children[i];
	return nullptr;
}

MTreeNode* MTreeNode::searchNode(int i, int j)
{
	queue<MTreeNode*> nodes;
	nodes.push(this);
	while (!nodes.empty())
	{
		MTreeNode* node = nodes.front();
		nodes.pop();
		if (node->m_i == i && node->m_j == j)
			return node;
		for (int i = 0; i < node->m_childCount; i++)
			nodes.push(node->m_children[i]);
	}
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	MTreeNode* node = new MTreeNode(nullptr);
	node->m_i = i;
	node->m_j = j;
	return node;
}

MTreeNode::~MTreeNode()
{
	for (int i = 0; i < this->m_childCount; i++)
		delete m_children[i];
}
