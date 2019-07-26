#include<iostream>
#include<iterator>
#include<set>
#include<algorithm>

using namespace std;


set<int>::const_iterator FindNearestElement(
	const set<int>& numbers,
	int border) {
	auto p = numbers.lower_bound(border);

	if (p == end(numbers)) {
		if (numbers.empty()) {
			return end(numbers);
		}
		else {
			return prev(p);
		}

	}
	else if (p == begin(numbers)) {
		return p;
	}
	else if(*p == border) {
		return p;	
	}
	else {
		if ((*p - border) < (border - *prev(p))) {
			return p;
		}
		else {
			return prev(p);
		}
	}

}


int main() {
	set<int> numbers = { 1, 4, 6 };
	cout <<
		*FindNearestElement(numbers, 0) << " " <<
		*FindNearestElement(numbers, 3) << " " <<
		*FindNearestElement(numbers, 5) << " " <<
		*FindNearestElement(numbers, 6) << " " <<
		*FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	return 0;
}