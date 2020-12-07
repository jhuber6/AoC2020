#include "Common.h"

#include <sstream>
#include <unordered_map>

auto parse(std::string &&contents) {
  std::unordered_map<std::string, std::unordered_map<std::string, int>> bags;
  for (const auto &line : getLines(contents)) {
    std::unordered_map<std::string, int> map{};
    std::stringstream ss(line);
    std::string color1, color2, x, str;

    ss >> color1 >> color2 >> x >> x;
    const std::string key = color1 + " " + color2;
    while (std::getline(ss, str, ',')) {
      std::stringstream ss2(str);
      int number;
      std::string c1, c2;
      ss2 >> number >> c1 >> c2;

      std::string bag = c1 + " " + c2;
      map[bag] = number;
    }
    bags[key] = std::move(map);
  }

  return bags;
}

bool visit(
    std::unordered_map<std::string, std::unordered_map<std::string, int>> &bags,
    const std::string &bag) {
  if (bags[bag].find("shiny gold") != bags[bag].end())
    return true;

  for (const auto &[color, amount] : bags[bag])
    if (visit(bags, color))
      return true;

  return false;
}

long count(
    std::unordered_map<std::string, std::unordered_map<std::string, int>> &bags,
    const std::string &bag) {
  long sum = 0;
  for (const auto &[color, amount] : bags[bag])
    sum += amount + amount * count(bags, color);

  return sum;
}

int main() {
  auto bags = parse(getFileContents("../input/Day7/input.txt"));

  long s1 = std::count_if(std::begin(bags), std::end(bags),
                          [&bags](auto x) { return visit(bags, x.first); });
  long s2 = count(bags, "shiny gold");

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
