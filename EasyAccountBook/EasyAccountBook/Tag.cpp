#include "stdafx.h"
#include "Tag.h"

using namespace std;

unsigned int BKDRHash(string &str_in)
{
	const char *str = str_in.c_str();
    unsigned int seed = 13131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}//hash function

string			Tag::rootTag = string ("根标签");
unsigned int	Tag::rootHash = BKDRHash (Tag::rootTag);
string			Tag::emptyTag =  string ("空标签");
unsigned int	Tag::emptyHash = BKDRHash (Tag::emptyTag);
string			Tag::nullTag =  string ("非法标签");
unsigned int	Tag::nullHash = BKDRHash (Tag::nullTag);
string			Tag::deletedTag =  string ("已删除标签");
unsigned int	Tag::deletedHash = BKDRHash (Tag::deletedTag);

Tag::Tag()
{
	deleteMark			=	false;
	tagName				=	emptyTag;
	tagHash				=	emptyHash;
	parentTag			=	Linklist<Tag>();
	subTag				=	Linklist<Tag>();
}
Tag::Tag(string &tagName_in)
{
	deleteMark			=	false;
	tagName				=	string(tagName_in.c_str());
	tagHash				=	BKDRHash(tagName_in);
	parentTag			=	Linklist<Tag>();
	subTag				=	Linklist<Tag>();
}
bool Tag::hasParentTag()
{
	return !parentTag.isEmpty();
}
void Tag::delTag()
{
	deleteMark	=	true;
	tagName		=	deletedTag;
	tagHash		=	deletedHash;
	Node<Tag> *currentNode = parentTag.getListHead();
	while(currentNode != nullptr)
	{
		currentNode->object->subTag.delNode(*this);
		currentNode = currentNode -> nextNode;
	}
	currentNode = subTag.getListHead();
	while(currentNode != nullptr)
	{
		currentNode->object->parentTag.delNode(*this);
		if( currentNode-> object ->parentTag.isEmpty() )
		{
			currentNode-> object -> delTag();
		}
		currentNode = currentNode -> nextNode;
	}
}
bool Tag::hasParentTag(Tag &parentTag_in)
{
	if ( parentTag.findNode(parentTag_in) != nullptr )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Tag::hasSubTag(Tag &subTag_in)
{
	if ( subTag.findNode(subTag_in) != nullptr )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Tag::addParentTag( Tag &parentTag_in )
{
	if ( parentTag.findNode( parentTag_in ) != nullptr )
	{
		return false;
	}
	else
	{
		parentTag.addNode( parentTag_in );
		return true;
	}
}
bool Tag::addSubTag( Tag &subTag_in )
{
	if ( subTag.findNode( subTag_in ) != nullptr )
	{
		return false;
	}
	else
	{
		subTag.addNode( subTag_in );
		return true;
	}
}
void Tag::set_tagName( string &tagName_in)
{
	tagName	=	string (tagName_in.c_str());
	tagHash	=	BKDRHash(tagName_in);
}
void	Tag::set_tagNameAndHash(string &tagName_in, unsigned int tagHash_in)
{
	tagName	=	string (tagName_in.c_str());
	tagHash	=	tagHash_in;
}
string &Tag::get_tagName()
{
	return tagName;
}
unsigned int Tag::get_tagHashCode()
{
	return tagHash;
}
unsigned int Tag::get_tagHashFunction(unsigned int size_in)
{
	return tagHash % size_in;
}
Linklist<Tag> &Tag::get_parentTagList()
{
	return parentTag;
}
Tag::~Tag()
{
	parentTag.delList();
	subTag.delList();
}


