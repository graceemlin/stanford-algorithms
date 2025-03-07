#include <bits/stdc++.h>

int small_knapsack(std::vector<std::pair<int, int>> &value_and_weights,
                   const int size, const int items) {
  std::vector<std::vector<int>> dp(items + 1, std::vector<int>(size + 1, 0));

  for (int i = 1; i <= items; ++i) {
    for (int remaining_capacity = 0; remaining_capacity <= size; ++remaining_capacity) {
      auto [curr_value, curr_weight] = value_and_weights[i - 1];
      if (curr_weight > remaining_capacity) {
        dp[i][remaining_capacity] = dp[i - 1][remaining_capacity];
      } else {
        dp[i][remaining_capacity] = std::max(dp[i - 1][remaining_capacity], dp[i - 1][remaining_capacity - curr_weight] + curr_value);
      }
    }
  }

  return dp[items][size];
}

int64_t big_knapsack(
    std::vector<std::pair<int64_t, int64_t>> &value_and_weights,
    int64_t remaining_capacity, int64_t items,
    std::map<std::pair<int64_t, int64_t>, int64_t> &cache) {
  if (items < 0) {
    return 0;
  }

  if (cache.find({items, remaining_capacity}) != cache.end()) {
    return cache[{items, remaining_capacity}];
  }

  auto [curr_weight, curr_value] = value_and_weights[items];
  if (remaining_capacity < curr_weight) {
    big_knapsack(value_and_weights, remaining_capacity, items - 1, cache);
    } else {
    cache[{items, remaining_capacity}] = std::max(big_knapsack(value_and_weights, remaining_capacity, items - 1, cache), (big_knapsack(value_and_weights, remaining_capacity - curr_weight, items - 1, cache) + curr_value));
  }

  return cache[{items, remaining_capacity}];
}

int main(int argc, char **argv) {
  std::ifstream file("knapsack1.txt");
  int size;
  file >> size;
  int items;
  file >> items;
  int item;
  int weight;
  std::vector<std::pair<int, int>> value_and_weights;
  int curr_val{};
  while (file >> item >> weight) {
    value_and_weights.push_back({item, weight});
  }

  std::cout << small_knapsack(value_and_weights, size, items) << std::endl;

  std::ifstream big_file("knapsack_big.txt");
  int64_t big_size;
  big_file >> big_size;
  int64_t big_items;
  big_file >> big_items;
  int64_t big_item;
  int64_t big_weight;
  std::vector<std::pair<int64_t, int64_t>> big_value_and_weights;
  int64_t big_curr_val{};
  while (big_file >> big_item >> big_weight) {
    big_value_and_weights.push_back({big_weight, big_item});
  }

  sort(big_value_and_weights.begin(), big_value_and_weights.end());

  std::map<std::pair<int64_t, int64_t>, int64_t> cache;
  std::cout << big_knapsack(big_value_and_weights, big_size, big_items - 1, cache) << std::endl;

  return 0;
}
