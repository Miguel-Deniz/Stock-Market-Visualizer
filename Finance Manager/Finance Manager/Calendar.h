#ifndef CALENDAR_H
#define CALENDAR_H

/*
	Author: Miguel Deniz Lopez
	Date:	7/10/16 6:31 PM

	class Time
	class Date
*/

#include "SLF.h"

class Time
{
public:
	// Initializes the time with the current system time
	Time();

	// Accessors
	// Returns the seconds after the minute - [0, 60] including leap second
	int getSec() const;

	// Returns the minutes after the hour - [0, 59]
	int getMin() const;

	// Returns the hours since midnight - [0, 23]
	int getHour() const;

	// Returns the day of the month - [1, 31]
	int getDay() const;

	// Returns the month of the year - [1, 12]
	int getMon() const;

	// Returns the year
	int getYear() const;

	// Updates time to current system time
	void updateTime();
private:
	tm* _localTime;

	// Returns a tm* of the current system times
	tm* getCurrentTm() const;

	friend ostream& operator<<(ostream& out, const Time& time);
};

ostream& operator<<(ostream& out, const Time& time);

//----------------------------------------------------------

class Date
{
	// Constants
	const int MIN_DAY = 1;
	// No MAX_DAY, use maxDay(int month, int year)

	const int MIN_MONTH = 1;
	const int MAX_MONTH = 12;

	const int MIN_YEAR = 1970;
	const int MAX_YEAR = 2016;

	int _month;
	int _day;
	int _year;

	/* Used to obtain the current time */
	Time _time;
	time_t _rawtime;
	struct tm* _now;

	/*	Sets the date to default values 1/1/1990 */
	void resetDate();

	// Returns 1 if the given year is a leapyear, 0 otherwise.
	int isLeapYear(int year) const;

	int isValidDate(int month, int day, int year);

	// Returns the number of the days in the given month of the year
	int maxDay(int month, int year) const;

	/* Converts the current stored date to an integer
	Format: YYYYMMDD ex. 19900101 is 1/1/1990 */
	int dateToInt();

	/*	Comparison operator, date1 relative to date2

	Parameters:
	Date& date1, first date
	Date& date2, second date
	Returns:
	A bool value depending if the operation is true or false. */
	friend bool operator>  (Date &date1, Date &date2);
	friend bool operator<= (Date &date1, Date &date2);
	friend bool operator<  (Date &date1, Date &date2);
	friend bool operator>= (Date &date1, Date &date2);
	friend bool operator== (Date &date1, Date &date2);
public:
	/*	Sets the date equal to the current date. See Date::updateDate()

	Parameters:
		VOID
	Returns:
		VOID */
	Date();

	/*	Sets the date equal to the given date.
		If invalid/unsuccessful, the date will be reset. see Date::resetDate()

	Parameters:
		unsigned int month [1-12]
		unsigned int day   [1-28/29/30/31]
		unsigned int year  [1990-2020]
	Returns:
		VOID */
	Date(int month, int day, int year);

	/*	Sets the date equal to the current date.

		Parameters:
			VOID
		Returns:
			VOID */
	void updateDate();

	/*	Returns a string of the date in the format MM/DD/YYYY

		Parameters:
			VOID
		Returns:
			A string of the date */
	string getTime();

	// Accessor methods
	// Returns the current month of the date
	int getMonth() const;
	// Returns the current day of the date
	int getDay() const;
	// Returns the current year of the date
	int getYear() const;

	int getDaysInYear(int year) const;

	// Returns the day count from from year 0.
	int getDateAsInt() const;

	/*	Sets the date to the given date: month,day,year
	If the date is invalid, the date will not be changed

	Returns 0 if unsuccessful and 1 if succeeded. */
	int setDate(int month, int day, int year);

	/*	Sets the month the the given month. If the new date is
	invalid, the date will not be changed.

	Returns 0 if unsuccessful, and 1 if succeeded. */
	void setMonth(int month);

	/*	Sets the day to the given day. If the new date is invalid,
	the date will not be changed.

	Returns 0 if unsuccessful, and 1 if succeeded. */
	void setDay(int day);

	/*	Sets the year to the given year. If the new date is
	invalid, the date will not be changed.

	Returns 0 if unsuccessful, and 1 if succeeded. */
	void setYear(int year);

	friend istream& operator>>(istream& in, Date& symbol);
	friend ostream& operator<<(ostream& out, const Date& date);
};

istream& operator>>(istream& in, Date& symbol);
ostream& operator<<(ostream& out, const Date& date);

#endif