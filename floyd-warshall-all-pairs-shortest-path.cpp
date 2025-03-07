#include <bits/stdc++.h>

void clear_matrix(std::vector<std::vector<int>> &matrix, const int vertex_count) {
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      if (i == j) {
        matrix[i][j] = 0;
      } else {
        matrix[i][j] = INT_MAX;
      }
    }
  }
}

void floyd_warshall(std::vector<std::vector<int>> &matrix, const int vertex_count) {
  for (int k = 0; k < vertex_count; ++k) {
    for (int i = 0; i < vertex_count; ++i) {
      for (int j = 0; j < vertex_count; ++j) {
        if (matrix[i][k] == INT_MAX || matrix[k][j] == INT_MAX) {
          continue;
        } else {
          matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
        }
      }
    }
  }

  for (int i = 0; i < vertex_count; ++i) {
    if (matrix[i][i] < 0) {
      std::cout << "negative cost cycle" << std::endl;
      return;
    }
  }

  int shortest_path = INT_MAX;
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      shortest_path = std::min(shortest_path, matrix[i][j]);
    }
  }

  std::cout << shortest_path << std::endl;
}

int main(int argc, char **argv) {
  std::ifstream file("g1.txt");
  int vertex_count;
  file >> vertex_count;
  int edge_count;
  file >> edge_count;

  int src;
  int dest;
  int weight;
  std::vector<std::vector<int>> matrix(vertex_count, std::vector<int>(vertex_count, INT_MAX));
  clear_matrix(matrix, vertex_count);
  while (file >> src >> dest >> weight) {
    matrix[src - 1][dest - 1] = weight;
  }
  floyd_warshall(matrix, vertex_count);

  std::ifstream file1("g2.txt");
  file1 >> vertex_count;
  file1 >> edge_count;
  clear_matrix(matrix, vertex_count);
  while (file1 >> src >> dest >> weight) {
    matrix[src - 1][dest - 1] = weight;
  }
  floyd_warshall(matrix, vertex_count);

  std::ifstream file2("g3.txt");
  file2 >> vertex_count;
  file2 >> edge_count;
  clear_matrix(matrix, vertex_count);
  while (file2 >> src >> dest >> weight) {
    matrix[src - 1][dest - 1] = weight;
  }
  floyd_warshall(matrix, vertex_count);

  return 0;
}
