#include "stdafx.h"

#define DEFAULT_TABLE_SIZE 1024


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
	Tag		&findTag( string tag_in );
	bool	addTag( string tag_in );
	bool	addTag( string parentTag_in, string tag_in);
	bool	editTag( string tag_old_in, string tag_new_in);
	bool	deleteTag( string Tag_in );
	int		tagBelongTo( string tag1_in, string tag2_in);
	//void	resizeTable( unsigned int size_in );
};
