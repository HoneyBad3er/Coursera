#include<iostream>
#include<string>
#include<deque>
#include<cstdint>
using namespace std;

class Arifm_Compr {
public:
	Arifm_Compr(int a) {
		compr.push_back(to_string(a));
	}
	void Give_skb() {
		compr.push_front("(");
		compr.push_back(")");
	}

	void Plus(int a) {
		first = false;
		compr.push_back(" + ");
		compr.push_back(to_string(a));
	}

	void Minus(int a) {
		first = false;
		compr.push_back(" - ");
		compr.push_back(to_string(a));
	}

	void Multiply(int a) {
		if (!first) {
			if (*(compr.end() - 2) == " + " || *(compr.end() - 2) == " - ") {
				Give_skb();
			}
		}
		compr.push_back(" * ");
		compr.push_back(to_string(a));
	}

	void Divivsion(int a) {
		if (!first) {
			if (*(compr.end() - 2) == " + " || *(compr.end() - 2) == " - ") {
				Give_skb();
			}
		}
		compr.push_back(" / ");
		compr.push_back(to_string(a));
	}

	string Get_compr() {
		string s;
		for (auto it = begin(compr); it < end(compr); ++it)
		{
			s += *it;
		}
		return s;
	}

private:
	deque<string> compr;
	bool first = true;
};

int main() {
	int a, n;
	cin >> a;
	cin >> n;
	Arifm_Compr compr(a);
	for (int i = 0; i < n; ++i) {
		char operation;
		int num;
		cin >> operation;
		cin >> num;
		switch (operation) {

		case '+':
			compr.Plus(num);
			break;
		case '-':
			compr.Minus(num);
			break;
		case '*':
			compr.Multiply(num);
			break;
		case '/':
			compr.Divivsion(num);
			break;
		default:
			break;
		}

	}

	cout << compr.Get_compr();

}