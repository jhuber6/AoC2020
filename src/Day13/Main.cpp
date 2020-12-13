#include "Common.h"

#include <cmath>

int main() {
  auto lines = getLines(getFileContents("../input/Day13/input.txt"));
  auto list = split(lines[1], ',');
  auto time = std::stol(lines[0]);
  auto strs = std::vector<std::string>();
  auto buses = std::vector<long>();
  auto diff = std::vector<long>();
  auto getMultiple = [time](auto x) {
    double td = static_cast<double>(time);
    double xd = static_cast<double>(x);
    return x * static_cast<long>(std::ceil(td / xd)) - time;
  };
  std::copy_if(std::begin(list), std::end(list), std::back_inserter(strs),
               [](auto x) { return x != "x"; });
  std::transform(std::begin(strs), std::end(strs), std::back_inserter(buses),
                 [](auto x) { return std::stol(x); });
  std::transform(std::begin(buses), std::end(buses), std::back_inserter(diff),
                 getMultiple);
  auto idx =
      std::min_element(std::begin(diff), std::end(diff)) - std::begin(diff);
  auto s1 = diff[idx] * buses[idx];

  // I just put this in mathematica
  // std::cout << "t = " << 0 << " (mod " << list[0] << ")\n";
  // for (std::size_t i = 1; i < list.size(); i++) {
  //   if (list[i] != "x") {
  //     std::cout << "t = " << std::stol(list[i]) - static_cast<long>(i) << "
  //     (mod " << list[i] << ")\n";
  //   }
  // }

  auto s2 = 379786358533423l;

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
