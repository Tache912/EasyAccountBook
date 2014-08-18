#include "stdafx.h"
using namespace std;

class account;
class accountBook
{
	vector<account*>	incomeAccounts;
	vector<account*>	expenditureAccounts;
	string						accountBookName;
};
