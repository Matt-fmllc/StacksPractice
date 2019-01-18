#pragma once

#include <cassert>



class Stack
{
	typedef enum _AllocationType
	{
		eAT_Illegal,
		eAT_FixedMem,
		eAT_DynamicMem,
		eAT_Max,
	}AllocationType; 

private:

protected:
	class Node {
	public:
		int		Data;
		Node*	pNext;

		Node() : Data(0), pNext(nullptr)
		{}
		~Node() {}
	};

	Node*	m_pRoot;

public:
	Stack() :
		m_pRoot(nullptr)
	{}
	~Stack() {}

	virtual void	Push(int iNewItem) = 0;
	virtual int		Pop() = 0;
	virtual void	Clear() = 0;

	int Count() const;
};


class Stack_DynamicMem : public Stack
{
private:
protected:
public:
	Stack_DynamicMem() {}
	~Stack_DynamicMem() {}

	virtual void Push(int _iNewItem);
	virtual int  Pop();
	virtual void Clear();
};

class Stack_FixedMem : public Stack
{
private:
protected:
public:
	Stack_FixedMem() {}
	~Stack_FixedMem() {}

	virtual void Push(int _iNewItem);
	virtual int  Pop();
	virtual void Clear();
};


class FixedStack
{
	struct Node {
		int Data;
		Node* pNext;
	};

private:
	Node* m_pRoot;
	Node* m_pNodes;
	int   m_iStackSize;

protected:
public:
	FixedStack(int _iStackSize) :
		m_pRoot(nullptr),
		m_pNodes(nullptr),
		m_iStackSize(0)
	{
		assert(_iStackSize >= 0);
		m_pRoot = (Node*)malloc(sizeof(Node)*_iStackSize);
		assert(m_pRoot);
		m_pNodes = m_pRoot;
		m_iStackSize = _iStackSize;
	}
	~FixedStack() {}

	void Push(int _iNewItem);
	int Pop();
};

void FixedStack::Push(int _iNewItem)
{
	if ((m_pRoot + 1) > m_pNodes + m_iStackSize) {
		// can wrap around here, or throw an error
		m_pRoot = m_pNodes;
		// top of stack, stack full
	}
	else {
		m_pRoot->pNext = ++m_pRoot;
	}
	m_pRoot->Data = _iNewItem;
	m_pRoot->pNext = nullptr;
}

int FixedStack::Pop()
{
	if ((m_pRoot - 1) < m_pNodes) {
		// bottom of stack, empty stack
		return -1;
	}
	else {
		int Data = m_pRoot->Data;
		m_pRoot--;
		return Data;
	}

}
