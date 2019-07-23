#include "test_runner.h"
#include "profile.h"
#include <string_view>
#include <map>
#include <future>
#include <string>
#include <sstream>
#include <functional>
#include <fstream>
#include <vector>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other){
      for(const auto& [word, count] : other.word_frequences){
      word_frequences[word] +=count;
      }
    }
};


Stats ExploreLine(const set<string>& key_words, string_view line) {
    Stats result;
        while(true){
            size_t space = line.find(' ');
            string word(line.substr(0, space));
            if (key_words.count(word) > 0){
                ++result.word_frequences[word.substr(0, word.npos)];
            }
            if (space == line.npos){
                break;
            } else{
                line.remove_prefix(space + 1);
            }
    }

    return result;
}


Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<future<Stats>> futures;
    size_t thread_count = 4;
    vector<vector<string>> publications;
    for (size_t i = 0; i < thread_count; ++i){
        publications.push_back({});
    }
    size_t stream_count = 0;
    for (string sentence; !input.eof();getline(input, sentence)){
        publications[stream_count].push_back(move( sentence));
        if (++stream_count == thread_count)
            stream_count = 0;
     }

     for (vector <string>& publication : publications){
         futures.push_back(async ([&key_words,&publication]{
             Stats result;
             for (string&line : publication){
             result += ExploreLine(key_words, line);
             }
              return result;
         }));
     }
    Stats result;
    for (auto& f : futures) {
        result += f.get();
      }
    return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
     return 0;
}
