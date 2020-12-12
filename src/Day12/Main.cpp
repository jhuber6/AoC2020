#include "Common.h"

#include <cmath>
#include <tuple>

int main() {
  auto lines = getLines(getFileContents("../input/Day12/input.txt"));
  auto moves = std::vector<std::tuple<char, long>>(lines.size());
  auto parse = [](const std::string &line) {
    auto move = line[0];
    auto amount = std::stol(line.substr(1, line.size() - 1));
    return std::tuple<char, long>(move, amount);
  };
  std::transform(std::begin(lines), std::end(lines), std::begin(moves), parse);

  long xPos = 0;
  long yPos = 0;
  long angle = 0;
  for (const auto &[move, amount] : moves) {
    if (move == 'N')
      yPos += amount;
    else if (move == 'S')
      yPos -= amount;
    else if (move == 'E')
      xPos += amount;
    else if (move == 'W')
      xPos -= amount;
    else if (move == 'L')
      angle = (angle + amount) % 360;
    else if (move == 'R')
      angle = (angle + (360 - amount)) % 360;
    else if (move == 'F') {
      xPos += amount * static_cast<long>(std::round(std::cos(
                           static_cast<double>(angle) * M_PI / 180.0)));
      yPos += amount * static_cast<long>(std::round(std::sin(
                           static_cast<double>(angle) * M_PI / 180.0)));
    }
  }

  auto s1 = std::abs(xPos) + std::abs(yPos);

  long xPosW = 10;
  long yPosW = 1;
  long xPosS = 0;
  long yPosS = 0;
  for (const auto &[move, amount] : moves) {
    if (move == 'N')
      yPosW += amount;
    else if (move == 'S')
      yPosW -= amount;
    else if (move == 'E')
      xPosW += amount;
    else if (move == 'W')
      xPosW -= amount;
    else if (move == 'L') {
      if (amount == 90) {
        std::swap(xPosW, yPosW);
        xPosW = -xPosW;
      }
      if (amount == 180) {
        xPosW = -xPosW;
        yPosW = -yPosW;
      }
      if (amount == 270) {
        std::swap(xPosW, yPosW);
        yPosW = -yPosW;
      }
    } else if (move == 'R') {
      if (360 - amount == 90) {
        std::swap(xPosW, yPosW);
        xPosW = -xPosW;
      }
      if (360 - amount == 180) {
        xPosW = -xPosW;
        yPosW = -yPosW;
      }
      if (360 - amount == 270) {
        std::swap(xPosW, yPosW);
        yPosW = -yPosW;
      }
    } else if (move == 'F') {
      xPosS += amount * xPosW;
      yPosS += amount * yPosW;
    }
  }

  auto s2 = std::abs(xPosS) + std::abs(yPosS);

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
