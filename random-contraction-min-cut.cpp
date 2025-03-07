#include <bits/stdc++.h>

int find(std::vector<int> &root, int x) {
  if (root[x] == x) {
    return x;
  } else {
    return root[x] = find(root , root[x]);
  }
}

bool merge(std::vector<int> &root, std::vector<int> &rank, const int x, const int y) {
  const int x_root = find(root, x);
  const int y_root = find(root, y);
  if (x_root != y_root) {
    if (rank[x_root] < rank[y_root]) {
      root[x_root] = y_root;
    } else if (rank[x_root] > rank[y_root]) {
      root[y_root] = x_root;
    } else {
      root[y_root] = x_root;
      ++rank[x_root];
    }
    return true;
  } else {
    return false;
  }
}

int random_contraction(const std::vector<std::pair<int, int>> edge_list, int vertex_count, const int edge_count) {
  std::vector<int> rank(vertex_count, 0);
  std::vector<int> root(vertex_count);
  for (int i = 0; i < vertex_count; ++i) {
    root[i] = i;
  }

  while (vertex_count > 2) {
    const int random_cut = rand() % edge_count;
    const auto [x, y] = edge_list[random_cut];
    if (merge(root, rank, x, y)) {
      --vertex_count;
    }
  }

  int min_cut{};
  for (const auto [x, y] : edge_list) {
    if (find(root, x) != find(root, y)) {
      ++min_cut;
    }
  }

  return min_cut;
}

int main(int argc, char** argv) {
  std::ifstream file("kargerMinCut.txt");
  std::vector<std::pair<int, int>> edge_list;
  std::string line;
  int vertex_count{};
  int edge_count{};
  int src;
  int dest;
  while (std::getline(file, line)) {
    std::istringstream neighborhood(line);
    neighborhood >> src;
    ++vertex_count;
    
    while (neighborhood >> dest) {
      if (src < dest) {
	edge_list.push_back({src - 1, dest- 1});
	++edge_count;
      }
    }
  }

  int min_cut = INT_MAX;
  for (int i = 0; i < 1000; ++i) {
    min_cut = std::min(min_cut, random_contraction(edge_list, vertex_count, edge_count));
  }

  std::cout << min_cut << std::endl;
  
  return 0;
}
