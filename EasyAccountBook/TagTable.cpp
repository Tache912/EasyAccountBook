#include "stdafx.h"
#include "Tag.h"
#include "TagTable.h"

TagTable::TagTable()
{
	tableSize		=	DEFAULT_TABLE_SIZE;
	occupation		=	1;
	rootHash		=	Tag::rootHash;	
	tagTable		=	new Tag[tableSize];
	nullTag			=	Tag(Tag::nullTag);
	emptyTag		=	Tag(Tag::emptyTag);
	unsigned int table_Index	=	rootHash % tableSize;
	tagTable[table_Index].set_tagNameAndHash(Tag::rootTag, rootHash);
}
TagTable::TagTable(unsigned int tableSize_in)
{
	tableSize		=	tableSize_in;
	occupation		=	1;
	rootHash		=	Tag::rootHash;	
	tagTable		=	new Tag[tableSize];
	nullTag			=	Tag(Tag::nullTag);
	emptyTag		=	Tag(Tag::emptyTag);
	unsigned int table_Index	=	rootHash % tableSize;
	tagTable[table_Index].set_tagNameAndHash( Tag::rootTag, rootHash);
}
Tag &TagTable::findTag( string tag_in )
{
	unsigned int hash			=	BKDRHash(tag_in);
	unsigned int table_Index	=	hash % tableSize;
	
	if( occupation == tableSize )
	{
		cerr<<"散列表已满"<<endl;
		return nullTag;
	}
	while ((tagTable[table_Index].get_tagName()) != tag_in)
	{
		if((tagTable[table_Index].get_tagName()) == Tag::emptyTag)
		{
			return emptyTag;
		}
		table_Index++;
		if(table_Index >= tableSize) table_Index = 0;
	}
	return tagTable[table_Index];
}
bool TagTable::addTag( string tag_in )//向根添加Tag
{
	if( occupation > tableSize / 2)
	{
		resizeTable (tableSize * 2);
	}
	Tag & tagToAdd = findTag( tag_in );
	if( tagToAdd.get_tagName() == emptyTag.get_tagName() )//该Tag未被TagTable收录
	{
		unsigned int hash			=	BKDRHash(tag_in);
		unsigned int table_Index	=	hash % tableSize;
		while( (tagTable[table_Index].get_tagName()) != Tag::emptyTag && (tagTable[table_Index].get_tagName()) != Tag::deletedTag )
		{
			table_Index++;
			if(table_Index >= tableSize) table_Index = 0;
		}
		tagTable[table_Index].set_tagNameAndHash(tag_in, hash);
		tagTable[rootHash % tableSize].addSubTag(tagTable[table_Index]);
		//cout<< tagTable[rootHash % tableSize].get_tagName()<<endl;
		tagTable[table_Index].addParentTag(tagTable[rootHash % tableSize]);
		occupation++;
		return true;
	}
	return false;
}
bool TagTable::addTag( string parentTag_in, string tag_in)
{
	if(occupation > tableSize / 2)
	{
		resizeTable(tableSize * 2 );
	}
	Tag &parentTag = findTag( parentTag_in );
	Tag &tagToAdd = findTag( tag_in );
	if( parentTag.get_tagName() == emptyTag.get_tagName() )
	{
		return false;
	}
	else if( tagToAdd.get_tagName() == emptyTag.get_tagName() )//该Tag未被TagTable收录
	{
		unsigned int hash			=	BKDRHash(tag_in);
		unsigned int table_Index	=	hash % tableSize;
		while( (tagTable[table_Index].get_tagName()) != Tag::emptyTag && (tagTable[table_Index].get_tagName()) != Tag::deletedTag )
		{
			table_Index++;
			if(table_Index >= tableSize) table_Index = 0;
		}
		tagTable[table_Index].set_tagNameAndHash(tag_in, hash);
		tagTable[table_Index].addParentTag(parentTag);
		parentTag.addSubTag(tagTable[table_Index]);
		occupation++;
		return true;
	}
	else//该Tag已被收录
	{
		if(tagToAdd.hasParentTag(parentTag))//该Tag的parent已经是parentTag_in
		{
			return true;
		}
		else//parentTag_in不在该Tag的parent里
		{
			tagToAdd.addParentTag(parentTag);
			parentTag.addSubTag(tagToAdd);
			return true;
		}
	}
}
bool TagTable::editTag( string tag_old_in, string tag_new_in)
{
	Tag &oldTag = findTag( tag_old_in );
	Tag &newTag  = findTag( tag_new_in );
	if( oldTag.get_tagName() == Tag::emptyTag )
	{
		return false;
	}
	else if ( newTag.get_tagName() != Tag::emptyTag )
	{
		return false;
	}
	else 
	{
		unsigned int table_Index = oldTag.get_tagHashFunction(tableSize);
		while ((tagTable[table_Index].get_tagName()) != tag_old_in)
		{
			table_Index++;
			if(table_Index >= tableSize) table_Index = 0;
		}
		tagTable[table_Index].set_tagNameAndHash(Tag::deletedTag,Tag::deletedHash);
		unsigned int hash = BKDRHash(tag_new_in);
		table_Index = hash % tableSize;
		while( (tagTable[table_Index].get_tagName()) != Tag::emptyTag && (tagTable[table_Index].get_tagName()) != Tag::deletedTag )
		{
			table_Index++;
			if(table_Index >= tableSize) table_Index = 0;
		}
		tagTable[table_Index].set_tagNameAndHash(tag_new_in, hash);
		return true;
	}
}
bool TagTable::deleteTag (string Tag_in )
{

	Tag &tagToDel = findTag( Tag_in );

	if( tagToDel.get_tagName() == Tag::emptyTag )
	{
		return false;
	}
	else
	{
		unsigned int table_Index = tagToDel.get_tagHashFunction(tableSize);
		while ((tagTable[table_Index].get_tagName()) != Tag_in)
		{
			table_Index++;
			if(table_Index >= tableSize) table_Index = 0;
		}
		tagTable[table_Index].set_tagNameAndHash(Tag::deletedTag,Tag::deletedHash);
		tagToDel.delTag(this);

		if(occupation < tableSize / 8)
		{
			resizeTable(tableSize / 2 );
		}

		return true;
	}
}
bool isTag1BelongToTag2_Helper( Tag &tag1, Tag &tag2 )
{
	if ( tag1.hasParentTag(tag2) )
	{
		return true;
	}
	else
	{
		Linklist<Tag> &parentTags = tag1.get_parentTagList();
		Node<Tag> *currentNode = parentTags.getListHead();
		while(currentNode != nullptr)
		{
			if (currentNode -> object -> hasParentTag(tag2))
			{
				return true;
			}
			if (isTag1BelongToTag2_Helper(*(currentNode->object),tag2))
			{
				return true;
			}
			currentNode = currentNode -> nextNode;
		}
		return false;
	}
}
int TagTable::tagBelongTo( string tag1_in, string tag2_in )
{
	Tag &tag1 = findTag( tag1_in );
	Tag &tag2 = findTag( tag2_in );
	if ( tag1.get_tagName() == emptyTag.get_tagName() && tag2.get_tagName() != emptyTag.get_tagName())
	{
		return -1;
	}
	if ( tag1.get_tagName() != emptyTag.get_tagName() && tag2.get_tagName() == emptyTag.get_tagName() )
	{
		return -2;
	}
	if ( tag1.get_tagName() == emptyTag.get_tagName() && tag2.get_tagName() == emptyTag.get_tagName() )
	{
		return -3;
	}
	//now tag1 and tag2 can't be emptyTag anymore
	if(isTag1BelongToTag2_Helper(tag1,tag2))
	{
		return 2;
	}
	if(isTag1BelongToTag2_Helper(tag2,tag1))
	{
		return 1;
	}
	return 0;
}
std::string TagTable::toString()
{
	stringstream ss;
	for(unsigned int i = 0; i < tableSize; i++)
	{
		ss<<i<<" : "<<tagTable[i].toString()<<endl;
	}
	return ss.str();
}
unsigned int &TagTable::getOccupation()
{
	return occupation;
}
void TagTable::resizeHelper_1(Tag *newTagTable, unsigned int newSize, unsigned int index)//复制标签名称和hash值
{

	Linklist<Tag> &currentList = tagTable[index].get_subTagList();
	unsigned int newIndex = tagTable[index].get_tagHashFunction(newSize);
	while(newTagTable[newIndex].get_tagName() != Tag::emptyTag)
	{
		newIndex++;
	}
	newTagTable[newIndex].set_tagNameAndHash(tagTable[index].get_tagName(),tagTable[index].get_tagHashCode());
	
	currentList.resetCurrentNode();
	Node<Tag> *currentNode = currentList.getNextCurrentNode();
	while(currentNode != nullptr) 
	{
		int hashIndex = currentNode->object->get_tagHashFunction(tableSize);
		while (tagTable[hashIndex].get_tagName() != currentNode->object ->get_tagName() )
		{
			hashIndex++;
		}
		resizeHelper_1(newTagTable, newSize, hashIndex);
		currentNode = currentList.getNextCurrentNode();
	}
	currentList.resetCurrentNode();
}
void TagTable::resizeHelper_2(Tag *newTagTable, unsigned int newSize, unsigned int index)//重新构建关系链
{

	if(tagTable[index].get_tagName() != Tag::emptyTag )
	{
		Linklist<Tag> &oldParentTagList = tagTable[index].get_parentTagList();
		Linklist<Tag> &oldSubTagList = tagTable[index].get_subTagList();

		if( ! oldParentTagList.isEmpty() )
		{
			
			Linklist<Tag> &newParentTagList = newTagTable[tagTable[index].get_tagHashFunction(newSize)].get_parentTagList();
			Node<Tag> *oldParentTagNode = oldParentTagList.getListHead();
			Node<Tag> *oldParentTagNodeSave = oldParentTagNode;
			while(oldParentTagNode != nullptr)
			{
				newParentTagList.addNode(newTagTable[oldParentTagNode->object->get_tagHashFunction(newSize)]);
				oldParentTagNode = oldParentTagNode ->nextNode;
			}
			oldParentTagNode = oldParentTagNodeSave;
		}
		if( ! oldSubTagList.isEmpty() )
		{
			Linklist<Tag> &newSubTagList = newTagTable[tagTable[index].get_tagHashFunction(newSize)].get_subTagList();
			
			Node<Tag> *oldSubTagNode = oldSubTagList.getListHead();
			Node<Tag> *oldSubTagNodeSave = oldSubTagNode;
			while( oldSubTagNode != nullptr)
			{
				newSubTagList.addNode(newTagTable[oldSubTagNode->object->get_tagHashFunction(newSize)]);
				oldSubTagNode = oldSubTagNode -> nextNode;
			}
			oldSubTagNode = oldSubTagNodeSave;
			
		}
	}
	
	
	Linklist<Tag> &currentList = tagTable[index].get_subTagList();
	currentList.resetCurrentNode();
	Node<Tag> *currentNode = currentList.getNextCurrentNode();
	while(currentNode != nullptr) 
	{
		int hashIndex = currentNode->object->get_tagHashFunction(tableSize);
		while (tagTable[hashIndex].get_tagName() != currentNode->object ->get_tagName() )
		{
			hashIndex++;
		}
		resizeHelper_2(newTagTable, newSize, hashIndex);
		currentNode = currentList.getNextCurrentNode();
	}
	currentList.resetCurrentNode();
}
bool TagTable::resizeTable( unsigned int size_in )
{
	if( size_in <= occupation )
	{
		cerr<<"空间过小"<<endl;
		return false;
	}
	Tag *newTagTable = new Tag[size_in];
	if( newTagTable == nullptr )
	{
		cerr<<"新散列表创建失败"<<endl;
		return false;
	}
	resizeHelper_1(newTagTable,size_in,rootHash%tableSize);
	resizeHelper_2(newTagTable,size_in,rootHash%tableSize);
	delete [] tagTable;
	tagTable = newTagTable;
	tableSize = size_in;
	return true;
}