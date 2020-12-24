#include <algorithm>
#include <array>
#include <list>



// template <typename T>
// class CircularList {
// public:
//   class iterator {
//   public:
//     iterator(typename std::vector<T>::iterator it, 
//              typename std::vector<T>::iterator begin, 
//              typename std::vector<T>::iterator end) :
//       it(it), begin(begin), end(end), size(0ul) {}
//     iterator operator++() {
//       if (it + 1 == end)
//         it = begin;
//       else
//         ++it;
//       size += 1;
//       return *this;
//     }
//     iterator operator++(int) {
//       iterator tmp = *this;
//       if (it + 1 == end)
//         it = begin;
//       else
//         ++it;
//       size += 1;
//       return tmp;
//     }
//     iterator operator+(const std::size_t i) {
//       std::size_t length = end - begin;
//       std::size_t start = it - begin;
//       it = begin + ((start + i) % length);
//       size += i;
//       return *this;
//     }
//     T& operator*() { return *it; }
//     bool operator==(const iterator& rhs) { 
//       return (it != rhs.it || size == 0) && end - begin != 0;
//     }
//     bool operator!=(const iterator& rhs) {
//       return (it != rhs.it || size == 0) && end - begin != 0;
//     }
//   private:
//     typename std::vector<T>::iterator it;
//     typename std::vector<T>::iterator begin;
//     typename std::vector<T>::iterator end;
//     std::size_t size;
//   };
// 
//   template <typename... Args>
//   CircularList(Args&&... args) : buffer{ std::forward<Args>(args)... } { }
// 
//   T& operator[](std::size_t n) { return buffer[wrapIdx(n)]; }
//   const T& operator[](std::size_t n) const { return buffer[wrapIdx(n)]; }
// 
//   auto begin() { return iterator(buffer.begin(), buffer.begin(), buffer.end()); }
//   auto end() { return iterator(buffer.begin(), buffer.begin(), buffer.end()); }
// 
// private:
//   std::vector<T> buffer;
//   std::size_t idx;
//   std::size_t wrapIdx(std::size_t idx) {
//     return (idx - buffer.size()) % buffer.size();
//   }
// };

int main() {
}
//  std::vector<unsigned long> cups = {6, 8, 5, 9, 7, 4, 2, 1, 3};
  std::list<unsigned long> cups = {3, 8, 9, 1, 2, 5, 4, 6, 7};

//  for (const auto &x : cups)
//    std::cout << x << " ";
//  std::cout << "\n";
//  std::size_t s = 1;
//  std::size_t s_n = s + 3;
//  std::size_t d = 4;
//  std::rotate(std::begin(cups) + 2, std::begin(cups) + 5, std::begin(cups) + 9);
//  for (const auto &x : cups)
//    std::cout << x << " ";
//  std::cout << "\n";

//  std::size_t idx = 0ul;
//  for (int rounds = 0; rounds < 10; ++rounds) {
//    auto cup = cups[idx];
//    auto idx1 = (idx + 1) % cups.size();
//    auto idx2 = (idx + 2) % cups.size();
//    auto idx3 = (idx + 3) % cups.size();
//    std::vector<unsigned long> three = {cups[idx1], cups[idx2], cups[idx3]};
//    std::vector<unsigned long> copy = cups;
//
//    std::cout << "-- move " << rounds << "--\n";
//    std::cout << "cups:";
//    for (const auto &x : cups) {
//      std::cout << " ";
//      if (x == cups[idx])
//        std::cout << "(";
//      std::cout << x;
//      if (x == cups[idx])
//        std::cout << ")";
//    }
//    std::cout << "\n";
//
//    auto dest = cups[idx];
//    auto loc = cups.end();
//    do {
//      dest = (dest - 1 + cups.size()) % cups.size();
//      loc = std::find(std::begin(cups), std::end(cups), dest);
//    } while (std::find(std::begin(three), std::end(three), dest) != std::end(three));
//
//    std::cout << "pick up: ";
//    for (const auto &x : three)
//      std::cout << x << ", ";
//    std::cout << "\n";
//    std::cout << "destination: " << dest << "\n\n";
//
//    idx = (idx + 1) % cups.size();
//  }


//  std::size_t idx = 0ul;
//  for (int i = 0; i < 10; ++i) {
//    std::cout << "-- move " << i << "--\n";
//    std::cout << "cups:";
//    for (const auto &x : cups) {
//      std::cout << " ";
//      if (x == cups[idx])
//        std::cout << "(";
//      std::cout << x;
//      if (x == cups[idx])
//        std::cout << ")";
//    }
//    std::cout << "\n";
//    auto &cup1 = cups[(idx + 1) % N];
//    auto &cup2 = cups[(idx + 2) % N];
//    auto &cup3 = cups[(idx + 3) % N];
//
//    std::size_t destIdx = 0ul;
//    for (std::size_t off = 1; off < 9; ++off) {
//      auto label = ((cups[idx] - off) + N) % N;
//      for (std::size_t x = 0; x < cups.size(); ++x) {
//        if (label == cups[x]) {
//          destIdx = x;
//          break;
//        }
//      }
//      if (cups[destIdx] != cup1 && cups[destIdx] != cup2 && cups[destIdx] != cup3)
//        break;
//    }
//
//    auto dest = cups[destIdx];
//
//    std::cout << "pick up: " << cup1 << ", " << cup2 << ", " << cup3 << "\n";
//    std::cout << "destination: " << dest << "\n\n";
//
//    for (std::size_t j = destIdx; j != (idx + 1) % N; j = ((j - 1) + N) % N)
//      std::swap(cups[j], cups[((j - 1) + N) % N]);
//    for (std::size_t j = destIdx; j != (idx + 2) % N; j = ((j - 1) + N) % N)
//      std::swap(cups[j], cups[((j - 1) + N) % N]);
//    for (std::size_t j = destIdx; j != (idx + 3) % N; j = ((j - 1) + N) % N)
//      std::swap(cups[j], cups[((j - 1) + N) % N]);
////    cups.erase(std::begin(cups) + 1, std::begin(cups) + 4);
////    auto it = std::find(std::begin(cups), std::end(cups), dest);
////    cups.insert(it + 1, cup1);
////    cups.insert(it + 2, cup2);
////    cups.insert(it + 3, cup3);
//    idx = (idx + 1) % N;
//  }
//  
//    std::cout << "-- final --\n";
//    std::cout << "cups:";
//    for (const auto &x : cups) {
//      std::cout << " ";
//      if (x == cups[idx])
//        std::cout << "(";
//      std::cout << x;
//      if (x == cups[idx])
//        std::cout << ")";
//    }
//    std::cout << "\n";
// }
