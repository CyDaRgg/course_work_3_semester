#pragma once
#include<iostream>

using namespace std;

template<class T>
class Myqueue
{
public:
	Myqueue();
	void push(T variable);
	void pop();

	T& front();
	T& back();

	T& peek(int id);

	void print();

	bool isEmpty();
	void clean();

	int amount();

	void pop_back();

	~Myqueue();


private:

	struct Node
	{
		Node(T var);
		Node* next;
		Node* previous;
		T data;
	};
	struct head_and_tail
	{
		head_and_tail();
		Node* head;
		Node* tail;

	};
	head_and_tail h_t;

};






template<class T>
Myqueue<T>::Myqueue()
{
}

template<class T>
void Myqueue<T>::push(T variable)
{
	if (h_t.head == nullptr && h_t.tail == nullptr)
	{
		h_t.head = new Node(variable);
		h_t.tail = h_t.head;
	}

	else
	{
		Node* temp;
		temp = h_t.tail;

		h_t.tail = new Node(variable);
		h_t.tail->next = temp;
		temp->previous = h_t.tail;
	}
}

template<class T>
void Myqueue<T>::pop()
{
	if (h_t.head == nullptr && h_t.tail == nullptr)
	{
		std::cout << "Нечего удалять!" << std::endl;
		return;
	}

	else
		if (h_t.head == h_t.tail)
		{
			delete h_t.head;
			h_t.head = h_t.tail = nullptr;
		}
		else
		{
			Node* temp;
			temp = (h_t.head)->previous;
			delete h_t.head;
			h_t.head = temp;
		}
}

template<class T>
T& Myqueue<T>::front()
{
	if (h_t.head == nullptr)
	{ }
		//throw Exception("fail in method front");
	return (h_t.head)->data;
}

template<class T>
T& Myqueue<T>::back()
{
	if (h_t.tail == nullptr)
	{ }
		//throw Exception("fail in method back");
	return (h_t.tail)->data;
}

template<class T>
T& Myqueue<T>::peek(int id)
{
	Node* temp;
	temp = h_t.head;

	for (int i = 1; i < id; ++i)
	{
		if (temp == nullptr)
		{
			std::cout << "Элемента под номером: " << id << " нету!" << std::endl;
			//throw Exception("fail in method peek");
		}
		temp = temp->previous;
	}
	if (temp == nullptr)
	{
		std::cout << "Элемента под номером: " << id << " нету!" << std::endl;
		//throw Exception("fail in method peek");
	}

	return temp->data;
}


template<class T>
void Myqueue<T>::print()
{
	while (h_t.head != nullptr)
	{
		std::cout << h_t.head->data << std::endl;
		pop();
	}
}


template<class T>
Myqueue<T>::Node::Node(T var)
{
	data = var;
	next = previous = nullptr;
}

template<class T>
Myqueue<T>::head_and_tail::head_and_tail()
{
	head = tail = nullptr;
}




template<class T>
bool Myqueue<T>::isEmpty()
{
	if (h_t.head == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
void Myqueue<T>::clean()
{
	while (h_t.head != nullptr)
	{
		pop();
	}
}

template<class T>
int Myqueue<T>::amount()
{
	int count = 0;
	Node* temp;
	temp = h_t.head;
	while (temp != nullptr)
	{
		count++;
		temp = temp->previous;
	}
	return count;
}

template<class T>
Myqueue<T>::~Myqueue()
{
	clean();
}

template<class T>
void Myqueue<T>::pop_back()
{
	if (h_t.head == nullptr && h_t.tail == nullptr)
	{
		std::cout << "Нечего удалять!" << std::endl;
		return;
	}

	else
		if (h_t.head == h_t.tail)
		{
			delete h_t.tail;
			h_t.head = h_t.tail = nullptr;
		}
		else
		{
			Node* temp;
			temp = (h_t.tail)->next;
			delete h_t.tail;
			h_t.tail = temp;
		}
}