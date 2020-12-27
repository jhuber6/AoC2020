#include "Common.h"

#include <array>
#include <memory>
#include <tuple>
#include <unordered_map>

constexpr std::size_t N = 10;

constexpr std::size_t monsterH = 3;
constexpr std::size_t monsterW = 20;
const std::string monster =
    "                  # #    ##    ##    ### #  #  #  #  #  #   ";

struct Piece {
  Piece(long id, std::string tile)
      : id(id), tile(tile), top(nullptr), bottom(nullptr), left(nullptr),
        right(nullptr) {}
  long id;
  std::string tile;

  std::shared_ptr<Piece> top;
  std::shared_ptr<Piece> bottom;
  std::shared_ptr<Piece> left;
  std::shared_ptr<Piece> right;
};

std::string flip(const std::string &tile, std::size_t Dim = N) {
  std::string dest;
  dest.resize(tile.size());
  for (std::size_t i = 0; i < Dim; ++i)
    for (std::size_t j = 0; j < Dim; ++j)
      dest[i * Dim + j] = tile[i * Dim + (Dim - 1 - j)];

  return dest;
}

std::string rotate(const std::string &tile, std::size_t Dim = N) {
  std::string dest;
  dest.resize(tile.size());
  for (std::size_t i = 0; i < Dim; ++i)
    for (std::size_t j = 0; j < Dim; ++j)
      dest[i * Dim + j] = tile[j * Dim + i];

  return flip(dest, Dim);
}

std::string getTop(const std::string &tile) {
  return tile.substr(0, N);
}

std::string getLeft(const std::string &tile) {
  return rotate(tile).substr(0, N);
}

std::string getBottom(const std::string &tile) {
  return rotate(rotate(tile)).substr(0, N);
}

std::string getRight(const std::string &tile) {
  return rotate(rotate(rotate(tile))).substr(0, N);
}

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

auto getEdgeMap(const std::unordered_map<long, std::string> &tiles) {
  std::unordered_map<std::string, std::vector<long>> edgeMap;

  for (const auto &[id, tile] : tiles) {
    edgeMap[getTop(tile)].emplace_back(id);
    edgeMap[getLeft(tile)].emplace_back(id);
    edgeMap[getRight(tile)].emplace_back(id);
    edgeMap[getBottom(tile)].emplace_back(id);
    edgeMap[getTop(flip(tile))].emplace_back(id);
    edgeMap[getLeft(flip(tile))].emplace_back(id);
    edgeMap[getRight(flip(tile))].emplace_back(id);
    edgeMap[getBottom(flip(tile))].emplace_back(id);
  }

  return edgeMap;
}

std::unordered_map<long, std::shared_ptr<Piece>> pieceMap;
std::unordered_map<long, bool> visitedMap;
void fitPiece(std::shared_ptr<Piece> &p,
              std::unordered_map<long, std::string> &tiles,
              std::unordered_map<std::string, std::vector<long>> &edgeMap) {
  auto getNeighbor = [&](const std::string &edge, auto &&edgeGetter) {
    auto &ids = edgeMap[edge];
    if (ids.size() < 2)
      return std::make_tuple<long, std::string>(-1, "");

    long neighborId = (p->id == ids[0]) ? ids[1] : ids[0];

    auto neighborTile = tiles[neighborId];
    long flips = 0;
    while (edgeGetter(neighborTile) != edge) {
      neighborTile = rotate(neighborTile);
      if (++flips == 4)
        neighborTile = flip(neighborTile);
    }

    return std::make_tuple(neighborId, neighborTile);
  };

  if (!p)
    return;

  if (visitedMap[p->id])
    return;
  visitedMap[p->id] = true;

  auto &tile = p->tile;
  auto [topId, topTile] = getNeighbor(getTop(tile), getBottom);
  auto [leftId, leftTile] = getNeighbor(getLeft(tile), getRight);
  auto [bottomId, bottomTile] = getNeighbor(getBottom(tile), getTop);
  auto [rightId, rightTile] = getNeighbor(getRight(tile), getLeft);

  if (topId != -1) {
    auto &topPiece = pieceMap[topId];
    if (!topPiece)
      topPiece = std::make_shared<Piece>(topId, flip(topTile));
    topPiece->bottom = p;
    p->top = topPiece;
  } else
    p->top = nullptr;
  if (leftId != -1) {
    auto &leftPiece = pieceMap[leftId];
    if (!leftPiece)
      leftPiece =
          std::make_shared<Piece>(leftId, rotate(rotate(flip(leftTile))));
    leftPiece->right = p;
    p->left = leftPiece;
  } else
    p->left = nullptr;

  if (bottomId != -1) {
    auto &bottomPiece = pieceMap[bottomId];
    if (!bottomPiece)
      bottomPiece = std::make_shared<Piece>(bottomId, flip(bottomTile));
    bottomPiece->top = p;
    p->bottom = bottomPiece;
  } else
    p->bottom = nullptr;

  if (rightId != -1) {
    auto &rightPiece = pieceMap[rightId];
    if (!rightPiece)
      rightPiece =
          std::make_shared<Piece>(rightId, rotate(rotate(flip(rightTile))));
    rightPiece->left = p;
    p->right = rightPiece;
  } else
    p->right = nullptr;

  fitPiece(p->top, tiles, edgeMap);
  fitPiece(p->left, tiles, edgeMap);
  fitPiece(p->bottom, tiles, edgeMap);
  fitPiece(p->right, tiles, edgeMap);

  return;
}

