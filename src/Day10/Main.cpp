#include "Common.h"

#include <unordered_map>

static std::unordered_map<std::size_t, long> cache;

long combinations(const std::vector<long> &numbers, std::size_t pos) {
  if (numbers[pos] == numbers[numbers.size() - 1])
    return 1;

  long &sum = cache[pos];
  if (!sum)
    for (std::size_t i = pos + 1; numbers[pos] + 3 >= numbers[i]; ++i)
      sum += combinations(numbers, i);

  return sum;
}

long allCombinations(const std::vector<long> &numbers) {
  return combinations(numbers, 0);
}

int main() {
  auto lines = getLines(getFileContents("../input/Day10/input.txt"));
  auto numbers = std::vector<long>(lines.size());
  std::transform(std::begin(lines), std::end(lines), std::begin(numbers),
                 [](auto x) { return std::stol(x); });
  numbers.push_back(0);
  std::sort(std::begin(numbers), std::end(numbers));
  numbers.push_back(numbers.back() + 3);

  long number = 0;
  long one = 0;
  long three = 0;
  for (const auto x : numbers) {
    if (x - number == 1)
      one++;
    else if (x - number == 3)
      three++;
    number = x;
  }

  auto s1 = one * three;
  auto s2 = allCombinations(numbers);

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
