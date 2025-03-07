#include <bits/stdc++.h>

int main(int argc, char** argv) {
  std::ifstream file("mwis.txt");
  int vertices;
  file >> vertices;
  int weight;
  std::vector<int> graph;
  while (file >> weight) {
    graph.push_back(weight);
  }

  int dp[vertices + 1];
  dp[0] = 0;
  dp[1] = graph[0];
  for (int i = 2; i <= vertices; ++i) {
    dp[i] = std::max(dp[i - 1], dp[i - 2] + graph[i - 1]);
  }

  char mwis_contains[vertices + 1];
  int current_vertex = vertices;
  while (current_vertex > 0) {
    if (dp[current_vertex - 2] + graph[current_vertex - 1] >
        dp[current_vertex - 1]) {
      mwis_contains[current_vertex--] = '1';
      mwis_contains[current_vertex--] = '0';
    } else {
      mwis_contains[current_vertex--] = '0';
    }
  }

  int targets[8] = {1, 2, 3, 4, 17, 117, 517, 997};
  for (int target : targets) {
    std::cout << mwis_contains[target] << " ";
  }
  std::cout << std::endl;
}
