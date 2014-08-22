#include "stdafx.h"
#include "account.h"
#include "Tag.h"

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
account::~account()
{
	accountTags.delList();
}
unsigned int account::getIdKey()
{
	return idKey;
}
void account::setDate(date &date_in)
{
	happenDate = date_in;
}
date account::getDate()
{
	return happenDate;
}

void account::setMoney(double money_in)
{
	money_in	=	abs(money_in);
	integerPart	=	(unsigned int)money_in;
	dicimalPart	=	(unsigned int)((money_in * 100) - (integerPart * 100));
}
double account::getMoney()
{
	return ((double)integerPart + ((double)dicimalPart)/100);
}

void account::addTag(Tag &tag_in)
{
	accountTags.addNode(tag_in);
}
bool account::delTag(Tag &tag_in)
{
	return accountTags.delNode(tag_in);
}
Linklist<Tag> &account::getTags()
{
	return accountTags;
}
string account::tagsToString()
{
	string output;
	accountTags.resetCurrentNode();
	Node<Tag> *currentNode = accountTags.getNextCurrentNode();
	while(currentNode != nullptr)
	{
		if(currentNode ->nextNode != nullptr)
		{
			output += currentNode -> object -> get_tagName() + "|";
		}
		else
		{
			output += currentNode -> object -> get_tagName();
		}
		currentNode = accountTags.getNextCurrentNode();
	}
	accountTags.resetCurrentNode();
	return output;
}

void account::addRemark(string remark_in)
{
	remark = remark + remark_in + "\n";
}
void account::setRemark(string remark_in)
{
	remark = remark_in + "\n";
}
const string &account::getRemark()
{
	return remark;
}
string account::toString()
{
	stringstream output;
	output << "编号：" << idKey << endl;
	output << "日期：" << happenDate.toString() << endl;
	output << "金额：" << getMoney() <<endl;
	output << "标签：" << tagsToString() << endl;
	output << "备注：" << getRemark() << endl;
	return output.str();
}
