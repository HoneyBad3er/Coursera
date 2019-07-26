#include "date.h"

Date::Date(const int& year, const int& month, const int& day) : _day(day), _month(month), _year(year) {}

int Date::GetYear() const {
	return _year;
}
int Date::GetMonth() const {
	return _month;
}
int Date::GetDay() const {
	return _day;
}

ostream& operator<< (ostream& out, const Date& date) {
	out << setfill('0');
	out << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
	return out;
}

bool operator== (const Date& lhs_date, const Date& rhs_date) {
	if ((lhs_date.GetYear() == rhs_date.GetYear()) && 
		(lhs_date.GetMonth() == rhs_date.GetMonth()) && 
		(lhs_date.GetDay() == rhs_date.GetDay())) {
		return true;
	}
	else {
		return false;
	}

}

bool operator!= (const Date& lhs_date, const Date& rhs_date) {
	if (lhs_date == rhs_date) {
		return false;
	}
	else {
		return true;
	}

}

bool operator< (const Date& lhs_date, const Date& rhs_date) {
	if (lhs_date != rhs_date) {
		if (lhs_date.GetYear() - rhs_date.GetYear() < 0) {
			return true;
		}
		else if (lhs_date.GetYear() - rhs_date.GetYear() > 0) {
			return false;
		}
		else if (lhs_date.GetMonth() - rhs_date.GetMonth() < 0) {
			return true;
		}
		else if (lhs_date.GetMonth() - rhs_date.GetMonth() > 0) {
			return false;
		}
		else if (lhs_date.GetDay() - rhs_date.GetDay() < 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

bool operator> (const Date& lhs_date, const Date& rhs_date) {
	if (lhs_date != rhs_date && !(lhs_date < rhs_date)) {
		return true;
	}
	else {
		return false;
	}

}


bool operator<= (const Date& lhs_date, const Date& rhs_date) {
	if (lhs_date < rhs_date || lhs_date == rhs_date) {
		return true;
	}
	else {
		return false;
	}

}


bool operator>= (const Date& lhs_date, const Date& rhs_date) {
	if (lhs_date > rhs_date || lhs_date == rhs_date) {
		return true;
	}
	else {
		return false;
	}

}


Date ParseDate(istream& stream) {
	int year = 0;
	int month = 0;
	int day = 0;

	stream >> year;

	if (stream.peek() != '-') {
		string ex = "Wrong date format: ";
		throw runtime_error(ex);
	}

	stream.ignore(1);
	stream >> month;
	if (stream.peek() != '-') {
		string ex = "Wrong date format: ";
		throw runtime_error(ex);
	}
	stream.ignore(1);
	stream >> day;

	if (month > 12 || month <= 0) {
		throw invalid_argument("Month value is invalid: " + to_string(month));
	}
	else if (day <= 0 || day > 31) {
		throw invalid_argument("Day value is invalid: " + to_string(day));
	}

	Date date(year, month, day);

	return date;
}