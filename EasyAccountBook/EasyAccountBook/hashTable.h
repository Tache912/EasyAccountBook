#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename T>
class HashTable
{
public:
	unsigned int	size;
	unsigned int	occupation;
	T				*object;

	HashTable();
	HashTable(unsigned int size_in);
	bool isEmpty();

	bool	findObject(T value_in );
	bool	addObject( string parentTag_in, string tag_in);
	bool	editTag( string tag_old_in, string tag_new_in);
	bool	deleteTag( string Tag_in );
	void	addNode(T *object_in);
	bool delNode(T *object_in);
	Linklist<T> *findNode(T *object_in);

	~Linklist();
};

#endif