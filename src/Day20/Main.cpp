#include "Common.h"

#include <unordered_map>
#include <array>
#include <tuple>

constexpr std::size_t N = 10;

auto getTiles(std::vector<std::string> &&tiles) {
  std::unordered_map<long, std::string> tileMap;

  for (const auto &tile : tiles) {
    auto tileId = tile.substr(tile.find(' ') + 1, 
                              tile.find(':') - tile.find(' ') - 1);
    auto tileStr = tile.substr(tile.find('\n') + 1);
    auto idx = std::stol(tileId);
    auto &&tileVal = std::string("");
    std::copy_if(std::begin(tileStr), std::end(tileStr), std::back_inserter(tileVal),
                  [] (auto x) { return x != '\n'; });

    tileMap[idx] = tileVal;
  }
  return tileMap;
}

auto getCorners(const std::unordered_map<long, std::string> &tiles) {
  std::unordered_map <std::string, long> edges;
  auto getEdges = [](const std::string &tile) {
    auto top = tile.substr(0, N);
    auto bottom = tile.substr(N*(N-1), N);
    auto left = std::string("");
    auto right = std::string("");
    for (std::size_t i = 0; i < N; ++i)
      left += tile[i*N];
    for (std::size_t i = 0; i < N; ++i)
      right += tile[i*N + N - 1];
    return std::array<std::string, 4>({top, right, bottom, left});
  };

  for (const auto &[id, tile] : tiles) {
    for (auto &edge : getEdges(tile)) {
      edges[edge]++;
      std::reverse(std::begin(edge), std::end(edge));
      edges[edge]++;
    }
  }

  long product = 1l;
  for (const auto &[id, tile] : tiles) {
    long numEdges = 0;
    for (auto &edge : getEdges(tile)) {
      numEdges += edges[edge];
      std::reverse(std::begin(edge), std::end(edge));
      numEdges += edges[edge];
    }

    if (numEdges == 12)
      product *= id;
  }

  return product;
}

// Each edge only has a single match
//
// Create a map from edges to a list of ID's that contain it
// 
// For each tile 
//  For each edge
//    if only one tile has this edge
//      edge piece
//    
//    Get id of tile with shared edge
//    Rotate / flip tile until the edges are aligned 
//    Add that side to the data tree mapping a tile to four other tiles (or
//    nullptr)
//
//  Once done Walk the data structure from the top to the bottom removing
//  edges
//
//  Try to match sea monster with each rotation and mark indices where it
//  occured.
//
//  Count occurences that weren't marked previously.

int main() {
  auto contents = getFileContents("../input/Day20/input.txt");
  auto tiles = getTiles(split(contents, "\n\n"));
  auto s1 = getCorners(tiles);

  std::cout << s1 << "\n";
}
