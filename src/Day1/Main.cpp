#include "Common.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

int partOne(std::vector<int> lines) {
  std::unordered_map<int, int> dict;
  for (const auto &n : lines)
    dict[n] = lines[n];

  for (const auto &n : lines) {
    if (dict.find(2020 - n) != dict.end())
      return n * (2020 - n);
  }

  return 0;
}

int partTwo(std::vector<int> lines) {
  std::unordered_map<int, int> dict;
  for (const auto &n : lines)
    dict[n] = lines[n];

  for (std::size_t i = 0; i < lines.size(); i++) {
    for (std::size_t j = i + 1; j < lines.size(); j++) {
      if (dict.find(2020 - (lines[i] + lines[j])) != dict.end())
        return lines[i] * lines[j] * (2020 - (lines[i] + lines[j]));
    }
  }

  return 0;
}

int main() {
  auto lines = getLines(getFileContents("../input/Day1/input.txt"));
  auto numbers = std::vector<int>(lines.size());
  std::transform(std::begin(lines), std::end(lines), std::begin(numbers),
                 [](auto x) { return std::stoi(x); });

  std::cout << partOne(numbers) << "\n";
  std::cout << partTwo(numbers) << "\n";
}
