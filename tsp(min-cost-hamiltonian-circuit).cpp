#include <bits/stdc++.h>

double tsp(const std::vector<std::vector<double>> &cost,
           std::vector<std::vector<double>> &memo, const int target_mask,
           int curr_mask, int curr_city, const int cities) {
  if (curr_mask == target_mask) {
    return cost[curr_city][0];
  }
  if (memo[curr_mask][curr_city] != -1) {
    return memo[curr_mask][curr_city];
  }
  double result = DBL_MAX;
  for (int i = 0; i < cities; ++i) {
    if ((curr_mask & (1 << i)) == 0) {
      result = std::min(result, cost[curr_city][i] + tsp(cost, memo, target_mask, curr_mask | (1 << i), i, cities));
    }
  }
  return memo[curr_mask][curr_city] = result;
}

int solve(const std::vector<std::pair<double, double>> &coords,
          const int cities) {

  std::vector<std::vector<double>> cost(cities,
                                            std::vector<double>(cities, 0));
  for (int i = 0; i < cities; ++i) {
    for (int j = 0; j < cities; ++j) {
      if (cost[i][j]) continue;
      auto &[x, y] = coords[i];
      auto &[z, w] = coords[j];
      cost[i][j] = cost[j][i] = sqrt(((x - z) * (x - z)) + ((y - w) * (y - w)));
    }
  }
  std::vector<std::vector<double>> memo((1 << cities), std::vector<double>(cities, -1));
  const int target_mask = (1 << cities) - 1;
  int curr_mask = 1;
  int curr_city{};
  return std::floor(tsp(cost, memo, target_mask, curr_mask, curr_city, cities));
}


int main(int argc, char **argv) {
  std::ifstream file("tsp.txt");
  int cities;
  file >> cities;
  double x;
  double y;
  std::vector<std::pair<double, double>> coords;

  while (file >> x >> y) {
    coords.push_back({x, y});
  }

  std::cout << solve(coords, cities) << std::endl;
  return 0;
}
