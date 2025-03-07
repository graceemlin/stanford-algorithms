#include <bits/stdc++.h>

int main(int argc, char** argv) {
  std::ifstream file("Median.txt");
  int element;

  const int mod = 10000;
  int result{};
  int elements{};
  std::priority_queue<int> max_heap;
  std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;

  while (file >> element) {
    max_heap.push(element);
    min_heap.push(max_heap.top());
    max_heap.pop();
    if (max_heap.size() < min_heap.size()) {
      max_heap.push(min_heap.top());
      min_heap.pop();
    }
    result += max_heap.top();
    result %= mod;
    ++elements;
  }

  std::cout << result << std::endl;
  return 0;
}
