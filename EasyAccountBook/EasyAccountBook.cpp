// EasyAccountBook.cpp : �������̨Ӧ�ó������ڵ㡣
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
	testTable.addTag("ʳƷ");
	testTable.addTag("���õ���");
	testTable.addTag("���õ���","��ˮ��");
	testTable.addTag("ʳƷ","����");
	testTable.addTag("����","��");

	testTable.resizeHelper(testTable.findTag("����ǩ").get_tagHashFunction(16));
	system("pause");
	return 0;
}

