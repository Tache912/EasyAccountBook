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
	date date1 = date();
	date date2 = date(2012,12,21);
	date date3 = date(20140820);
	cout
	cout<< date3.toString() <<endl;
	system("pause");
	return 0;
}

