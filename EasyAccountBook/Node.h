#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
	Node<T>	*previrousNode;
	Node<T>	*nextNode;
	T		*object;
	Node();
	Node(Node<T> *previrousNode_in,Node<T> *nextNode_in, T &object_in);
	~Node();
};
template <typename T>
Node<T>::Node()
{
	previrousNode	=	nullptr;
	nextNode		=	nullptr;
	object			=	nullptr;
}
template <typename T>
Node<T>::Node(Node<T> *previrousNode_in,Node<T> *nextNode_in, T &object_in)
{
	previrousNode	=	previrousNode_in;
	nextNode		=	nextNode_in;
	object			=	&object_in;
}
template <typename T>
Node<T>::~Node()
{
	if(previrousNode != nullptr)
	{
		previrousNode -> nextNode = nextNode;
	}
	if(nextNode != nullptr)
	{
		nextNode -> previrousNode = previrousNode;
	}
	previrousNode	=	nullptr;
	nextNode		=	nullptr;
	object			=	nullptr;
}

#endif