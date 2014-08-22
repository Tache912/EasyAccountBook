// EasyAccountBook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TagTable.h"
#include "account.h"


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	TagTable &tagTable = TagTable(8);
	tagTable.addTag("食品");
	tagTable.addTag("日用品");
	account &testaccount = account(101,date(),111.119999);
	testaccount.addTag(tagTable.findTag("食品"));
	testaccount.addTag(tagTable.findTag("日用品"));
	testaccount.addRemark("这是测试用的备注");
	cout<<testaccount.getMoney()<<endl;
	cout<<testaccount.tagsToString()<<endl;
	cout<<endl<<testaccount.toString()<<endl;
	system("pause");
	return 0;
}

