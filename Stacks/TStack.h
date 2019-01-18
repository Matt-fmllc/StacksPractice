#pragma once

#include <cassert>
#include <mutex>
#include <memory>

namespace StackTemplate {


	// Stack 
	// Templated Stack Implementation
	// handles both dynamic and fixed memory allocation
	// Threadsafe implementation
	// 
	// Basic Methods:
	//		Pop() - Gets an Element from the Stack
	//		Push(Type) - Adds an Element to the Stack
	//		IsEmpty() - Determines if the Stack contains any elements

	template<class T>
	class TStack
	{
	public:
		// defines memory handling types
		typedef enum _AllocationType
		{
			eAT_Illegal,
			eAT_FixedMem,
			eAT_DynamicMem,
			eAT_Max,
		}AllocationType;

	private:
		// Stack Node
		// Data struct for organizing the Stacks data
		struct TNode {
			T		Data;
			TNode*	pNext;
		};

		std::mutex m_Mutex;

		// Stack Variables
		// current Stack root
		TNode*	m_pRoot;		
		// allocation for fixed mem scenario
		TNode*	m_pNodes;			// relevent to the fixed mem scenario
		// size of the allocation for fixed mem scenario
		int		m_iStackSize;		// relevant to the fixed mem scenario
		// type of memory management for this stack
		AllocationType	m_eAllocationType;

	public:
		// Public Methods
		virtual inline bool Push(T const& NewItem);
		virtual inline T Pop();
		virtual inline bool IsEmpty();

		// Constructors/Destructor
		TStack();
		TStack(AllocationType _eAllocType, int _iStackSize);
		virtual ~TStack();
	};

	// Default Constructor
	// defaults to dynamic memory allocation strategy
	template<class T>
	TStack<T>::TStack() :
		m_pRoot(nullptr), m_pNodes(nullptr), m_iStackSize(-1), m_eAllocationType(eAT_Illegal)
	{
		m_eAllocationType = eAT_DynamicMem;
		m_iStackSize = -1;
	}

	// Complex Constructor
	// Allows definition of memory handling strategy
	// and allocation size of stack for fixed memory strategy
	template<class T>
	TStack<T>::TStack(AllocationType _eAllocType, int _iStackSize) :
		m_pRoot(nullptr), m_pNodes(nullptr), m_iStackSize(-1), m_eAllocationType(eAT_Illegal)
	{
		m_Mutex.lock();
		
		assert(_iStackSize > 0);
		assert(_eAllocType > eAT_Illegal && _eAllocType < eAT_Max);
		m_eAllocationType = _eAllocType;
		m_iStackSize = _iStackSize;
		if (m_eAllocationType == eAT_FixedMem) {
			m_pRoot = (TNode*) malloc(sizeof(TNode) * _iStackSize);
			assert(m_pRoot);
			m_pNodes = m_pRoot;
		}

		m_Mutex.unlock();
	}

	// Destructor
	template<class T>
	TStack<T>::~TStack()
	{
		if (m_eAllocationType == eAT_DynamicMem) {
			TNode* pNode = m_pRoot;
			while (pNode != nullptr) {
				TNode* pTemp = pNode;
				pNode = pNode->pNext;
				delete pTemp;
			}
		}
		else {
			free(m_pNodes);
		}
	}


	// Push
	// Adds elements to the Stack
	// Utilizes thread safe approach for adding elements
	template<class T>
	bool TStack<T>::Push(T const& NewItem)
	{
		m_Mutex.lock();

		if (m_eAllocationType == eAT_DynamicMem) {
			TNode* pNode = new TNode();
			if (!pNode) {
				m_Mutex.unlock();
				return false;
			}
			pNode->Data = NewItem;
			pNode->pNext = m_pRoot;
			m_pRoot = pNode;

			m_Mutex.unlock();
			return true;
		}
		else {
			if ((m_pRoot + 1) > m_pNodes + m_iStackSize) {
				// can wrap around here, or throw an error
				m_pRoot = m_pNodes;
				// top of stack, stack full
			}
			else {
				m_pRoot->pNext = ++m_pRoot;
			}
			m_pRoot->Data = NewItem;
			m_pRoot->pNext = nullptr;

			m_Mutex.unlock();
			return true;
		}

		m_Mutex.unlock();

		return false;
	}


	// Pop
	// Retrieves an element from the Stack
	// Utilizes threadsafe approach to retrieving elements
	template<class T>
	T TStack<T>::Pop()
	{
		m_Mutex.lock();

		if (m_eAllocationType == eAT_DynamicMem) {
			if (m_pRoot == nullptr) {
				m_Mutex.unlock();
				return (T)0;
			}

			TNode* pNode = m_pRoot;
			m_pRoot = pNode->pNext;
			T Data = pNode->Data;
			delete pNode;

			m_Mutex.unlock();
			return Data;
		}
		else {
			if ((m_pRoot - 1) < m_pNodes) {
				// bottom of stack, empty stack
				m_Mutex.unlock();
				return (T)0;
			}
			else {
				T Data = m_pRoot->Data;
				m_pRoot--;
				m_Mutex.unlock();
				return Data;
			}
		}
	}

	
	// IsEmpty
	// Determines if the stack is empty
	template<class T>
	bool TStack<T>::IsEmpty()
	{
		if (m_eAllocationType == eAT_DynamicMem) {
			if (!m_pRoot) {
				return true;
			}
		}
		else {
			if (m_pRoot == m_pNodes) {
				return true;
			}
		}

		return false;
	}


} // end namespace