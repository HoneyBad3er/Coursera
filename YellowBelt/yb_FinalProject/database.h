#pragma once
#include<vector>
#include<set>
#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<iterator>
#include<algorithm>
#include<utility>
#include"date.h"
using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	void Print(ostream& out) const;

	template <typename Func>
	int RemoveIf(Func f) {
		int count = 0;
		map<const Date, vector<string>> storage_c = storage;
		for (auto d : storage_c) {
			vector<string> events = d.second;
			auto it1 = stable_partition(events.begin(),
				events.end(), [f, d](const string& s)
			{return !f(d.first, s);});

				count += events.end() - it1;

				events.erase(it1, end(events));
				if (events.size() == 0) {
					storage.erase(d.first);
					set_storage.erase(d.first);
				}
				else {
					storage[d.first] = events;
					set_storage[d.first] = set<string>(events.begin(), events.end());
				}
		}
		return count;
	}

	template <typename Func>
	vector<pair<const Date, string>> FindIf(Func f) const {
		vector<pair<const Date, string>> founded;
		for (auto it = storage.begin(); it != storage.end(); ++it) {
			for (auto event_it = begin(it->second); event_it != end(it->second); ++event_it) {
				if (f(it->first, *event_it)) {
					founded.push_back(make_pair(it->first, *event_it));
				}
			}

		}
		return founded;
	}

	pair<const Date, string> Last(const Date& date) const ;

private:
	map<const Date, vector<string>> storage;
	map<const Date, set<string>> set_storage;

};

ostream& operator<<(ostream& stream, pair<Date, string> p);