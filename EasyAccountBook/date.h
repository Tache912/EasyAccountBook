using namespace std;

class date
{
private:
	int year;
	int mon;
	int day;
	int weekday;
public:
	date();
	date(int year_in, int mon_in, int day_in);
	date(int int_date_in);
	date(date &date_in,bool add_or_minus);
	int getYear() const;
	int getMonth() const;
	int getDay() const;

	int getYear();
	int getMonth();
	int getDay();
	int getWeekday();
	string toString();
	static int getWeekdayfromYMD(int year_in, int mon_in, int day_in);
	bool setDate(int year_in, int mon_in, int day_in);

	bool operator>(const date &date_right);
	bool operator<(const date &date_right);
	bool operator==(const date &date_right);
	bool operator!=(const date &date_right);
};
