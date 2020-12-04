#include "Common.h"

#include <algorithm>
#include <unordered_map>

const std::string colors[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

auto parseInput(std::string &&input) {
  std::vector<std::unordered_map<std::string, std::string>> passports{};
  for (auto entry : split(input, "\n\n")) {
    std::replace(entry.begin(), entry.end(), '\n', ' ');
    std::unordered_map<std::string, std::string> passport;
    for (const auto field : split(entry, ' ')) {
      auto delim = field.find(':', 0);
      auto &&key = field.substr(0, delim);
      auto &&value = field.substr(delim + 1, field.size());
      passport[key] = value;
    }
    if (passport.size() >= 7)
      passports.emplace_back(std::move(passport));
  }

  return passports;
}

int main() {
  auto passports = parseInput(getFileContents("../input/Day4/input.txt"));
  auto isValid1 = [](const auto &passport) {
    return passport.size() == 8 ||
           (passport.find("cid") == passport.end() && passport.size() == 7);
  };
  auto isValid2 = [](const auto &passport) {
    if (passport.size() < 7)
      return 0;
    if (passport.find("cid") != passport.end() && passport.size() == 7)
      return 0;

    auto byr = std::stoi(passport.at("byr"));
    auto iyr = std::stoi(passport.at("iyr"));
    auto eyr = std::stoi(passport.at("eyr"));
    auto hgt = passport.at("hgt");
    auto hcl = passport.at("hcl");
    auto ecl = passport.at("ecl");
    auto pid = passport.at("pid");
    auto hv = std::stoi(hgt);

    if (byr < 1920 || byr > 2002)
      return 0;
    if (iyr < 2010 || iyr > 2020)
      return 0;
    if (eyr < 2020 || eyr > 2030)
      return 0;

    if (hgt[hgt.size() - 1] == 'm') {
      if (hv < 150 || hv > 193)
        return 0;
    } else if (hgt[hgt.size() - 1] == 'n') {
      if (hv < 59 || hv > 76)
        return 0;
    } else
      return 0;
    if (hcl[0] != '#' || hcl.size() != 7)
      return 0;
    if (std::find(std::begin(colors), std::end(colors), ecl) ==
        std::end(colors))
      return 0;
    if (pid.size() != 9)
      return 0;

    return 1;
  };
  auto s1 = std::count_if(passports.begin(), passports.end(), isValid1);
  auto s2 = std::count_if(passports.begin(), passports.end(), isValid2);

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
