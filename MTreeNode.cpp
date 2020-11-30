#include "MTreeNode.h"

MTreeNode::MTreeNode()
{

}

MTreeNode::MTreeNode(MTreeNode* parent)
{
	this->m_parent = parent;
	this->m_children = new MTreeNode[2];
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
	return m_children + i;
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
	if (this->j() - j == 0 && this->i() - i == -1)
	{
		this->m_children[0].m_parent = this;
		this->m_children[0].m_distance = this->m_distance + 1;
		this->m_children[0].m_children = new MTreeNode[2];
		this->m_children[0].m_i = i;
		this->m_children[0].m_j = j;
		this->m_childCount++;
		return true;
	}
	else if (this->i() - i == 0 && this->j() - j == -1)
	{
		this->m_children[1].m_parent = this;
		this->m_children[1].m_distance = this->m_distance + 1;
		this->m_children[1].m_children = new MTreeNode[2];
		this->m_children[1].m_i = i;
		this->m_children[1].m_j = j;
		this->m_childCount++;
		return true;
	}
	return false;
}

MTreeNode* MTreeNode::hasChild(int i, int j)
{
	if (this->j() - j == 0 && this->i() - i == -1 && this->m_children[0].m_parent != nullptr)
	{
		return this->m_children;
	}
	else if (this->i() - i == 0 && this->j() - j == -1 && this->m_children[1].m_parent != nullptr)
	{
		return this->m_children + 1;
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
	if(m_children != nullptr)
		delete[] m_children;
}
