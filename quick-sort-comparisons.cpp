#include <bits/stdc++.h>

enum pivot_type {
  first,
  median,
  last
};
  
int median_of_three(const std::vector<int64_t> &elements, int l, int r) {
  int m = (l + r) / 2;

  if (elements[l] > elements[m]) std::swap(l, m);
  if (elements[m] > elements[r]) std::swap(r, m);
  if (elements[l] > elements[m]) std::swap(l, m);
  
  return m;
}

int find_pivot(const std::vector<int64_t> &elements, int l, int r, pivot_type pivot) {
  switch (pivot) {
  case first :
    return l;
  case last :
    return r;
  default:
    return median_of_three(elements, l, r);
  }
}

int partition(std::vector<int64_t> &elements, int curr_pivot, int end) {
  int curr_pivot_value = elements[curr_pivot];
  int start = curr_pivot + 1;
  int new_pivot = start;

  for (int i = start; i <= end; ++i) {
    if (elements[i] < curr_pivot_value) {
      std::swap(elements[i], elements[new_pivot++]);
    }
  }

  std::swap(elements[curr_pivot], elements[--new_pivot]);

  return new_pivot;
}

int64_t quicksort(std::vector<int64_t> &elements, int l, int r, pivot_type pivot) {
  if (l >= r) {
    return 0;
  }

  int curr_pivot = find_pivot(elements, l, r, pivot);
  std::swap(elements[l], elements[curr_pivot]);
  int new_pivot = partition(elements, l, r);
  
  int64_t comparisons = r - l;
  comparisons += quicksort(elements, l, new_pivot - 1, pivot);
  comparisons += quicksort(elements, new_pivot + 1, r, pivot);
  return comparisons;
}

void solve(const std::vector<int64_t> &elements, int l, int r) {
  std::vector<int64_t> e1 = elements;
  std::vector<int64_t> e2 = elements;
  std::vector<int64_t> e3 = elements;
  std::cout << quicksort(e1, l, r, first) << std::endl;
  std::cout << quicksort(e2, l, r, last) << std::endl;
  std::cout << quicksort(e3, l, r, median) << std::endl;
}

int main(int argc, char **argv) {
  std::ifstream file("QuickSort.txt");
  int element;

  const int n = 10000;
  std::vector<int64_t> elements(n);
  int i{};
  while (file >> element) {
    elements[i] = element;
    ++i;
  }

  solve(elements, 0, n - 1);
  
  return 0;
}
