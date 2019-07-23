#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y)	out << (x) << "\n" << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;

    if (true)
    PRINT_VALUES(output, 5, "red belt");
    else
    cout << 2 << endl;

    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");
}
