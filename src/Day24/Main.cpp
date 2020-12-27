#include "Common.h"

#include <map>
#include <tuple>
#include <vector>

static const std::vector<std::tuple<int, int, int>> neighbors = {
    {1, -1, 0}, {-1, 1, 0}, {1, 0, -1}, {-1, 0, 1}, {0, 1, -1}, {0, -1, 1}};

auto getHexCoord(const std::string &dirs) {
  auto [x, y, z] = std::tuple<int, int, int>();
  for (std::size_t i = 0; i < dirs.size(); ++i) {
    if (dirs[i] == 'e') {
      x++;
      y--;
    } else if (dirs[i] == 'w') {
      x--;
      y++;
    } else if (dirs[i] == 'n' && dirs[i + 1] == 'e') {
      x++;
      z--;
      i++;
    } else if (dirs[i] == 's' && dirs[i + 1] == 'w') {
      x--;
      z++;
      i++;
    } else if (dirs[i] == 'n' && dirs[i + 1] == 'w') {
      y++;
      z--;
      i++;
    } else if (dirs[i] == 's' && dirs[i + 1] == 'e') {
      y--;
      z++;
      i++;
    }
  }

  return std::tuple<int, int, int>(x, y, z);
}

int main() {
  auto lines = getLines(getFileContents("../input/Day24/input.txt"));
  std::map<std::tuple<int, int, int>, bool> grid;

  for (const auto &line : lines) {
    auto &color = grid[getHexCoord(line)];
    color = !color;
  }
  auto s1 = std::count_if(std::begin(grid), std::end(grid),
                          [](auto x) { return x.second; });

  // Buffer out edges in the map
  std::map<std::tuple<int, int, int>, bool> update;
  for (const auto &[p, c] : grid) {
    const auto [x, y, z] = p;
    update[p] = c;
    for (const auto [x1, y1, z1] : neighbors) {
      const auto tile = std::tuple<int, int, int>(x + x1, y + y1, z + z1);
      if (grid.find(tile) != grid.end())
        update[tile] = grid.at(tile);
      else
        update[tile] = false;
    }
  }

  grid = update;
  for (int i = 0; i < 100; ++i) {
    for (const auto &[p, c] : grid) {
      const auto [x, y, z] = p;
      long count = 0l;
      for (const auto [x1, y1, z1] : neighbors) {
        const auto tile = std::tuple<int, int, int>(x + x1, y + y1, z + z1);
        if (grid.find(tile) != grid.end())
          count += grid.at(tile);
        else
          update[tile] = false;
      }
      if (c && (count == 0 || count > 2))
        update[p] = false;
      else if (!c && count == 2)
        update[p] = true;
    }
    grid = update;
  }

  auto s2 = std::count_if(std::begin(grid), std::end(grid),
                          [](auto x) { return x.second; });
  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
