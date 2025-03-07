#include <bits/stdc++.h>

void merge(std::vector<int> &elements, int l, int m, int r, int64_t& inversions) {
  int i = l;
  int j = m + 1;
  int k{};
  
  std::vector<int> temp(r - l + 1);
  while (i <= m && j <= r) {
    if (elements[i] <= elements[j]) {
      temp[k++] = elements[i++];
    } else {
      inversions += m - i + 1;
      temp[k++] = elements[j++];
    }
  }

  while (i <= m) {
    temp[k++] = elements[i++];
  }

  while (j <= r) {
    temp[k++] = elements[j++];
  }

  for (int fill = l; fill <= r; ++fill) {
    elements[fill] = temp[fill - l];
  }
}

void solve(std::vector<int> &elements, int l, int r, int64_t& inversions) {
  if (l >= r) {
    return;
  }
  
  int m = (l + r) / 2;
  solve(elements, l, m, inversions);
  solve(elements, m + 1, r, inversions);
  merge(elements, l, m, r, inversions);
}

int main(int argc, char** argv) {
  std::ifstream file("IntegerArray.txt");
  int element;

  const int n = 100000;
  std::vector<int> elements(n);
  
  int i{};
  while (file >> element) {
    elements[i] = element;
    ++i;
  }

  int64_t inversions{};
  solve(elements, 0, n - 1, inversions);
  
  std::cout << inversions << std::endl;

  return 0;
}
