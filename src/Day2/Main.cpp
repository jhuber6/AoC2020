#include "Common.h"

#include <algorithm>

int main() {
  auto content = getFileContents("../input/Day2/input.txt");
  std::replace(content.begin(), content.end(), '-', ' '); 
  auto lines = getLines(content);
  auto words = map(lines, getWords);

  auto &&p1 = [](int lo, int hi, char key, std::string &pwd) {
    auto c = std::count(pwd.begin(), pwd.end(), key);
    return lo <= c && c <= hi;
  };
  auto &&p2 = [](int lo, int hi, char key, std::string &pwd) {
    return (pwd[lo - 1] == key) ^ (pwd[hi - 1] == key);
  };

  auto s1 = std::count_if(words.begin(), words.end(), [p1](auto &line) {
      return p1(std::stoi(line[0]), std::stoi(line[1]), line[2][0], line[3]);
  });
  auto s2 = std::count_if(words.begin(), words.end(), [p2](auto &line) {
      return p2(std::stoi(line[0]), std::stoi(line[1]), line[2][0], line[3]);
  });

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
