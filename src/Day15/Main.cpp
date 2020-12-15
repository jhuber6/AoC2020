#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

long solve(const std::vector<long> &numbers, const std::size_t iterations) {
  std::vector<std::array<unsigned long, 2>> uses(iterations);

  for (std::size_t i = 0; i < numbers.size(); i++)
    uses[numbers[i]] = {0, (i + 1)};

  auto last = numbers.back();
  for (std::size_t i = numbers.size(); i < iterations; i++) {
    if (!uses[last][0])
      last = 0;
    else
      last = uses[last][1] - uses[last][0];

    uses[last] = {uses[last][1], i + 1};
  }

  return last;
}

int main() {
  auto numbers = std::vector<long>({0, 14, 1, 3, 7, 9});

  std::cout << solve(numbers, 2020) << "\n";
  std::cout << solve(numbers, 30000000) << "\n";
}
