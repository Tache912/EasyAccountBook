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
	int a = 1;
	int *pa = &a;
	int *pb;
	pb = pa;
	pa = nullptr;
	cout<< *pb;
	TagTable testTable = TagTable(16);
	testTable.addTag("食品");
	testTable.addTag("家用电器");
	testTable.addTag("家用电器","热水器");
	testTable.addTag("食品","肉类");
	testTable.addTag("肉类","鱼");

	testTable.resizeHelper(testTable.findTag("根标签").get_tagHashFunction(16));
	system("pause");
	return 0;
}

