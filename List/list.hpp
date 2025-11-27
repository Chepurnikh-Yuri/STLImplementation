#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <utility>
#include <stdexcept>

template<typename T>
class List 
{
public:
	struct Node 
	{
		T val;
		Node* next;
		Node* prev;

		Node(const T& val) noexcept :
			val(val), next(nullptr), prev(nullptr) { }

		T& operator*()  
		{
			return val;
		}

		const T& operator*() const   
		{
			return val;
		}
	};

	List() noexcept : m_head(nullptr), m_tail(nullptr) { }

	// copy operations
	List(const List& other)
	{
		Node* otherCurr = other.m_head;

		while (otherCurr)
		{
			Node* newNode = new Node(otherCurr->val);

			if (!m_head)
			{
				m_head = m_tail = newNode;
			}

			else 
			{
				m_tail->next = newNode;
				newNode->prev = m_tail;
				m_tail = newNode;
			}

			otherCurr = otherCurr->next;
		}
	}

	List& operator=(const List& other)
	{
		if (this != &other)
		{
			clear();

			Node* otherCurr = other.m_head;

			while (otherCurr)
			{
				Node* newNode = new Node(otherCurr->val);

				if (!m_head)
				{
					m_head = m_tail = newNode;
				}

				else 
				{
					m_tail->next = newNode;
					newNode->prev = m_tail;
					m_tail = newNode;
				}

				otherCurr = otherCurr->next;
			}
		}

		return *this;
	}

	// move operations
	List(List&& other) noexcept : 
		m_head(other.m_head),
		m_tail(other.m_tail)
	{
		other.m_tail = nullptr;
		other.m_head = nullptr;
	}

	List& operator=(List&& other) noexcept
	{
		if (this != &other)
		{
			clear();

			m_tail = other.m_tail;
			m_head = other.m_head;
			other.m_tail = nullptr;
			other.m_head = nullptr;
		}

		return *this;
	}

	// init_list ctor
	List(const std::initializer_list<T>& init) 
	{
		if (!init.size())
			return;

		auto it = init.begin();

		m_head = m_tail = new Node(*it);

		++it;

		for (; it != init.end(); ++it)
		{
			Node* newNode = new Node(*it);
			m_tail->next = newNode;
			newNode->prev = m_tail;
			m_tail = newNode;
		}
	}

	// dtor
	~List() 
	{
		clear();
	}

	// references
	T& front() { return m_head->val; }
	const T& front() const { return m_head->val; }

	T& back() { return m_tail->val; }
	const T& back() const { return m_tail->val; }

	// iterators
	Node* begin() { return m_head; }
	const Node* begin() const { return m_head; }

	Node* end() { return m_tail->next; }
	const Node* end() const { return m_tail->next; }

	bool empty() const { return !m_head; }
	
	size_t size() const 
	{
		size_t count = 0;

		Node* tmp = m_head;

		while (tmp)
		{
			++count;
			tmp = tmp->next;
		}

		return count;
	}

	void pushBack(const T& val)
	{
		Node* newNode = new Node(val);

		if (!m_head)
		{
			m_head = m_tail = newNode;
		}
		else
		{
			newNode->prev = m_tail;
			m_tail->next = newNode;
			m_tail = newNode;
		}
	}

	void pushFront(const T& val)
	{
		Node* newNode = new Node(val);

		if (!m_head)
		{
			m_head = m_tail = newNode;
		}
		else 
		{
			newNode->next = m_head;
			m_head->prev = newNode;
			m_head = newNode;
		}
	}

	T popBack() 
	{
		if (!m_head)
			throw std::runtime_error("The list is empty");

		if (m_head == m_tail)
		{
			T val = m_head->val;
			delete m_head;
			m_head = m_tail = nullptr;
			return val;
		}

		Node* tmp = m_tail;
		m_tail = m_tail->prev;
		m_tail->next = nullptr;
		T val = tmp->val;
		delete tmp;
		return val;
	}

	T popFront() 
	{
		if (!m_head)
			throw std::runtime_error("The list is empty");

		if (m_head == m_tail)
		{
			T val = m_head->val;
			delete m_head;
			m_head = m_tail = nullptr;
			return val;
		}

		Node* tmp = m_head;
		m_head = m_head->next;
		m_head->prev = nullptr;
		T val = tmp->val;
		delete tmp;
		return val;
	}

	void clear() 
	{
		while (m_head)
		{
			Node* tmp = m_head;
			m_head = m_head->next;
			delete tmp;
		}

		m_tail = nullptr;
	}

	void print() const noexcept 
	{
		Node* tmp = m_head;

		while (tmp)
		{
			std::cout << tmp->val << " -> ";
			tmp = tmp->next;
		}
		std::cout << " nullptr" << std::endl;
	}

private:
	Node* m_head;
	Node* m_tail;
};

// 1 <-> 2 <-> 3 <-> 4 <-> 5 -> nullptr
// ^                       ^
// m_head                 m_tail

#endif // LIST_HPP