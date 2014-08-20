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
	Tag &tagToAdd = findTag( tag_in );
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
	Tag &parentTag = findTag( parentTag_in );
	Tag &tagToAdd  = findTag( tag_in );
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
		tagToDel.delTag();
		occupation--;
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
void TagTable::resizeHelper(unsigned int index)//递归遍历标签树
{

	Linklist<Tag> &currentList = tagTable[index].get_subTagList();
	cout<< tagTable[index].get_tagName()<<endl;
	currentList.resetCurrentNode();
	Node<Tag> * currentNode = currentList.getNextCurrentNode();
	while(currentNode != nullptr) 
	{
		int hashIndex = currentNode->object->get_tagHashFunction(tableSize);
		while (tagTable[hashIndex].get_tagName() != currentNode->object ->get_tagName() )
		{
			hashIndex++;
		}
		resizeHelper(hashIndex);
		currentNode = currentList.getNextCurrentNode();
	}
	currentList.resetCurrentNode();
}
bool TagTable::resizeTable( unsigned int size_in )
{
	if( size_in <= occupation )
	{
		cerr<<"原来散列表就够满了，你要作死么？"<<endl;
		return false;
	}
	Tag *newTagTable = new Tag[size_in];
	if( newTagTable == nullptr )
	{
		cerr<<"新散列表创建失败"<<endl;
		return false;
	}
	
	

	tableSize = size_in;
	return true;
}