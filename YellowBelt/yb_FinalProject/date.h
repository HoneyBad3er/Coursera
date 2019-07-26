#pragma once
#include<sstream>
#include<string>
#include<iostream>
#include<cstdint>
#include<iomanip>
using namespace std;

class Date {
public:
	Date(const int& year, const int& month, const int& day);

	int GetYear() const;

	int GetMonth() const;

	int GetDay() const;

private:
	const int _day;
	const int _month;
	const int _year;

};

Date ParseDate(istream& stream);

ostream& operator<< (ostream& out, const Date& date);


bool operator< (const Date& lhs_date, const Date& rhs_date);

bool operator> (const Date& lhs_date, const Date& rhs_date);

bool operator== (const Date& lhs_date, const Date& rhs_date);

bool operator<= (const Date& lhs_date, const Date& rhs_date);

bool operator>= (const Date& lhs_date, const Date& rhs_date);

bool operator!= (const Date& lhs_date, const Date& rhs_date);


