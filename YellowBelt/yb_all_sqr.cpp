#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<string>
using namespace std;

template <typename T> T Sqr(const T& num);
template <typename T1> vector<T1> Sqr(vector<T1> v);
template <typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> m);
template <typename First, typename Second> pair<First, Second> Sqr(pair<First, Second> p);

template <typename T>
T Sqr(const T& num){
	return num* num;
}

template <typename T1>
vector<T1> Sqr(vector<T1> v){
	for (T1& i : v){
		i = Sqr(i);
	}
	return v;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> m){
	for (auto& item : m){
		item.second = Sqr(item.second);
	}
	return m;
}

template <typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> p){
	return make_pair(Sqr(p.first), Sqr(p.second));
}


int main(){
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}
