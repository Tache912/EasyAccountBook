// EasyAccountBook.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Tag.h"
#include "TagNode.h"
#include "TagTable.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	TagTable *testTable = new TagTable();
	testTable -> addTag("ʳƷ");
	testTable -> addTag("ʳƷ","����");
	testTable -> addTag("����","����");
	testTable -> addTag("����","����");
	testTable -> addTag("����","������");
	testTable -> addTag("����","�Ź�");
	testTable -> addTag("ʳƷ","�߲�");
	testTable -> addTag("�߲�","Ҷ��");
	testTable -> addTag("Ҷ��","����");
	testTable -> addTag("�߲�","��");
	testTable -> addTag("��","�ƹ�");
	testTable -> addTag("ʳƷ","ˮ��");
	testTable -> addTag("ˮ��","����");
	testTable -> addTag("����");
	testTable -> addTag("����","����");

	cout<<testTable -> tagBelongTo("����","����")<<endl;

	
	system("pause");
	return 0;
}

