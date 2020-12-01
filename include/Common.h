#ifndef COMMON_H
#define COMMON_H

#include <type_traits>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

std::string getFileContents(const std::string &fname) {
  std::ifstream infile(fname, std::ios::in | std::ios::binary);

  if (!infile) {
    std::cerr << "Failed to open file: " << fname << "\n";
    return std::string{};
  }
  std::string contents;
  infile.seekg(0, std::ios::end);
  contents.resize(infile.tellg());
  infile.seekg(0, std::ios::beg);
  infile.read(&contents[0], contents.size());
  infile.close();

  return contents;
}

template <typename T>
std::vector<std::string> split(const std::string &str, T&& delim) {
  std::size_t start;
  std::size_t end = 0;
  std::vector<std::string> strvec;

  while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
    end = str.find(delim, start);
    strvec.emplace_back(str.substr(start, end - start));
  }

  return strvec;
}

std::vector<std::string> getLines(const std::string &str) {
  return split(str, '\n');
}

std::vector<std::string> getWords(const std::string &str) {
  return split(str, ' ');
}

template <typename A, typename Fn,
          typename B = typename std::invoke_result<Fn, A>::type>
auto map(const std::vector<A> &a, Fn&& f) {
    auto res = std::vector<B>{};
    std::transform(std::begin(a), std::end(a), std::back_inserter(res), f);
    return res;
}

#endif
