#include "test_runner.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include <iterator>
#include <utility>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    size_t size = distance(range_begin, range_end);
    if ( size < 2){
        return;
    }

    vector<typename RandomIt::value_type> range(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto first_border = range.begin() + size / 3 ;
    auto second_border = first_border + size / 3;
    MergeSort(range.begin(),first_border);
    MergeSort(first_border, second_border);
    MergeSort(second_border, range.end());
    vector<typename RandomIt::value_type> tmp;
    merge(make_move_iterator(range.begin()), make_move_iterator(first_border),make_move_iterator(first_border),make_move_iterator(second_border), back_inserter(tmp));
    merge(make_move_iterator(tmp.begin()), make_move_iterator(tmp.end()), make_move_iterator(second_border),make_move_iterator(range.end()), range_begin );
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  /*for (auto it = begin(numbers); it != end(numbers); ++it){
      cout << *it << "  ";
  }
  cout << "\n";*/
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
