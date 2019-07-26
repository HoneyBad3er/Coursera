#include "database.h"

void Database::Add(const Date& date, const string& event) {

	if (set_storage.count(date) != 0) {
		if (set_storage[date].find(event) == set_storage[date].end() ) {
			storage[date].push_back(event);
			set_storage[date].insert(event);
		}
	}
	else {
		storage[date].push_back(event);
		set_storage[date].insert(event);
	}
}

void Database::Print(ostream& out) const {
	for (auto it = begin(storage); it != end(storage); ++it) {
		for (auto event : it->second) {
			out << it->first << " " << event << endl;
		}
	}
}

pair<const Date, string> Database::Last(const Date& date) const {
	auto it = storage.upper_bound(date);
	if (it == storage.begin()) {
		throw invalid_argument("No entries");
	}
	--it;
	auto val_it = (it->second).end();
	--val_it;

	return make_pair(it->first, *val_it);
}

ostream& operator<<(ostream& stream, pair<Date, string> p) {
	stream << p.first << " " << p.second;
	return stream;
}