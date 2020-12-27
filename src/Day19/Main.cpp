#include "Common.h"

#include <sstream>
#include <tuple>
#include <unordered_map>
#include <variant>

using Rule = std::vector<std::vector<std::variant<std::size_t, char>>>;

auto parseRules(const std::vector<std::string> &lines) {
  auto rules = std::unordered_map<std::size_t, Rule>();
  std::string id;
  for (const auto &line : lines) {
    std::stringstream ss(line);
    std::size_t idx;
    ss >> idx >> id;
    Rule rule;
    std::vector<std::variant<std::size_t, char>> subrule;
    while (ss >> id) {
      std::variant<std::size_t, char> v;
      if (id == "|")
        break;
      if (id[0] == '\"')
        v = id[1];
      else
        v = static_cast<std::size_t>(std::stol(id));
      subrule.emplace_back(v);
    }
    rule.emplace_back(subrule);
    if (id == "|") {
      std::vector<std::variant<std::size_t, char>> subrule2;
      while (ss >> id) {
        std::variant<std::size_t, char> v;
        if (id[0] == '\"')
          v = id[1];
        else
          v = static_cast<std::size_t>(std::stol(id));
        subrule2.emplace_back(v);
      }
      rule.emplace_back(subrule2);
    }
    rules[idx] = rule;
  }
  return rules;
}

// Eager Recursive-Descent LL(1) parser with backtracking
class Parser {
public:
  Parser(const std::unordered_map<std::size_t, Rule> &rules,
         const std::string &str)
      : rules(rules), message(str){};

  bool run(const Rule &rule) {
    auto result = parseRule(rule);
    return (idx == message.size()) ? result : false;
  }

  bool parseRule(const Rule &rule) {
    if (auto *c = std::get_if<char>(&rule[0][0]))
      return match(*c);

    std::size_t saveIdx = idx;
    for (const auto subrule : rule) {
      bool status = true;
      idx = saveIdx;
      for (const auto match : subrule) {
        if (!status)
          break;
        status &= parseRule(rules.at(std::get<std::size_t>(match)));
      }

      if (status)
        return true;
    }

    return false;
  };

private:
  bool match(const char c) {
    if (c == message[idx++])
      return true;
    return false;
  }

  const std::unordered_map<std::size_t, Rule> rules;
  const std::string message = "";

  /// Index of the current character. Must be restored after testing a branch.
  std::size_t idx = 0;
};

int main() {
  auto contents = split(getFileContents("../input/Day19/input.txt"), "\n\n");
  auto rules = parseRules(getLines(contents[0]));
  auto messages = getLines(contents[1]);

  auto s1 = 0l;
  for (const auto &message : messages) {
    Parser parser(rules, message);
    s1 += parser.run(rules[0]);
  }

  // A direct translation doesn't work because the rule 0: 8 11 isn't LL(1) due
  // to both 8 and 11 being able to derive ε. The backtracking cannot know hou
  // much to recurse in a single direction.
  //
  // A workaround is to simply test a few common expansions of 8 instead.
  rules[0] = {{42ul, 11ul},
              {42ul, 42ul, 11ul},
              {42ul, 42ul, 42ul, 11ul},
              {42ul, 42ul, 42ul, 42ul, 11ul},
              {42ul, 42ul, 42ul, 42ul, 42ul, 11ul},
              {42ul, 42ul, 42ul, 42ul, 42ul, 42ul, 11ul},
              {42ul, 42ul, 42ul, 42ul, 42ul, 42ul, 42ul, 11ul}};

  // E  := A E' B
  // E' := A E' B | ε
  rules[999] = {{42ul, 999ul, 31ul}, {}};
  rules[11] = {{42ul, 999ul, 31ul}};

  auto s2 = 0l;
  for (const auto &message : messages) {
    Parser parser(rules, message);
    s2 += parser.run(rules[0]);
  }

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
