#include "stdafx.h"


using namespace std;
class Tag;
class account
{
private:
	unsigned int	idKey;
	date			happenDate;
	unsigned int	integerPart;
	unsigned int	dicimalPart;
	Linklist<Tag>	accountTags;
	string			remark;//备注
	
public:
	account();
	account(unsigned int idKey_in, date &date_in, double money_in);
	~account();

	unsigned int	getIdKey();

	void			setDate(date &date_in);
	date			getDate();
	
	void			setMoney(double money_in);
	double			getMoney();

	void			addTag(Tag &tag_in);
	bool			delTag(Tag &tag_in);
	Linklist<Tag>	&getTags();
	string			tagsToString();

	void			addRemark(string remark_in);
	void			setRemark(string remark_in);
	const string	&getRemark();

	string			toString();

	
};
