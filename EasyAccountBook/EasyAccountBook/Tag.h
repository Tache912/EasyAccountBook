#include "stdafx.h"
using namespace std;

class TagNode;

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
	void							delTag();
	bool							addParentTag(Tag &parentTag_in);
	bool							addSubTag(Tag &subTag_in);
	void							set_tagName(string	&tagName_in);
	void							set_tagNameAndHash(string &tagName_in, unsigned int tagHash_in);
	string							&get_tagName();
	unsigned int					get_tagHashCode();
	unsigned int					get_tagHashFunction(unsigned int size_in);
	Linklist<Tag>					&get_parentTagList();
	string							toString();
	//Linklist<Tag>					*get_subTagList();
	~Tag();
};
