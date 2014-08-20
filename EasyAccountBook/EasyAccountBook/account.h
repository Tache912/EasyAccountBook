#include "stdafx.h"
#include "Tag.h"
#include "TagTable.h"
#include "date.h"

using namespace std;

class account
{
private:
	unsigned int	idKey;
	date			happenDate;
	unsigned int	integerPart;
	unsigned int	dicimalPart;
	vector<Tag>		accountTags;
	string			remark;//±¸×¢
	
public:
	account();
	account(unsigned int idKey_in, date &date_in, double money);
	void	changeDate(date &date_in);
	void	addTag(Tag &tag_in);
	bool	delTag(Tag &tag_in);
	void	addRemark(string remark_in);
	void	changeRemark(string remark_in);


};
