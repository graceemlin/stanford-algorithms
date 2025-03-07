#include <bits/stdc++.h>

int solve(const std::vector<std::pair<double, double>> &coords,
          const int cities) {
  std::vector<bool> visited(cities, false);
  int curr_city{};
  int next_city{};
  double total_cost{};
  visited[0] = true;
  int seen = 1;
  while (seen < cities) {
    double min_cost = DBL_MAX;
    for (int j = 1; j < cities; ++j) {
      if (visited[j]) continue;
      auto &[x, y] = coords[curr_city];
      auto &[z, w] = coords[j];
      double curr_cost = sqrt(((x - z) * (x - z)) + ((y - w) * (y - w)));
      if (curr_cost < min_cost) {
        min_cost = curr_cost;
        next_city = j;
      }
    }

    total_cost += min_cost;
    visited[next_city] = true;
    curr_city = next_city;
    ++seen;
  }

  auto &[x, y] = coords[curr_city];
  auto &[z, w] = coords[0];
  total_cost += sqrt(((x - z) * (x - z)) + ((y - w) * (y - w)));

  return total_cost;
}

int main(int argc, char **argv) {
  std::ifstream file("nn.txt");
  int cities;
  file >> cities;
  int city;
  double x;
  double y;
  std::vector<std::pair<double, double>> coords;

  while (file >> city >> x >> y) {
    coords.push_back({x, y});
  }

  std::cout << solve(coords, cities) << std::endl;
  return 0;
}
