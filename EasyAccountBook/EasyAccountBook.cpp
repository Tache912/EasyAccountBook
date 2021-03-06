// EasyAccountBook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TagTable.h"
#include "accountBook.h"


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	accountBook testBook = accountBook("测试账本");
	testBook.getTagTable().addTag("食品");
	testBook.getTagTable().addTag("家用电器");
	testBook.getTagTable().addTag("食品","肉类");
	testBook.getTagTable().addTag("肉类","猪肉");
	testBook.getTagTable().addTag("猪肉","瘦肉");
	testBook.getTagTable().addTag("猪肉","排骨");
	testBook.getTagTable().addTag("家用电器","热水器");
	testBook.addExpenditure(account(testBook.getExpenditureIdKeyCounter(),date(),111.123));
	testBook.addExpenditure(account(testBook.getExpenditureIdKeyCounter(),date(2014,8,25),222.345));
	testBook.addExpenditure(account(testBook.getExpenditureIdKeyCounter(),date(20140826),441.567));
	cout<< testBook.ListToString(1) <<endl;
	cout<< testBook.getTagTable().toString()<<endl;
	system("pause");
	return 0;
}

