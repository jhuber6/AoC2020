#include "Common.h"

#include <numeric>

int main() {
  auto lines = getLines(getFileContents("../input/Day9/input.txt"));
  auto numbers = std::vector<long>(lines.size());
  std::transform(std::begin(lines), std::end(lines), std::begin(numbers),
                 [](auto x) { return std::stol(x); });

  auto findSumPairs = [&numbers](auto begin, auto end, long target) {
    for (std::size_t i = begin; i < end; i++) {
      for (std::size_t j = i + 1; j < end; j++) {
        if (numbers[i] + numbers[j] == target)
          return true;
      }
    }
    return false;
  };

  long target = 0;
  long result = 0;
  std::size_t begin = 0;
  for (std::size_t end = 25; end < numbers.size(); ++begin, ++end) {
    if (!findSumPairs(begin, end, numbers[end]))
      target = numbers[end];
  }

  for (std::size_t i = 0; i < numbers.size(); ++i) {
    for (std::size_t j = i + 1; j < numbers.size(); ++j) {
      long sum = std::accumulate(std::begin(numbers) + i,
                                 std::begin(numbers) + j + 1, 0);
      if (sum > target)
        break;
      if (sum == target) {
        long max = *std::max_element(std::begin(numbers) + i,
                                     std::begin(numbers) + j + 1);
        long min = *std::min_element(std::begin(numbers) + i,
                                     std::begin(numbers) + j + 1);
        result = max + min;
      }
    }
  }

  auto s1 = target;
  auto s2 = result;

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
