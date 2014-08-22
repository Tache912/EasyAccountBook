#include "stdafx.h"


using namespace std;
bool check_day(int year_in, int mon_in, int day_in);
date::date()
{
	time_t now_time;
	struct tm pt ;
	time(&now_time);
	localtime_s(&pt,&now_time);
	
	year	=	pt.tm_year+1900;
	mon		=	pt.tm_mon+1;
	day		=	pt.tm_mday;
	weekday	=	pt.tm_wday;//0=sunday,1=monday,...,6=saturday
}

date::date(int year_in, int mon_in, int day_in)
{
	if(!check_day(year_in, mon_in, day_in))
	{
		year	=	-1;
		mon		=	-1;
		day		=	-1;
		weekday	=	-1;
	}
	else
	{
		year	=	year_in;
		mon		=	mon_in;
		day		=	day_in;
		weekday	=	getWeekdayfromYMD(year_in, mon_in, day_in);
	}
}
date::date(int int_date_in)//yyyymmdd
{
	int year_in		=	int_date_in / 10000;
	int mon_in	=	(int_date_in - year_in * 10000)/100;
	int day_in		=	(int_date_in - year_in * 10000) - mon_in * 100;

	if(!check_day(year_in, mon_in, day_in))
	{
		year	=	-1;
		mon		=	-1;
		day		=	-1;
		weekday	=	-1;
	}
	else
	{
		year	=	year_in;
		mon		=	mon_in;
		day		=	day_in;
		weekday	=	getWeekdayfromYMD(year_in, mon_in, day_in);
	}

}
date::date(date &date_in,bool add_or_minus)
{
	int year_in	=	date_in.getYear();
	int mon_in	=	date_in.getMonth();
	int day_in	=	date_in.getDay();
	if(!check_day(year_in, mon_in, day_in))
	{
		year	=	-1;
		mon		=	-1;
		day		=	-1;
		weekday	=	-1;
	}
	else
	{ 
		if ( add_or_minus == true )//true is add
		{
			if( ( year_in % 4 == 0 && year_in % 100 != 0 ) || year_in % 400 == 0 )
			{
				if( mon_in == 2 && day_in == 28 )
				{
					year	=	year_in;
					mon		=	3;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( (mon_in == 4 || mon_in == 6 || mon_in == 9 || mon_in == 11) && day_in == 30 )
				{
					year	=	year_in;
					mon		=	mon_in + 1;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( mon_in == 12 && day_in == 31 )
				{
					year	=	year_in + 1;
					mon		=	1;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if(day_in == 31)
				{
					year	=	year_in;
					mon		=	mon_in + 1;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else
				{
					year	=	year_in;
					mon		=	mon_in;
					day		=	day_in + 1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
			}
			else
			{
				if( mon_in == 2 && day_in == 29 )
				{
					year	=	year_in;
					mon		=	3;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( (mon_in == 4 || mon_in == 6 || mon_in == 9 || mon_in == 11) && day_in == 30 )
				{
					year	=	year_in;
					mon		=	mon_in + 1;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( mon_in == 12 && day_in == 31 )
				{
					year	=	year_in + 1;
					mon		=	1;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if(day_in == 31)
				{
					year	=	year_in;
					mon		=	mon_in + 1;
					day		=	1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else
				{
					year	=	year_in;
					mon		=	mon_in;
					day		=	day_in + 1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
			}
		}
		else//false is minus
		{
			if( ( year_in % 4 == 0 && year_in % 100 != 0 ) || year_in % 400 == 0 )
			{
				if( mon_in == 3 && day_in == 1 )
				{
					year	=	year_in;
					mon		=	2;
					day		=	28;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( (mon_in == 5 || mon_in == 7 || mon_in == 10 || mon_in == 12) && day_in == 1 )
				{
					year	=	year_in;
					mon		=	mon_in - 1;
					day		=	30;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( mon_in == 1 && day_in == 1 )
				{
					year	=	year_in - 1;
					mon		=	12;
					day		=	31;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if(day_in == 1)
				{
					year	=	year_in;
					mon		=	mon_in - 1;
					day		=	31;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else
				{
					year	=	year_in;
					mon		=	mon_in;
					day		=	day_in - 1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
			}
			else
			{
				if( mon_in == 3 && day_in == 1 )
				{
					year	=	year_in;
					mon		=	2;
					day		=	29;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( (mon_in == 5 || mon_in == 7 || mon_in == 10 || mon_in == 12) && day_in == 1 )
				{
					year	=	year_in;
					mon		=	mon_in - 1;
					day		=	30;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if( mon_in == 1 && day_in == 1 )
				{
					year	=	year_in - 1;
					mon		=	12;
					day		=	31;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else if(day_in == 1)
				{
					year	=	year_in;
					mon		=	mon_in - 1;
					day		=	31;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
				else
				{
					year	=	year_in;
					mon		=	mon_in;
					day		=	day_in - 1;
					weekday	=	getWeekdayfromYMD(year,mon,day);
				}
			}
		}
	}
}
bool date::setDate(int year_in, int mon_in, int day_in)
{
	if(!check_day(year_in, mon_in, day_in))
	{
		year	=	-1;
		mon		=	-1;
		day		=	-1;
		weekday	=	-1;
		return false;
	}
	else
	{
		year	=	year_in;
		mon		=	mon_in;
		day		=	day_in;
		weekday	=	getWeekdayfromYMD(year_in, mon_in, day_in);
		return true;
	}
}
int date::getYear() const 
{
	return year;
}
int date::getMonth() const 
{
	return mon;
}
int date::getDay() const 
{
	return day;
}

int date::getYear() 
{
	return year;
}
int date::getMonth() 
{
	return mon;
}
int date::getDay() 
{
	return day;
}
int date::getWeekday()
{
	return weekday;
}
string date::toString()
{
	stringstream ss;
	string weekname[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	ss<<year<<"/"<<mon<<"/"<<day<<"/"<<weekname[weekday];
	return ss.str();
}

bool date::operator>(const date &date_right)
{
	if( this->year > date_right.getYear())
	{
		return true;
	}
	else if(this->year == date_right.getYear() && this->mon > date_right.getMonth())
	{
		return true;
	}
	else if(this->year == date_right.getYear() && this->mon == date_right.getMonth() && this->day > date_right.getDay())
	{
		return true;
	}
	return false;
}
bool date::operator<(const date &date_right)
{
	if( this->year < date_right.getYear())
	{
		return true;
	}
	else if(this->year == date_right.getYear() && this->mon < date_right.getMonth())
	{
		return true;
	}
	else if(this->year == date_right.getYear() && this->mon == date_right.getMonth() && this->day < date_right.getDay())
	{
		return true;
	}
	return false;
}
bool date::operator==(const date &date_right)
{

	if(this->year == date_right.getYear() && this->mon == date_right.getMonth() && this->day == date_right.getDay())
	{
		return true;
	}
	return false;
}
bool date::operator!=(const date &date_right)
{

	if(this->year != date_right.getYear() || this->mon != date_right.getMonth() || this->day != date_right.getDay())
	{
		return true;
	}
	return false;
}

bool check_day(int year_in, int mon_in, int day_in)
{
	if( year_in < 1583 || mon_in < 1 || mon_in > 12 || day_in < 1 || day_in > 31 )
	{
		return false;
	}
	else if( ( year_in % 4 == 0 && year_in % 100 != 0 ) || year_in % 400 == 0 )
	{
		if( mon_in == 2 && day_in > 28 )
		{
			return false;
		}
		else if( (mon_in == 4 || mon_in == 6 || mon_in == 9 || mon_in == 11) && day_in > 30 )
		{
			return false;
		}
	}
	else
	{
		if( mon_in == 2 && day_in > 29 )
		{
			return false;
		}
		else if( (mon_in == 4 || mon_in == 6 || mon_in == 9 || mon_in == 11) && day_in > 30 )
		{
			return false;
		}
	}
	return true;
}

//蔡勒公式求星期数
int date::getWeekdayfromYMD(int year_in, int mon_in, int day_in)
{
	if(!check_day(year_in, mon_in, day_in))
	{
		return -1;
	}
	else
	{
		int m;
		int year_Z = year_in;
		if(mon_in == 1 || mon_in == 2)
		{
			m = mon_in + 12;
			year_Z --;
		}
		else
		{
			m = mon_in;
		}
		int c	=	year_Z / 100;
		int y	=	year_Z - c * 100;
		int d	=	day_in;
		int w	=	( y + y/4 + c/4 - 2*c + (26 * ( m + 1 ))/10 + d - 1 ) % 7;
		if( w < 0 )
		{
			w = ( w % 7 + 7 ) % 7; 
		}
		return w;
	}
}