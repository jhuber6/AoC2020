#include "Common.h"

#include <array>

int main() {
  auto contents = split(getFileContents("../input/Day6/input.txt"), "\n\n");

  long sum = 0;
  for (const auto &group : contents) {
    std::array<bool, 26> mask;
    std::fill(std::begin(mask), std::end(mask), false);
    for (const auto &person : getLines(group)) {
      for (const auto &c : person)
        mask[c - 'a'] = true;
    }
    sum += std::count_if(std::begin(mask), std::end(mask),
                         [](auto x) { return x; });
  }

  auto s1 = sum;

  sum = 0;
  for (const auto &group : contents) {
    std::array<bool, 26> mask;
    std::fill(std::begin(mask), std::end(mask), true);
    for (const auto &person : getLines(group)) {
      std::array<bool, 26> answers;
      std::fill(std::begin(answers), std::end(answers), false);
      for (const auto &c : person)
        answers[c - 'a'] = true;
      std::transform(std::begin(mask), std::end(mask), std::begin(answers),
                     std::begin(mask), [](bool x, bool y) { return x & y; });
    }
    sum += std::count_if(std::begin(mask), std::end(mask),
                         [](auto x) { return x; });
  }

  auto s2 = sum;

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
