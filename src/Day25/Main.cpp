#include "Common.h"

long getLoopSize(long subject, long target) {
  long loopSize = 0;
  long value = 1;
  while (value != target) {
    value = value * subject;
    value = value % 20201227;
    loopSize++;
  }

  return loopSize;
}

long handshake(long subject, long loopSize) {
  long value = 1;
  for (long i = 0; i < loopSize; ++i) {
    value = value * subject;
    value = value % 20201227;
  }
  return value;
}

int main() {
  auto contents = getFileContents("../input/Day25/input.txt");
  auto card = std::stol(getLines(contents)[0]);
  auto door = std::stol(getLines(contents)[1]);
  auto doorLoops = getLoopSize(7, door);
  auto key = handshake(card, doorLoops);

  std::cout << key << "\n";
}
