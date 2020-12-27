# Advent of Code 2020
My solutions for AoC2020 done in C++. Requires C++17.

## Building and running

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make -j
```

```bash
for day in {1..25}; do echo "Day ${day}"; ./bin/Day${day}; done
```
