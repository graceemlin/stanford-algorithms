#include <bits/stdc++.h>

int main(int argc, char** argv) {
  std::ifstream file("edges.txt");
  int vertex_count;
  file >> vertex_count;
  int edge_count;
  file >> edge_count;

  std::map<int, std::vector<std::pair<int, int>>> adjlist;
  int src;
  int dest;
  int weight;
  int edge{};
  while (file >> src >> dest >> weight) {
    adjlist[src - 1].push_back({dest - 1, weight});
    adjlist[dest - 1].push_back({src - 1, weight});
  }

  std::vector<bool> visited(vertex_count, false);
  std::priority_queue<std::tuple<int, int, int>,
                      std::vector<std::tuple<int, int, int>>, std::greater<>>
      heap;

  for (auto [dest, weight] : adjlist[0]) {
      heap.push({weight, 0, dest});
  }
  visited[0] = true;

  int64_t sum{};
  while (!heap.empty()) {
    auto [weight, src, dest] = heap.top();
    heap.pop();

    if (visited[dest] == false) {
      visited[dest] = true;
      sum += weight;
      for (auto [neighbor, weight] : adjlist[dest]) {
        if (!visited[neighbor]) {
          heap.push({weight, dest, neighbor});
        }
      }
    } else {
      continue;
    }
  }

  std::cout << sum << std::endl;
  return 0;
}
