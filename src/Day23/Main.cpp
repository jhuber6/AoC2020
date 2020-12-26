#include <array>
#include <unordered_map>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>

template <typename T> class CircularBuffer {
public:
  class Node {
  public:
    T data;
    std::shared_ptr<Node> next;
  };

  CircularBuffer(std::initializer_list<T> list)
      : head(nullptr), size(list.size()) {
    if (!list.size())
      return;

    head = std::make_shared<Node>();
    head->data = *list.begin();
    std::shared_ptr<Node> last = head;
    for (auto it = list.begin() + 1; it != list.end(); ++it) {
      last->next = std::make_shared<Node>();
      last = last->next;
      last->data = *it;
    }

    last->next = head;
  }

  void append() {
    auto end = head;
    for (end = head; end->next != head; end = end->next)
      ;
    for (int i = 10; i <= 1000000; ++i, ++size) {
      end->next = std::make_shared<Node>();
      end = end->next;
      end->data = i;
    }
    end->next = head;
  }

  std::shared_ptr<Node> head;
  std::size_t size;
};

void runGame(CircularBuffer<long> &cups, int numRounds, long maxVal) {
  std::unordered_map<long, std::shared_ptr<CircularBuffer<long>::Node>> cache;
  cache.reserve(maxVal);

  cache[cups.head->data] = cups.head;
  for (auto loc = cups.head; loc->next != cups.head; loc = loc->next)
    cache[loc->next->data] = loc->next;

  for (int rounds = 0; rounds < numRounds; ++rounds) {
    std::array<long, 3> three = {cups.head->next->data,
                                 cups.head->next->next->data,
                                 cups.head->next->next->next->data};

    auto dest = cups.head->data;
    do {
      if (--dest == 0)
        dest = maxVal;
    } while (std::find(std::begin(three), std::end(three), dest) !=
             std::end(three));

    auto &loc = cache[dest];
    auto start = cups.head->next;
    cups.head->next = start->next->next->next;
    start->next->next->next = loc->next;
    loc->next = start;

    cups.head = cups.head->next;
  }

  while (cups.head->data != 1)
    cups.head = cups.head->next;
  cups.head = cups.head->next;
}

int main() {
  CircularBuffer<long> cups = {6, 8, 5, 9, 7, 4, 2, 1, 3};

  runGame(cups, 100, 9);
  for (auto node = cups.head; node->next != cups.head; node = node->next)
    std::cout << node->data;
  std::cout << "\n";

  cups = {6, 8, 5, 9, 7, 4, 2, 1, 3};
  cups.append();
  runGame(cups, 10000000, 1000000);
  std::cout << cups.head->data * cups.head->next->data << "\n";
}
