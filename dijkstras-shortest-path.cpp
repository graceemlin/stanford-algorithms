#include <bits/stdc++.h>

void solve(std::map<int, std::vector<std::pair<int, int>>> &adjlist,
           const int vertices) {
  std::map<int, int64_t> distance_from_origin;
  for (int i = 0; i < vertices; ++i) {
    distance_from_origin[i] = INT_MAX;
  }

  std::priority_queue<std::pair<int, int64_t>, std::vector<std::pair<int, int64_t>>, std::greater<>> heap;
  heap.push({0, 0});
  distance_from_origin[0] = 0;

  while (!heap.empty()) {
    auto [curr_vertex, weight] = heap.top();
    heap.pop();

    for (auto [neighbor, distance_to_neighbor ]: adjlist[curr_vertex]) {
      int64_t new_weight = weight + distance_to_neighbor;
      if (distance_from_origin[neighbor] > new_weight) {
        distance_from_origin[neighbor] = new_weight;
        heap.push({neighbor, new_weight});
      }
    }
  }

  const int targets[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
  for (int target : targets) {
    std::cout << distance_from_origin[target - 1] << ",";
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  std::ifstream file("dijkstraData.txt");
  std::map<int, std::vector<std::pair<int, int>>> adjlist;
  std::string line;

  int src;
  int dest;
  int weight;
  while (std::getline(file, line)) {
    std::istringstream neighborhood(line);
    neighborhood >> src;

    char comma;
    while (neighborhood >> dest >> comma >> weight) {
      adjlist[src - 1].push_back({dest - 1, weight});
    }
  }

  const int vertices = 200;
  solve(adjlist, vertices);
  return 0;
}
