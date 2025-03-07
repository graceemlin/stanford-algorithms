#include <bits/stdc++.h>

int64_t job_scheduling(const std::vector<std::pair<double, double>> &job_list) {
  double completion_time{};
  double sum{};
  for (auto [weight, length] : job_list) {
    completion_time += length;
    sum += completion_time * weight;
  }

  return sum;
}

int main(int argc, char**) {
  std::ifstream file("jobs.txt");
  double job_count;
  file >> job_count;

  std::vector<std::pair<double, double>> job_list(job_count);
  double weight;
  double length;
  int job{};
  while (file >> weight >> length) {
    job_list[job++] = {weight, length};
  }

  auto diff_comparator = [&](std::pair<double, double> x,
                             std::pair<double, double> y) {
     if ((x.first - x.second) == (y.first - y.second)) {
      return x.first > y.first;
    } else {
      return (x.first - x.second) > (y.first - y.second);
    }
  };

  sort(job_list.begin(), job_list.end(), diff_comparator);
  std::cout << job_scheduling(job_list) << std::endl;

  auto ratio_comparator = [&](std::pair<double, double> x,
                              std::pair<double, double> y) {
    return (x.first / x.second) > (y.first / y.second);
  };

  sort(job_list.begin(), job_list.end(), ratio_comparator);
  std::cout << job_scheduling(job_list) << std::endl;

  return 0;
}
