#include "stdafx.h"
#include "account.h"

using namespace std;

account::account()
{
	idKey		=	-1;
	happenDate	=	date();
	integerPart	=	0;
	dicimalPart	=	0;
	accountTags	=	Linklist<Tag>();
	remark		=	"这是默认构造函数所生成的对象\n";
}
account::account(unsigned int idKey_in, date &date_in, double money_in)
{
	idKey		=	idKey_in;
	happenDate	=	date_in;
	money_in	=	abs(money_in);
	integerPart	=	(unsigned int)money_in;
	dicimalPart	=	(unsigned int)((money_in * 100) - (integerPart * 100));
	accountTags	=	Linklist<Tag>();
	remark		=	"";
}
void account::changeDate(date &date_in)
{
	happenDate = date_in;
}
void account::changeMoney(double money_in)
{
	money_in	=	abs(money_in);
	integerPart	=	(unsigned int)money_in;
	dicimalPart	=	(unsigned int)((money_in * 100) - (integerPart * 100));
}
void account::addTag(Tag &tag_in)
{
	accountTags.addNode(tag_in);
}
bool account::delTag(Tag &tag_in)
{
	return accountTags.delNode(tag_in);
}
void account::addRemark(string remark_in)
{
	remark = remark + remark_in + "\n";
}
void account::changeRemark(string remark_in)
{
	remark = remark_in + "\n";
}