#include "Common.h"

long partOne(std::vector<std::string> board) {
  auto update = board;
  do {
    board = update;
    for (std::size_t i = 0; i < board.size(); i++) {
      for (std::size_t j = 0; j < board[i].size(); j++) {
        auto occupied = 0;
        for (auto r = -1; r <= 1; r++) {
          for (auto c = -1; c <= 1; c++) {
            if (static_cast<long>(i) + r < 0 ||
                i + static_cast<std::size_t>(r) >= board.size())
              continue;
            if (static_cast<long>(j) + c < 0 ||
                j + static_cast<std::size_t>(c) >= board[i].size())
              continue;
            if (r == 0 && c == 0)
              continue;
            if (board[i + r][j + c] == '#')
              occupied++;
          }
        }
        if (board[i][j] == 'L' && occupied == 0)
          update[i][j] = '#';
        else if (board[i][j] == '#' && occupied >= 4)
          update[i][j] = 'L';
      }
    }
  } while (board != update);

  long occupied = 0;
  for (const auto &r : board)
    for (const auto &c : r)
      if (c == '#')
        occupied++;

  return occupied;
}

long partTwo(std::vector<std::string> board) {
  auto update = board;
  do {
    board = update;
    for (std::size_t i = 0; i < board.size(); i++) {
      for (std::size_t j = 0; j < board[i].size(); j++) {
        auto search = [i, j, &board](auto x, auto y) {
          long r = i + y;
          long c = j + x;
          while (1) {
            if (r < 0 || static_cast<std::size_t>(r) >= board.size())
              return 0;
            if (c < 0 || static_cast<std::size_t>(c) >= board[i].size())
              return 0;
            if (board[r][c] == '#')
              return 1;
            if (board[r][c] == 'L')
              return 0;
            r += y;
            c += x;
          }
        };
        auto occupied = 0;
        occupied += search(1, 1);
        occupied += search(1, 0);
        occupied += search(1, -1);
        occupied += search(0, -1);
        occupied += search(-1, -1);
        occupied += search(-1, 0);
        occupied += search(-1, 1);
        occupied += search(0, 1);
        if (board[i][j] == 'L' && occupied == 0)
          update[i][j] = '#';
        else if (board[i][j] == '#' && occupied >= 5)
          update[i][j] = 'L';
      }
    }
  } while (board != update);

  long occupied = 0;
  for (const auto &r : board)
    for (const auto &c : r)
      if (c == '#')
        occupied++;

  return occupied;
}

int main() {
  auto board = getLines(getFileContents("../input/Day11/input.txt"));

  auto s1 = partOne(board);
  auto s2 = partTwo(board);

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
