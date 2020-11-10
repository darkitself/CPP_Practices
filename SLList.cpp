#include "SLList.h"

SLList::SLList(int data)
{
	this->m_data = data;
	this->m_nextElem = nullptr;
}

int SLList::getData() const
{
	return this->m_data;
}

void SLList::setData(int data)
{
	m_data = data;
}

SLList* SLList::next() const
{
	return this->m_nextElem;
}

bool SLList::hasNext() const
{
	return this->m_nextElem != nullptr;
}

SLList* SLList::beginList(int data)
{
	return new SLList(data);
}

SLList* SLList::addElement(int data)
{
	SLList* currElem = this;
	while (currElem->hasNext())
		currElem = currElem->m_nextElem;
	try
	{
		currElem->m_nextElem = new SLList(data);
	}
	catch(...)
	{
		currElem->m_nextElem = nullptr;
	}
	return currElem->m_nextElem;
}

void SLList::removeNext()
{
	if (this->hasNext())
	{
		SLList* t = this->m_nextElem->m_nextElem;
		this->m_nextElem->m_nextElem = nullptr;
		delete this->m_nextElem;
		this->m_nextElem = t;
	}
}

SLList::~SLList()
{
	if (this->hasNext())
		delete this->m_nextElem;
}


