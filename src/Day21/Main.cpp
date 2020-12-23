#include "Common.h"

#include <map>
#include <sstream>
#include <unordered_map>

auto getIngredients(const std::string &str) {
  auto loc = str.find("contains");
  auto ingredientStr = str.substr(0, loc - 2);
  return getWords(ingredientStr);
}

auto getAllergins(const std::string &str) {
  auto loc = str.find("contains");
  auto allerginStr = str.substr(loc + 9);
  allerginStr.pop_back();
  return split(allerginStr, ", ");
}

auto getOccurences(const std::vector<std::string> &lines) {
  std::unordered_map<std::string, std::vector<std::string>> allerginMap;

  for (const auto &line : lines) {
    auto ingredients = getIngredients(line);
    auto allergins = getAllergins(line);

    std::sort(std::begin(ingredients), std::end(ingredients));
    std::sort(std::begin(allergins), std::end(allergins));
    for (const auto allergin : allergins) {
      auto &e = allerginMap[allergin];

      if (e.empty()) {
        e = ingredients;
      } else {
        auto idx = std::set_intersection(std::begin(e), std::end(e),
                                         std::begin(ingredients),
                                         std::end(ingredients), std::begin(e));
        e.resize(idx - std::begin(e));
      }
    }
  }

  return allerginMap;
}

int main() {
  auto lines = getLines(getFileContents("../input/Day21/input.txt"));
  auto occurences = getOccurences(lines);

  auto s1 = 0l;
  for (const auto &line : lines) {
    auto ingredients = getIngredients(line);
    auto allergins = getAllergins(line);

    for (const auto &ingredient : ingredients) {
      bool found = false;
      for (const auto &[allergin, elems] : occurences) {
        if (std::find(elems.begin(), elems.end(), ingredient) != elems.end())
          found = true;
      }
      if (!found)
        s1++;
    }
  }

  std::map<std::string, std::string> valid;
  while (!occurences.empty()) {
    auto e = std::vector<std::string>();
    auto k = std::string("");
    for (auto &[allergin, elems] : occurences) {
      if (elems.size() == 1) {
        valid[allergin] = elems.front();
        e = elems;
        k = allergin;
      }
    }
    occurences.erase(k);

    for (auto &[allergin, elems] : occurences) {
      auto idx =
          std::set_difference(std::begin(elems), std::end(elems), std::begin(e),
                              std::end(e), std::begin(elems));
      elems.resize(idx - std::begin(elems));
    }
  }

  std::string s2 = "";
  for (const auto &[k, e] : valid)
    s2 += e + ",";
  s2.pop_back();

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
