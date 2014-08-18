#include "Tag.h"
#include "TagTable.h"
#include <vector>
#include <string>

using namespace std;

class date
{
	unsigned	int	dateValue;
};

class account
{
	unsigned	int	idKey;
	date					happenDate;
	unsigned	int	integerPart;
	unsigned	int	dicimalPart;
	vector<Tag*>	accountTags;
	string				remark;
};
