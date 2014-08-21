// EasyAccountBook.cpp : 定义控制台应用程序的入口点。
//



#include "stdafx.h"
#include "Tag.h"
#include "TagNode.h"
#include "TagTable.h"
#include "date.h"


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	TagTable testTable = TagTable(8);

	testTable.addTag("食品");
	testTable.addTag("家用电器");
	testTable.addTag("家用电器","热水器");
	testTable.addTag("食品","肉类");
	testTable.addTag("肉类","鱼");

	cout<<testTable.getOccupation()<<endl;
	cout<<testTable.toString()<<endl;

	cout<<testTable.tagBelongTo("鱼","食品")<<endl;

	testTable.deleteTag("食品");
	testTable.deleteTag("家用电器");

	cout<<testTable.getOccupation()<<endl;
	cout<<testTable.toString()<<endl;

	testTable.addTag("食品");
	testTable.addTag("家用电器");
	testTable.addTag("家用电器","热水器");
	testTable.addTag("食品","肉类");
	testTable.addTag("肉类","鱼");
	testTable.addTag("日用品");
	testTable.addTag("日用品","雨伞");
	testTable.addTag("日用品","鞋");
	testTable.addTag("鞋","凉鞋");

	cout<<testTable.getOccupation()<<endl;
	cout<<testTable.toString()<<endl;
	system("pause");
	return 0;
}

