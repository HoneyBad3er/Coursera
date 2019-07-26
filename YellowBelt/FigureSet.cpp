#include<iostream>
#include<vector>
#include<sstream>
#include<cstdint>
#include<algorithm>
#include<numeric>
#include<iomanip>
#include<cmath>
#include<memory>
using namespace std;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() = 0;
	virtual double Area() = 0;
};

class Triangle : public Figure {
public:
	Triangle(const string& fname, const int fa, const int fb, const int fc) : name(fname), a(fa), b(fb), c(fc) {}

	string Name() const override {
		return name;
	}

	double Perimeter() override {

		return a + b + c;
	}

	double Area() override {
		double p = Perimeter() / 2;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}

private:
	string name;
	int a, b, c;
};

class Rect : public Figure {
public:
	Rect(const string& fname, const int fa, const int fb) : name(fname), a(fa), b(fb) {}

	string Name() const override {
		return name;
	}

	double Perimeter() override {

		return 2 * (a + b);
	}

	double Area() override {
		return a * b;
	}

private:
	string name;
	int a, b;
};

class Circle : public Figure {
public:
	Circle(const string& fname, const int& r) : name(fname), radius(r) {}

	string Name() const override {
		return name;
	}

	double Perimeter() override {

		return 2 * 3.14*radius;
	}

	double Area() override {

		return 3.14*radius*radius;
	}

private:
	string name;
	int radius;
};


shared_ptr<Figure> CreateFigure(istringstream& is) {
	string figure_name;
	is >> figure_name;
	if (figure_name == "TRIANGLE") {
		string a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(figure_name, stoi(a), stoi(b), stoi(c));
	}
	else if (figure_name == "RECT") {
		string a, b;
		is >> a >> b;
		return make_shared<Rect>(figure_name, stoi(a), stoi(b));
	}
	else {
		string num;
		is >> num;
		return make_shared<Circle>(figure_name, stoi(num));
	}
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}
