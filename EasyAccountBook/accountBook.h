#include "stdafx.h"
#include "TagTable.h"
#include "account.h"
using namespace std;

class accountBook
{
	double				totalIncome;
	double				totalExpenditure;
	Linklist<account>	incomeAccounts;
	Linklist<account>	expenditureAccounts;
	Linklist<account>	tempAccountsList;
	TagTable			bookTags;
	string				accountBookName;
};
