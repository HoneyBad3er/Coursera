#include<iostream>
#include<cstdint>
#include<vector>
using namespace std;

int main() {
	uint64_t N;
	uint64_t R;

	cin >> N >> R;
	uint64_t v = 0;
	for (uint64_t i = 0; i < N; ++i) {
		uint64_t w, h, d;
		cin >> w >> h >> d;
		v += w*h*d;
	}
	uint64_t mass = v * R;
	cout << mass << endl;
	return 0;
}


