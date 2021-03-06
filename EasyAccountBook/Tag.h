#include "stdafx.h"
#ifndef TAG_H
#define TAG_H

using namespace std;
class TagTable;

unsigned int BKDRHash(string &str_in);

class Tag
{
private:
	bool				deleteMark;
	string				tagName;
	unsigned int		tagHash;
	Linklist<Tag>		parentTag;
	Linklist<Tag>		subTag;


public:
	static	string			rootTag;
	static	unsigned int	rootHash;
	static  string			emptyTag;
	static  unsigned int	emptyHash;
	static	string			nullTag;
	static	unsigned int	nullHash;
	static  string			deletedTag;
	static  unsigned int	deletedHash;


									Tag();
									Tag(string &tagName_in);
	bool							hasParentTag(Tag &parentTag_in);
	bool							hasParentTag();
	bool							hasSubTag(Tag &subTag_in);
	void							delTag(TagTable *table_in);
	bool							addParentTag(Tag &parentTag_in);
	bool							addSubTag(Tag &subTag_in);
	void							set_tagName(string	&tagName_in);
	void							set_tagNameAndHash(string &tagName_in, unsigned int tagHash_in);
	string							&get_tagName();
	unsigned int					get_tagHashCode();
	unsigned int					get_tagHashFunction(unsigned int size_in);
	Linklist<Tag>					&get_parentTagList();
	Linklist<Tag>					&get_subTagList();
	string							toString();
	Tag&							operator=(const Tag& tag_rignt);

	//Linklist<Tag>					*get_subTagList();
	~Tag();
};
#endif
