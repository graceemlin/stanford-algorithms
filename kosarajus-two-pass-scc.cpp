#include <bits/stdc++.h>

void dfs1(int vertex, std::map<int, std::vector<int>> &adjlist, std::vector<int> &relabel, std::map<int, bool> &visited) {
  visited[vertex] = true;
  for (int neighbor : adjlist[vertex]) {
    if (!visited[neighbor]) {
      dfs1(neighbor, adjlist, relabel, visited);
    }
  }
  
  relabel.push_back(vertex);
}

void dfs2(int vertex, int &scc_size, std::map<int, std::vector<int>>& reversed, std::map<int, bool> &visited) {
  ++scc_size;
  visited[vertex] = true;
  for (int neighbor : reversed[vertex]) {
    if (!visited[neighbor]) {
      dfs2(neighbor, scc_size, reversed, visited);
    }
  }
}

void solve(std::map<int, std::vector<int>> &adjlist, std::map<int, std::vector<int>> &reversed, const int n) {
  std::map<int, bool> visited;
  std::vector<int> relabel;
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs1(i, adjlist, relabel, visited);
    }
  }

  visited.clear();
  
  reverse(relabel.begin(), relabel.end());

  std::vector<int> result;
  for (int i = 0; i < n; ++i) {
    if (!visited[relabel[i]]) {
      int scc_size{};
      dfs2(relabel[i], scc_size, reversed, visited);
      result.push_back(scc_size);
    }
  }

  sort(result.rbegin(), result.rend());

  for (int i = 0; i < 5; ++i) {
    std::cout << result[i] << ' ';
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  std::ifstream file("SCC.txt");
  std::map<int, std::vector<int>> adjlist;
  std::map<int, std::vector<int>> reversed;
  int src;
  int dst;
  while (file >> src >> dst) {
    adjlist[src - 1].push_back(dst - 1);
    reversed[dst - 1].push_back(src - 1);
  }

  const int n = 875714;
  solve (adjlist, reversed, n);
  
  return 0;
}
