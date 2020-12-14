#include "Common.h"

#include <cstdint>
#include <numeric>
#include <unordered_map>

#include <bitset>

int main() {
  std::unordered_map<uint64_t, uint64_t> mem;
  auto contents = getFileContents("../input/Day14/input.txt");
  std::replace(std::begin(contents), std::end(contents), '[', ' ');
  std::replace(std::begin(contents), std::end(contents), ']', ' ');
  auto lines = getLines(contents);

  uint64_t maskAnd = 0x0;
  uint64_t maskOr = 0x0;
  for (const auto &line : lines) {
    auto words = getWords(line);
    if (words[0] == "mask") {
      auto maskAndStr = words[2];
      auto maskOrStr = words[2];
      std::replace(std::begin(maskAndStr), std::end(maskAndStr), 'X', '1');
      std::replace(std::begin(maskOrStr), std::end(maskOrStr), 'X', '0');
      maskAnd = std::stol(maskAndStr, nullptr, 2);
      maskOr = std::stol(maskOrStr, nullptr, 2);
    } else {
      uint64_t idx = std::stol(words[1]);
      uint64_t val = std::stol(words[3]);
      val &= maskAnd;
      val |= maskOr;
      mem[idx] = val;
    }
  }

  uint64_t s1 = 0;
  for (const auto &[k, v] : mem)
    s1 += v;

  mem.clear();
  uint64_t mask = 0x0;
  uint64_t floating = 0x0;
  for (const auto &line : lines) {
    auto words = getWords(line);
    if (words[0] == "mask") {
      auto maskStr = words[2];
      auto maskFloatingStr = words[2];
      std::replace(std::begin(maskStr), std::end(maskStr), 'X', '0');
      std::replace(std::begin(maskFloatingStr), std::end(maskFloatingStr), '1',
                   '0');
      std::replace(std::begin(maskFloatingStr), std::end(maskFloatingStr), 'X',
                   '1');
      mask = std::stol(maskStr, nullptr, 2);
      floating = std::stol(maskFloatingStr, nullptr, 2);
    } else {
      uint64_t idx = std::stol(words[1]);
      uint64_t val = std::stol(words[3]);

      uint64_t perms = 1 << std::bitset<36>(floating).count();
      for (uint64_t i = 0; i < perms; i++) {
        int k = 0;
        uint64_t maskPerm = 0x0;
        for (uint64_t m = 0; m < 36; m++) {
          if ((floating >> m) & 0x1) {
            maskPerm |= ((i >> k) & 0x1) << m;
            k++;
          }
        }
        mem[(idx & ~floating) | mask | maskPerm] = val;
      }
    }
  }

  uint64_t s2 = 0;
  for (const auto &[k, v] : mem)
    s2 += v;

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
