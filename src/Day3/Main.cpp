#include "Common.h"

#include <functional>
#include <numeric>
#include <tuple>

using Pair = std::tuple<int, int>;

int main() {
  auto grid = getLines(getFileContents("../input/Day3/input.txt"));
  auto height = grid.size();
  auto width = grid[0].size();

  auto moves = std::vector<Pair>({{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}});
  auto trees = std::vector<int>();
  auto &&move = [&](Pair dir) {
    const auto &[r, d] = dir;
    int numTrees = 0;
    std::size_t x = 0;
    std::size_t y = 0;
    while (y < height) {
      if (grid[y][x] == '#')
        numTrees++;
      x = (x + r) % width;
      y = y + d;
    }

    return numTrees;
  };

  std::transform(moves.begin(), moves.end(), std::back_inserter(trees), move);
  int s1 = trees[1];
  int s2 =
      std::accumulate(trees.begin(), trees.end(), 1, std::multiplies<int>());

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
