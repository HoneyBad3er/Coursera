#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};


template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
		begin(range_copy), middle, end(range_copy),
		[](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
	}
	);
	return middle->age;
}

void PrintStats(vector<Person> persons) {

	cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;;
	auto female_it = partition(begin(persons), end(persons), 
		[](Person person) { if (person.gender == Gender::FEMALE) { return true; } else { return false; }});
	cout << "Median age for females = " << ComputeMedianAge(begin(persons), female_it) << endl;
	cout << "Median age for males = " << ComputeMedianAge(female_it, end(persons) ) << endl;
	auto female_it2 = partition(begin(persons), female_it,
		[](Person person) { if (person.gender == Gender::FEMALE && person.is_employed == true) { return true; } else { return false; }});
	cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), female_it2) << endl;
	cout << "Median age for unemployed females = " << ComputeMedianAge(female_it2, female_it) << endl;
	auto male_it = partition(female_it, end(persons),
		[](Person person) { if (person.gender == Gender::MALE && person.is_employed == true) { return true; } else { return false; }});
	cout << "Median age for employed males = " << ComputeMedianAge(female_it, male_it) << endl;
	cout << "Median age for unemployed males = " << ComputeMedianAge(male_it, end(persons)) << endl;
}
int main() {
	vector<Person> persons = {
		{31, Gender::MALE, false},
		{40, Gender::FEMALE, true},
		{24, Gender::MALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
}
