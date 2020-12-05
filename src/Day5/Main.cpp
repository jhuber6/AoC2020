#include "Common.h"

#include <numeric>

int main() {
  auto lines = getLines(getFileContents("../input/Day5/input.txt"));
  auto seatIDs = std::vector<int>(lines.size());
  auto getSeatID = [](const std::string &l) {
    auto s = 0b0;
    for (const auto &c : l)
      s = (s << 1) + (c == 'B' || c == 'R');
    return s;
  };
  std::transform(std::begin(lines), std::end(lines), std::begin(seatIDs),
                 getSeatID);
  auto max = *std::max_element(std::begin(seatIDs), std::end(seatIDs));
  auto min = *std::min_element(std::begin(seatIDs), std::end(seatIDs));
  auto sum = std::accumulate(std::begin(seatIDs), std::end(seatIDs), 0);

  auto s1 = max;
  auto s2 = -1 * (min - max - 1) * (min + max) / 2 - sum;

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
