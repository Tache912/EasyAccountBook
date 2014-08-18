#ifndef LINKLIST_H
#define LINKLIST_H
#include "Node.h"
template <typename T>
class Linklist
{
private:
	unsigned int	size;
	Node<T>			*listHead;
	Node<T>			*listTail;
	Node<T>			*currentNode;

public:
				Linklist();
				~Linklist();

	bool		isEmpty();	
	void		addNode	(T &object_in);
	Node<T>		*findNode(T &object_in);
	Node<T>		*getListHead();
	bool		delNode	(T &object_in);
	void		delList();
	
};
template <typename T>
Linklist<T>::Linklist()
{
	size		=	0;
	listHead	=	nullptr;
	listTail	=	nullptr;
	currentNode	=	nullptr;
}
template <typename T>
void Linklist<T>::addNode(T &object_in)
{
	if( size == 0 )
	{
		listHead = new Node<T>(nullptr, nullptr, object_in);
		listTail = listHead;
		size++;
	}
	else
	{
		listTail -> nextNode = new Node<T>(listTail, nullptr, object_in);
		listTail = listTail -> nextNode;
		size++;
	}
}
template <typename T>
Node<T> *Linklist<T>::findNode(T &object_in)
{
	currentNode = listHead;
	if( currentNode != nullptr )
	{
		while( currentNode != nullptr )
		{
			if( currentNode ->object == &object_in )
			{
				Node<T> *returnNode = currentNode;
				currentNode = nullptr;
				return returnNode;
			}
			currentNode = currentNode ->nextNode;
		}
	}
	return nullptr;
}
template <typename T>
Node<T> *Linklist<T>::getListHead()
{
	return listHead;
}
template <typename T>
bool Linklist<T>::delNode(T &object_in)
{
	currentNode = findNode(object_in);
	if( currentNode != nullptr )
	{
		if( size > 1 && currentNode -> nextNode == nullptr )//currentNode is listTail
		{
			listTail = currentNode -> previrousNode;
			listTail -> nextNode = nullptr;

		}
		else if( size > 1 && currentNode -> previrousNode == nullptr)//currentNode is listHead
		{
			listHead = currentNode -> nextNode;
			listTail -> previrousNode = nullptr;
		}
		else if( size > 1 )//currentNode is in somewhere middle
		{
			currentNode -> nextNode -> previrousNode = currentNode -> previrousNode;
			currentNode -> previrousNode -> nextNode = currentNode -> nextNode;
		}
		else if( size == 1)//just one node in list
		{
			//do nothing
		}
		delete currentNode;
		currentNode = nullptr;
		size--;
		return true;
	}
	else
	{
		return false;
	}
}
template <typename T>
bool Linklist<T>::isEmpty()
{
	return (bool)size;
}
template <typename T>
Linklist<T>::~Linklist()
{
	currentNode = listHead;
	if( currentNode != nullptr )
	{
		while(currentNode -> nextNode != nullptr)
		{
			currentNode = currentNode -> nextNode;
			delete currentNode ->previrousNode;
			size--;
		}
		delete currentNode;
		size--;
		listHead = nullptr;
		listTail = nullptr;
		currentNode = nullptr;
	}
}
template <typename T>
void Linklist<T>::delList()
{
	currentNode = listHead;
	if( currentNode != nullptr )
	{
		while(currentNode -> nextNode != nullptr)
		{
			currentNode = currentNode -> nextNode;
			delete currentNode ->previrousNode;
			size--;
		}
		delete currentNode;
		size--;
		listHead = nullptr;
		listTail = nullptr;
		currentNode = nullptr;
	}
}
#endif