long getCornerProduct(std::shared_ptr<Piece> head) {
  long product = 1;
  while (head->top)
    head = head->top;
  while (head->left)
    head = head->left;
  product *= head->id;
  while (head->bottom)
    head = head->bottom;
  product *= head->id;
  while (head->right)
    head = head->right;
  product *= head->id;
  while (head->top)
    head = head->top;
  product *= head->id;

  return product;
}

auto getImage(std::shared_ptr<Piece> head) {
  while (head->top)
    head = head->top;
  while (head->left)
    head = head->left;

  std::size_t size = 0;
  auto getSize = head;
  while (getSize) {
    getSize = getSize->right;
    size++;
  }
  std::vector<std::string> imageVec(size * 8);
  auto v = head;
  std::size_t line = 0;
  while (v) {
    auto h = v;
    while (h) {
      std::size_t idx = 0;
      for (std::size_t i = 1; i < N - 1; ++i) {
        for (std::size_t j = 1; j < N - 1; ++j)
          imageVec[line * 8 + idx] += h->tile[i * N + j];
        idx++;
      }
      h = h->right;
    }
    v = v->bottom;
    line++;
  }

  std::string image = "";
  for (const auto &x : imageVec)
    image += x;

  return std::make_tuple(image, imageVec[0].size());
}

std::string findMonsters(std::string &image, std::size_t M) {

  int count = 0;
  bool monsterFound = false;
  while (!monsterFound) {
    image = rotate(image, M);
    if (count++ == 4)
      image = flip(image, M);
    for (std::size_t i = 0; i < M - monsterH; ++i) {
      for (std::size_t j = 0; j < M - monsterW; ++j) {
        bool isMonster = true;
        for (std::size_t y = 0; y < monsterH; ++y)
          for (std::size_t x = 0; x < monsterW; ++x)
            if (monster[y * monsterW + x] == '#' &&
                image[(i + y) * M + j + x] != '#')
              isMonster = false;
        if (isMonster) {
          monsterFound = true;
          for (std::size_t y = 0; y < monsterH; ++y)
            for (std::size_t x = 0; x < monsterW; ++x)
              if (monster[y * monsterW + x] == '#')
                image[(i + y) * M + j + x] = 'O';
        }
      }
    }
  }

  return image;
}

int main() {
  auto contents = getFileContents("../input/Day20/input.txt");
  auto tiles = getTiles(split(contents, "\n\n"));
  auto edgeMap = getEdgeMap(tiles);

  auto [id, tile] = *tiles.begin();
  auto head = std::make_shared<Piece>(id, tile);
  fitPiece(head, tiles, edgeMap);

  auto [image, M] = getImage(head);
  auto monsters = findMonsters(image, M);

  auto s1 = getCornerProduct(head);
  long s2 = count_if(std::begin(monsters), std::end(monsters),
                     [](auto x) { return x == '#'; });

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
