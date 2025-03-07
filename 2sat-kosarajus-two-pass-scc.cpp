#include <bits/stdc++.h>

void dfs1(int vertex, std::map<int, std::vector<int>> &adjlist,
          std::vector<int> &relabel, std::map<int, bool> &visited) {
  visited[vertex] = true;
  for (int neighbor : adjlist[vertex]) {
    if (!visited[neighbor]) {
      dfs1(neighbor, adjlist, relabel, visited);
    }
  }
  relabel.push_back(vertex);
}

void dfs2(int vertex, int &scc, std::map<int, std::vector<int>> &reversed,
          std::map<int, bool> &visited, std::map<int, int> &result) {
  visited[vertex] = true;
  result[vertex] = scc;
  for (int neighbor : reversed[vertex]) {
    if (!visited[neighbor]) {
      dfs2(neighbor, scc, reversed, visited, result);
    }
  }
}

int solve(std::map<int, std::vector<int>> &adjlist, std::map<int, std::vector<int>> &reversed, const int n) {
  std::map<int, bool> visited;
  std::vector<int> relabel;
  for (int i = 0; i < 2 * n; ++i) {
    if (!visited[i]) {
      dfs1(i, adjlist, relabel, visited);
    }
  }

  visited.clear();

  reverse(relabel.begin(), relabel.end());

  std::map<int, int> result;
  int scc{};
  for (int i = 0; i < 2 * n; ++i) {
    if (!visited[relabel[i]]) {
      dfs2(relabel[i], scc, reversed, visited, result);
      ++scc;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (result[i] == result[i + n]) {
      return 0;
    }
  }

  return 1;
}

int main(int argc, char **argv) {
  std::string filestr = "2sat";
  for (int i = 0; i < 6; ++i) {
    std::string filename = filestr;
    filename += i + '1';
    filename += ".txt";
    std::ifstream file(filename);
    std::map<int, std::vector<int>> adjlist;
    std::map<int, std::vector<int>> reversed;
    int number;
    file >> number;
    int src;
    int dst;
    while (file >> src >> dst) {
      if (src > 0 && dst > 0) {
        adjlist[src + number - 1].push_back(dst - 1);
        adjlist[dst + number - 1].push_back(src - 1);
        reversed[dst - 1].push_back(src + number - 1);
        reversed[src - 1].push_back(dst + number - 1);
      } else if (src > 0 && dst < 0) {
        adjlist[src + number - 1].push_back(number - dst - 1);
        adjlist[-dst - 1].push_back(src - 1);
        reversed[number - dst - 1].push_back(src + number - 1);
        reversed[src - 1].push_back(-dst - 1);
      } else if (src < 0 && dst > 0) {
        adjlist[-src - 1].push_back(dst - 1);
        adjlist[dst + number - 1].push_back(number - src - 1);
        reversed[dst - 1].push_back(-src - 1);
        reversed[number - src - 1].push_back(dst + number - 1);
      } else {
        adjlist[-src - 1].push_back(number - dst - 1);
        adjlist[-dst - 1].push_back(number - src - 1);
        reversed[number - dst - 1].push_back(-src - 1);
        reversed[number - src - 1].push_back(-dst - 1);
      }
    }

    std::cout << solve(adjlist, reversed, number);
  }
  std::cout << std::endl;

  return 0;
}
