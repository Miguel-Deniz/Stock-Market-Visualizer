#include "Calendar.h"

// Time Class

Time::Time()
{
	updateTime();
}

int Time::getSec() const
{
	if (_localTime == NULL)
		return 0;
	else
		return _localTime->tm_sec;
}

int Time::getMin() const
{
	if (_localTime == NULL)
		return 0;
	else
		return _localTime->tm_min;
}

int Time::getHour() const
{
	if (_localTime == NULL)
		return 0;
	else
		return _localTime->tm_hour;
}

int Time::getDay() const
{
	if (_localTime == NULL)
		return 0;
	else
		return _localTime->tm_mday;
}

int Time::getMon() const
{
	if (_localTime == NULL)
		return 0;
	else
		return _localTime->tm_mon + 1;
}

int Time::getYear() const
{
	if (_localTime == NULL)
		return 0;
	else
		return _localTime->tm_year + 1900;
}

tm* Time::getCurrentTm() const
{
	// Reterieve current date/time in system in seconds
	time_t now = time(0);

	return localtime(&now);
}

void Time::updateTime()
{
	_localTime = getCurrentTm();
}

ostream& operator<<(ostream& out, const Time& time)
{
	// Format: MM/DD/YYYY HOUR:MINUTE:SECOND
	out << time.getMon() << "/" <<
		time.getDay() << "/" <<
		time.getYear() << " " <<
		setw(2) << setfill('0') << time.getHour() << ":" <<
		setw(2) << setfill('0') << time.getMin() << ":" <<
		setw(2) << setfill('0') << time.getSec();

	return out;
}

//----------------------------------------------------------

Date::Date()
{
	_time.updateTime();
	updateDate();
}

Date::Date(int month, int day, int year)
{
	_time.updateTime();
	if (!setDate(month, day, year))
	{
		cout << "invalid date " << endl;
		resetDate();
	}
}

void Date::resetDate()
{
	_month = MIN_MONTH;
	_day = MIN_DAY;
	_year = MIN_YEAR;
}

void Date::updateDate()
{
	_time.updateTime();

	setDay(_time.getDay());
	setMonth(_time.getMon());
	setYear(_time.getYear());
}

int Date::setDate(int month, int day, int year)
{
	if (isValidDate(month, day, year))
	{
		setMonth(month);
		setDay(day);
		setYear(year);
		return 1;
	}

	return 0;
}

void Date::setMonth(int month)
{
	_month = month;
}

void Date::setDay(int day)
{
	_day = day;
}

void Date::setYear(int year)
{
	_year = year;
}

string Date::getTime()
{
	return intToStr(_month) + "/" + intToStr(_day) + "/" + intToStr(_year);
}

int Date::getMonth() const
{
	return _month;
}

int Date::getDay() const
{
	return _day;
}

int Date::getYear() const
{
	return _year;
}

int Date::getDaysInYear(int year) const
{
	if ((year))
		return 364;
	else
		return 365;
}

int Date::dateToInt()
{
	return _year * 10000 + _month * 100 + _day;
}

int Date::isLeapYear(int year) const
{
	return (year % 4) || ((year % 100 == 0) && (year % 400)) ? 0 : 1;
}

int Date::isValidDate(int month, int day, int year)
{
	bool valid = true;

	if (year < MIN_YEAR || year > MAX_YEAR) valid = false;
	if (month < MIN_MONTH || month > MAX_MONTH) valid = false;
	if (day < MIN_DAY || day > maxDay(month, year)) valid = false;

	return valid;
}

int Date::maxDay(int month, int year) const
{
	return 31 - ((month == 2) ? (3 - isLeapYear(year)) : ((month - 1) % 7 % 2));
}

int Date::getDateAsInt() const
{
	int dayCount = 0;

	for (int year = 0; year < _year; ++year)
		dayCount += getDaysInYear(year);

	for (int month = 1; month < _month; ++month)
		dayCount += maxDay(month, _year);

	dayCount += _day;

	return dayCount;

}

bool operator>  (Date &date1, Date &date2)
{
	return (date1.dateToInt() > date2.dateToInt());
}

bool operator<= (Date &date1, Date &date2)
{
	return (date1.dateToInt() <= date2.dateToInt());
}

bool operator<  (Date &date1, Date &date2)
{
	return (date1.dateToInt() < date2.dateToInt());
}

bool operator>= (Date &date1, Date &date2)
{
	return (date1.dateToInt() >= date2.dateToInt());
}

bool operator== (Date &date1, Date &date2)
{
	return (date1.getTime() == date2.getTime());
}

istream& operator>>(istream& in, Date& date)
{
	int month, day, year;
	char ch1, ch2;

	in >> month >> ch1 >> day >> ch2 >> year;

	date.setDate(month, day, year);

	return in;
}

ostream& operator<<(ostream& out, const Date& date)
{
	out << date._month << "/" << date._day << "/" << date._year;
	return out;
}