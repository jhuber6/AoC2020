#include "Common.h"

#include <tuple>
#include <unordered_map>

auto parseLine(const std::string &line) {
  auto pos = line.find(' ');
  auto opcode = line.substr(0, pos);
  auto value = std::stoi(line.substr(pos + 1, line.size()));
  return std::tuple<std::string, long>(opcode, value);
}

int main() {
  auto lines = getLines(getFileContents("../input/Day8/input.txt"));
  auto opcodes = std::vector<std::tuple<std::string, long>>(lines.size());
  std::transform(std::begin(lines), std::end(lines), std::begin(opcodes),
                 parseLine);

  std::unordered_map<std::size_t, long> insts;
  std::size_t idx = 0;
  long accumulator = 0;
  while (insts.find(idx) == insts.end()) {
    const auto &[opcode, value] = opcodes[idx];
    insts[idx++] = accumulator;
    if (opcode == "acc")
      accumulator += value;
    else if (opcode == "jmp")
      idx += value - 1;
  }

  auto s1 = accumulator;

  int nthInstruction = 0;
  while (idx != opcodes.size()) {
    auto i = 0;
    idx = 0;
    accumulator = 0;
    insts.clear();
    while (idx < opcodes.size() && insts.find(idx) == insts.end()) {
      const auto &[opcode, value] = opcodes[idx];
      insts[idx++] = accumulator;
      if (opcode == "acc")
        accumulator += value;
      else if (opcode == "jmp") {
        if (i++ != nthInstruction)
          idx += value - 1;
      } else {
        if (i++ == nthInstruction)
          idx += value - 1;
      }
    }
    nthInstruction += 1;
  }

  auto s2 = accumulator;

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
