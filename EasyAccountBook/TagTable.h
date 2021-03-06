#ifndef TAGTABLE_H
#define TAGTABLE_H

#include "stdafx.h"
#include "Tag.h"
#define DEFAULT_TABLE_SIZE 8
class Tag;
class TagTable
{
private:
	unsigned int	tableSize;
	unsigned int	occupation;
	unsigned int	rootHash;
	Tag				nullTag;
	Tag				emptyTag;
	Tag				*tagTable;
public:
	TagTable();
	TagTable( unsigned int tableSize_in );
	Tag			&findTag( string tag_in );
	bool		addTag( string tag_in );
	bool		addTag( string parentTag_in, string tag_in);
	bool		editTag( string tag_old_in, string tag_new_in);
	bool		deleteTag( string Tag_in );
	int			tagBelongTo( string tag1_in, string tag2_in);
	std::string	toString();
	unsigned int &getOccupation();
	bool		resizeTable( unsigned int size_in );
	void		resizeHelper_1(Tag *newTagTable, unsigned int newSize, unsigned int index);
	void		resizeHelper_2(Tag *newTagTable, unsigned int newSize, unsigned int index);

};
#endif

