#include <bits/stdc++.h>

int main(int argc, char** argv) {
  std::ifstream file("algo1-programming_prob-2sum.txt");
  int64_t element;
  std::vector<int64_t> elements;
  while (file >> element) {
    elements.push_back(element);
  }

  int result{};
  std::unordered_set<int64_t> exists(elements.begin(), elements.end());
  for (int64_t target = -10000; target <= 10000; ++target) {
    for (int64_t element: elements) {
      int64_t complement = target - element;
      if ((complement != element) && (exists.find(complement) != exists.end())) {
        ++result;
        break;
      }
    }
  }

  std::cout << result << std::endl;
  return 0;
}
