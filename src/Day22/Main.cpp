#include "Common.h"

#include <deque>
#include <unordered_map>

enum class Winner : bool {
  Player1 = false,
  Player2 = true,
};

auto getDeckString(const std::deque<long> &deck) {
  std::string str = "";
  for (const auto &card : deck)
    str += std::to_string(card);

  return str;
}

auto combat(std::deque<long> player1, std::deque<long> player2,
            std::unordered_map<std::string, bool> hands1,
            std::unordered_map<std::string, bool> hands2,
            const bool recursive = false) {
  while (!player1.empty() && !player2.empty()) {
    auto &played1 = hands1[getDeckString(player1)];
    auto &played2 = hands2[getDeckString(player2)];
    if (played1 && played2)
      return std::tuple<Winner, std::deque<long>>(Winner::Player1, player1);

    long unsigned card1 = player1.front();
    long unsigned card2 = player2.front();
    player1.pop_front();
    player2.pop_front();
    played1 = true;
    played2 = true;

    if (card1 <= player1.size() && card2 <= player2.size() && recursive) {
      std::deque<long> newDeck1(player1.begin(), player1.begin() + card1);
      std::deque<long> newDeck2(player2.begin(), player2.begin() + card2);
      auto &&[win, deck] = combat(newDeck1, newDeck2, hands1, hands2);
      if (win == Winner::Player1) {
        player1.push_back(card1);
        player1.push_back(card2);
      } else {
        player2.push_back(card2);
        player2.push_back(card1);
      }
    } else {
      if (card1 > card2) {
        player1.push_back(card1);
        player1.push_back(card2);
      } else if (card2 > card1) {
        player2.push_back(card2);
        player2.push_back(card1);
      }
    }
  }

  if (player2.empty())
    return std::tuple<Winner, std::deque<long>>(Winner::Player1, player1);
  return std::tuple<Winner, std::deque<long>>(Winner::Player2, player2);
}

long run(std::deque<long> player1, std::deque<long> player2, bool recursive) {
  std::unordered_map<std::string, bool> hands1;
  std::unordered_map<std::string, bool> hands2;

  auto [win, deck] = combat(player1, player2, hands1, hands2, recursive);

  long sum = 0l;
  long idx = deck.size();
  for (const auto &card : deck)
    sum += card * idx--;
  return sum;
}

int main() {
  auto contents = getFileContents("../input/Day22/input.txt");
  auto player1Str = getLines(split(contents, "\n\n")[0]);
  auto player2Str = getLines(split(contents, "\n\n")[1]);
  auto player1 = std::deque<long>();
  auto player2 = std::deque<long>();
  std::transform(std::begin(player1Str) + 1, std::end(player1Str),
                 std::back_inserter(player1),
                 [](auto x) { return std::stol(x); });
  std::transform(std::begin(player2Str) + 1, std::end(player2Str),
                 std::back_inserter(player2),
                 [](auto x) { return std::stol(x); });

  auto s1 = run(player1, player2, false);
  auto s2 = run(player1, player2, true);
  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
