#include "stdafx.h"
#include "TagTable.h"
#include "account.h"
using namespace std;

class accountBook
{
private:
	double				totalIncome;
	double				totalExpenditure;
	double				totalTemp;

	unsigned int		incomeIdKeyCounter;
	unsigned int		expenditureIdKeyCounter;

	Linklist<account>	incomeAccounts;
	Linklist<account>	expenditureAccounts;
	Linklist<account>	tempAccountsList;
	TagTable			bookTags;
	string				accountBookName;
public:
	accountBook();
	accountBook(string bookName_in);

	bool			addIncome(account &account_in);
	bool			addExpenditure(account &account_in);
	bool			delIncome(unsigned int idKey_in);
	bool			delExpenditure(unsigned int idKey_in);

	//If idKey not found, it returns a default account() object,which idKey == -1
	const account	&findIncome(unsigned int idKey_in);

	//If idKey not found, it returns a default account() object,which idKey == -1
	const account	&findExpenditure(unsigned int idKey_in);

	double			getTotalIncome();
	double			getTotalExpenditure();

	unsigned int	getIncomeIdKeyCounter();
	unsigned int	getExpenditureIdKeyCounter();

	//listID = 0, 1, 2(0 = income, 1 = expenditure, 2 = temp)
	string			ListToString(unsigned int listID);

	void			resetTempAccountsList();

	TagTable		&getTagTable();
	void			setBookName(string bookName_in);
	const string	&getBookName();

	//TODO：排序与统计函数

};
