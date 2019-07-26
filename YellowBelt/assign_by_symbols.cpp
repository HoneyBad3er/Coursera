#include<iostream>
#include<iterator>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdint>

using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	const string& prefix) {

	auto it1 = lower_bound(range_begin, range_end, prefix,
		[](const string& s, string value) {
		int n = value.size();
		return s.substr(0, n) < value;
	}
	);

	auto it2 = upper_bound(range_begin, range_end, prefix,
		[](string value, const string& s) {
		int n = value.size();
		return s.substr(0, n) > value;
	}
	);

	return { it1, it2 };
}


int main() {
	const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

	const auto mo_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto mt_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	cout << (mt_result.first - begin(sorted_strings)) << " " <<
		(mt_result.second - begin(sorted_strings)) << endl;

	const auto na_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	cout << (na_result.first - begin(sorted_strings)) << " " <<
		(na_result.second - begin(sorted_strings)) << endl;

	return 0;
}
