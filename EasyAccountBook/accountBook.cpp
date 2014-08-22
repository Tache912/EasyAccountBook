#include "stdafx.h"
#include "accountBook.h"

accountBook::accountBook()
{
	totalIncome = 0;
	totalExpenditure = 0;
	incomeIdKeyCounter = 0;
	expenditureIdKeyCounter = 0;

	incomeAccounts = Linklist<account>();
	expenditureAccounts = Linklist<account>();
	tempAccountsList = Linklist<account>();
	bookTags = TagTable();
	accountBookName = "默认账本";
}

accountBook::accountBook(string bookName_in)
{
	totalIncome = 0;
	totalExpenditure = 0;
	incomeIdKeyCounter = 0;
	expenditureIdKeyCounter = 0;

	incomeAccounts = Linklist<account>();
	expenditureAccounts = Linklist<account>();
	tempAccountsList = Linklist<account>();
	bookTags = TagTable();
	accountBookName = bookName_in;
}

bool accountBook::addIncome(account &account_in)
{
	if(account_in.getIdKey() == -1)
	{
		return false;
	}
	else
	{
		totalIncome += account_in.getMoney();
		incomeAccounts.addNode(account_in);
		incomeIdKeyCounter ++;
		return true;
	}
}

bool accountBook::addExpenditure(account &account_in)
{
	if(account_in.getIdKey() == -1)
	{
		return false;
	}
	else
	{
		totalExpenditure += account_in.getMoney();
		expenditureAccounts.addNode(account_in);
		expenditureIdKeyCounter ++;
		return true;
	}
}

bool accountBook::delIncome(unsigned int idKey_in)
{
	incomeAccounts.resetCurrentNode();
	Node<account> *currentNode = incomeAccounts.getNextCurrentNode();
	while(currentNode != nullptr)
	{
		if(currentNode -> object -> getIdKey() == idKey_in)
		{
			totalIncome -= currentNode -> object -> getMoney();
			delete currentNode;
			incomeAccounts.resetCurrentNode();
			return true;
		}
		currentNode = incomeAccounts.getNextCurrentNode();
	}
	incomeAccounts.resetCurrentNode();
	return false;
}

bool accountBook::delExpenditure(unsigned int idKey_in)
{
	expenditureAccounts.resetCurrentNode();
	Node<account> *currentNode = expenditureAccounts.getNextCurrentNode();
	while(currentNode != nullptr)
	{
		if(currentNode -> object -> getIdKey() == idKey_in)
		{
			totalExpenditure -= currentNode -> object -> getMoney();
			delete currentNode;
			expenditureAccounts.resetCurrentNode();
			return true;
		}
		currentNode = expenditureAccounts.getNextCurrentNode();
	}
	expenditureAccounts.resetCurrentNode();
	return false;
}

const account &accountBook::findIncome(unsigned int idKey_in)
{
	incomeAccounts.resetCurrentNode();
	Node<account> *currentNode = incomeAccounts.getNextCurrentNode();
	while(currentNode != nullptr)
	{
		if(currentNode -> object -> getIdKey() == idKey_in)
		{
			account &output = *(currentNode -> object);
			incomeAccounts.resetCurrentNode();
			return output;
		}
		currentNode = incomeAccounts.getNextCurrentNode();
	}
	incomeAccounts.resetCurrentNode();
	return account();
}

const account &accountBook::findIncome(unsigned int idKey_in)
{
	expenditureAccounts.resetCurrentNode();
	Node<account> *currentNode = expenditureAccounts.getNextCurrentNode();
	while(currentNode != nullptr)
	{
		if(currentNode -> object -> getIdKey() == idKey_in)
		{
			account &output = *(currentNode -> object);
			expenditureAccounts.resetCurrentNode();
			return output;
		}
		currentNode = expenditureAccounts.getNextCurrentNode();
	}
	expenditureAccounts.resetCurrentNode();
	return account();
}

double accountBook::getTotalIncome()
{
	return totalIncome;
}

double accountBook::getTotalExpenditure()
{
	return totalExpenditure;
}

unsigned int accountBook::getIncomeIdKeyCounter()
{
	return incomeIdKeyCounter;
}

unsigned int accountBook::getExpenditureIdKeyCounter()
{
	return expenditureIdKeyCounter;
}
string accountBook::ListToString(unsigned int listID)
{
	Linklist<account> *outputList;
	switch(listID)
	{
	case 0:
		outputList = &incomeAccounts;
		break;
	case 1:
		outputList = &expenditureAccounts;
		break;
	case 2:
		outputList = &tempAccountsList;
		break;
	default:
		return "不支持的listID";
	}
	(*outputList).resetCurrentNode();
	Node<account> *currentNode = (*outputList).getNextCurrentNode();
	string output;
	while(currentNode -> nextNode != nullptr)
	{
		output += currentNode -> object -> toString() + "\n";
		currentNode = (*outputList).getNextCurrentNode();
	}
	output += currentNode -> object -> toString();
	(*outputList).resetCurrentNode();
	return output;
}
void accountBook::resetTempAccountsList()
{
	totalTemp = 0;
	tempAccountsList.delList();
}

TagTable &accountBook::getTagTable()
{
	return bookTags;
}

void accountBook::setBookName(string bookName_in)
{
	accountBookName = bookName_in;
}

const string &accountBook::getBookName()
{
	return accountBookName;
}