// EasyAccountBook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Tag.h"
#include "TagNode.h"
#include "TagTable.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	TagTable *testTable = new TagTable();
	testTable -> addTag("食品");
	testTable -> addTag("食品","肉类");
	testTable -> addTag("肉类","鱼肉");
	testTable -> addTag("肉类","猪肉");
	testTable -> addTag("鱼肉","龙利柳");
	testTable -> addTag("猪肉","排骨");
	testTable -> addTag("食品","蔬菜");
	testTable -> addTag("蔬菜","叶菜");
	testTable -> addTag("叶菜","生菜");
	testTable -> addTag("蔬菜","瓜");
	testTable -> addTag("瓜","黄瓜");
	testTable -> addTag("食品","水果");
	testTable -> addTag("水果","西瓜");
	testTable -> addTag("超市");
	testTable -> addTag("超市","肉类");

	cout<<testTable -> tagBelongTo("超市","生菜")<<endl;

	
	system("pause");
	return 0;
}

