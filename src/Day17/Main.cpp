#include "Common.h"

#include <map>

long run(std::map<std::array<long, 4>, bool> board) {
  std::map<std::array<long, 4>, bool> update;

  // Buffer in the initially unactivated borders
  for (const auto &[v, c] : board) {
    const auto &[x, y, z, w] = v;
    for (long i = -1; i <= 1; ++i) {
      for (long j = -1; j <= 1; ++j) {
        for (long k = -1; k <= 1; ++k) {
          for (long l = -1; l <= 1; ++l) {
            auto p = std::array<long, 4>({x + i, y + j, z + k, w + l});
            if (board.find(p) == board.end())
              update[p] = false;
            else
              update[p] = board[p];
          }
        }
      }
    }
  }
  board = update;

  for (long cycles = 0; cycles < 6; ++cycles) {
    for (const auto &[v, c] : board) {
      const auto &[x, y, z, w] = v;
      long count = 0;
      for (long i = -1; i <= 1; ++i) {
        for (long j = -1; j <= 1; ++j) {
          for (long k = -1; k <= 1; ++k) {
            for (long l = -1; l <= 1; ++l) {
              auto p = std::array<long, 4>({x + i, y + j, z + k, w + l});
              if (i == 0 && j == 0 && k == 0 && l == 0)
                continue;
              if (board.find(p) == board.end())
                update[p] = false;
              else
                count += board[p];
            }
          }
        }
      }
      update[v] = ((c && (count == 2 || count == 3)) || (!c && count == 3));
    }
    board = update;
  }

  return std::count_if(std::begin(board), std::end(board),
                       [](auto x) { return x.second; });
}

int main() {
  auto lines = getLines(getFileContents("../input/Day17/input.txt"));
  std::map<std::array<long, 4>, bool> board;

  for (long i = 0; static_cast<std::size_t>(i) < lines.size(); ++i)
    for (long j = 0; static_cast<std::size_t>(j) < lines[i].size(); ++j)
      board[std::array<long, 4>({i, j, 0, 0})] = lines[i][j] == '#';

  std::cout << run(board) << "\n";
}
