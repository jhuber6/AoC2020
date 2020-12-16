#include "Common.h"

#include <sstream>
#include <tuple>
#include <unordered_map>

auto parseTicket(std::string &str) {
  std::stringstream ss(str);
  std::vector<std::vector<long>> numbers;
  std::string id;
  std::getline(ss, id, '\n');
  while (std::getline(ss, id, '\n')) {
    std::vector<long> list;
    std::stringstream line(id);
    while (std::getline(line, id, ','))
      list.emplace_back(std::stol(id));

    numbers.emplace_back(list);
  }

  return numbers;
}

auto parseRanges(std::string &str) {
  std::replace(std::begin(str), std::end(str), '-', ' ');
  std::stringstream ss(str);
  std::string id;
  std::vector<std::tuple<long, long, long, long>> ranges;
  long l1, r1, l2, r2;
  while (std::getline(ss, id, ':')) {
    ss >> l1 >> r1 >> id >> l2 >> r2;
    ranges.push_back(std::tuple<long, long, long, long>(l1, r1, l2, r2));
  }

  return ranges;
}

int main() {
  auto fields = split(getFileContents("../input/Day16/input.txt"), "\n\n");
  auto ranges = parseRanges(fields[0]);
  auto myticket = parseTicket(fields[1]).front();
  auto nearby = parseTicket(fields[2]);
  auto isValid = [](auto &&rule, auto value) {
    const auto &[l1, r1, l2, r2] = rule;
    return (l1 <= value && value <= r1) || (l2 <= value && value <= r2);
  };

  // Get only valid tickets
  auto validTickets = std::vector<std::vector<long>>();
  auto sum = 0l;
  for (const auto &ticket : nearby) {
    bool ticketValid = true;
    for (const auto &value : ticket) {
      bool valid = false;
      for (const auto &rule : ranges)
        valid |= isValid(rule, value);
      if (!valid)
        sum += value;
      ticketValid &= valid;
    }
    if (ticketValid)
      validTickets.emplace_back(ticket);
  }

  // Get the number of rules satisfied by each column
  std::vector<std::vector<std::size_t>> rules(myticket.size());
  for (std::size_t i = 0; i < myticket.size(); i++) {
    for (std::size_t j = 0; j < validTickets.size(); j++) {
      for (std::size_t k = 0; k < ranges.size(); k++) {
        if (isValid(ranges[k], validTickets[j][i]))
          rules[i].push_back(k);
      }
    }
  }

  // Get only the rules that are satsified by every column
  std::vector<std::vector<std::size_t>> validRules(myticket.size());
  for (std::size_t i = 0; i < rules.size(); i++) {
    for (std::size_t k = 0; k < ranges.size(); k++) {
      std::size_t numValid =
          std::count(std::begin(rules[i]), std::end(rules[i]), k);
      if (numValid == validTickets.size())
        validRules[i].push_back(k);
    }
  }

  // The remaining rules will always have ascending values. Find the values that
  // aren't already seen by order of how many matching rules each column has
  std::unordered_map<std::size_t, std::size_t> map;
  std::unordered_map<std::size_t, std::size_t> v;
  for (std::size_t size = 0; size <= ranges.size(); size++) {
    for (std::size_t i = 0; i < rules.size(); i++) {
      if (validRules[i].size() == size) {
        for (std::size_t j = 0; j < validRules[i].size(); j++) {
          if (map.find(validRules[i][j]) == map.end()) {
            v[validRules[i][j]] = myticket[i];
            map[validRules[i][j]] = 1;
          }
        }
      }
    }
  }

  auto s1 = sum;
  auto s2 = v[0] * v[1] * v[2] * v[3] * v[4] * v[5];

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
