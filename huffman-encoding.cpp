#include <bits/stdc++.h>

int main(int argc, char** argv) {
  std::ifstream file("huffman.txt");
  int symbol_count;
  file >> symbol_count;
  std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<>> symbols;
  int weight;
  while (file >> weight) {
    symbols.push({weight, 0, 0});
  }

  while (symbols.size() > 1) {
    auto [weight1, depth1, min_depth1] = symbols.top();
    symbols.pop();
    auto [weight2, depth2, min_depth2] = symbols.top();
    symbols.pop();
    int new_weight = weight1 + weight2;
    int new_depth = std::max(depth1, depth2) + 1;
    int new_min_depth = std::min(min_depth1, min_depth2) + 1;
    symbols.push({new_weight, new_depth, new_min_depth});
  }

  auto [total_weight, max_depth, min_depth] = symbols.top();
  std::cout << max_depth << std::endl;
  std::cout << min_depth << std::endl;
}
