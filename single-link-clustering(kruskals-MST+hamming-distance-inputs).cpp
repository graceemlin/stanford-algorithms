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
    } else if (rank[x_root] > rank[y_root]){
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

void solve(std::vector<std::tuple<int, int, int>> &edge_list, const int vertex_count, const int target) {
  std::vector<int> rank(vertex_count, 0);
  std::vector<int> root(vertex_count);
  for (int i = 0; i < vertex_count; ++i) {
    root[i] = i;
  }

  auto weight_sort = [&](std::tuple<int, int, int> x, std::tuple<int, int, int> y) {
    return std::get<2>(x) < std::get<2>(y);
      };
  std::sort(edge_list.begin(), edge_list.end(), weight_sort);
  int edge{};
  int groups = 10000;
  while (groups > target) {
    auto [x, y, weight] = edge_list[edge];
    groups -= merge(root, rank, x, y);
    ++edge;
  }

  edge = 0;
  auto [x, y, weight] = edge_list[edge];
  int x_root = find(root, x);
  int y_root = find(root, y);
  while (x_root == y_root) {
    ++edge;
    auto [x, y, weight] = edge_list[edge];
    x_root = find(root, x);
    y_root = find(root, y);
  }

  std::cout << std::get<2>(edge_list[edge - 1]) << std::endl;
}

void solve1(const std::vector<std::string> &hamming_list, const int vertex_count,
            const int length) {
  std::map<std::string, int> key_to_index;
  for (int i = 0; i < vertex_count; ++i) {
    key_to_index.insert({hamming_list[i], i});
  }

  std::vector<int> rank(vertex_count, 0);
  std::vector<int> root(vertex_count);
  for (int i = 0; i < vertex_count; ++i) {
    root[i] = i;
  }

  int groups = vertex_count;
  for (int i = 0; i < vertex_count; ++i) {
    std::string curr_key = hamming_list[i];
    if (key_to_index.find(curr_key) != key_to_index.end() && key_to_index[curr_key] != i) {
      groups -= merge(root, rank, key_to_index[curr_key], i);
    }

    for (int j = 0; j < length; ++j) {
      std::string curr_key_1 = curr_key;
      curr_key_1[j] = ((curr_key_1[j] - '0') ^ 1) + '0';
      if (key_to_index.find(curr_key_1) != key_to_index.end()) {
        groups -= merge(root, rank, key_to_index[curr_key_1], i);
      }

      for (int k = j + 1; k < length; ++k) {
        std::string curr_key_2 = curr_key_1;
        curr_key_2[k] = ((curr_key_2[k] - '0') ^ 1) + '0';
        if (key_to_index.find(curr_key_2) != key_to_index.end()) {
          groups -= merge(root, rank, key_to_index[curr_key_2], i);
        }
      }
    }
  }

  std::cout << groups << std::endl;
}


int main(int argc, char** argv) {
  std::ifstream file("clustering1.txt");
  std::vector<std::tuple<int, int, int>> edge_list;
  std::string line;

  int src;
  int dest;
  int weight;
  std::set<int> vertices;
  while (file >> src >> dest >> weight) {
    edge_list.push_back({src - 1, dest - 1, weight});
    vertices.insert(src - 1);
    vertices.insert(dest - 1);
  }

  const int target = 4;
  solve(edge_list, vertices.size(), target);

  std::ifstream big_file("clustering_big.txt");
  int vertex_count;
  int length;
  big_file >> vertex_count;
  big_file >> length;
  std::vector<std::string> hamming_list(vertex_count);
  char bit;
  for (int i = 0; i < vertex_count; ++i) {
    std::string key;
    for (int j = 0; j < length; ++j) {
      big_file >> bit;
      key += bit;
    }
    hamming_list[i] = key;
  }

  solve1(hamming_list, vertex_count, length);
  return 0;
}
