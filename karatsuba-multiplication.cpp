#include <bits/stdc++.h>

std::string string_add(std::string x, std::string y) {
  if (x.size() > y.size()) {
    swap(x, y);
  }

  int y_ptr = y.size() - 1;
  int x_ptr = x.size() - 1;
  std::string result = "";
  int carry{};
  while (x_ptr >= 0) {
    int sum = (x[x_ptr--] - '0') + (y[y_ptr--] - '0') + carry;
    result.push_back((sum % 10) + '0');
    carry = sum / 10;
  }

  while (y_ptr >= 0) {
    int sum = (y[y_ptr--] - '0') + carry;
    result.push_back((sum % 10) + '0');
    carry = sum / 10;
  }

  if (carry) {
    result.push_back(carry + '0');
  }
  
  std::reverse(result.begin(), result.end());
  
  return result;
}

std::string karatsuba(const std::string &x, const std::string &y, int n) {
  if (n < 5) {
    return std::to_string(std::stoi(x) * std::stoi(y));
  }
  
  std::string a = x.substr(0,  n / 2);
  std::string b = x.substr(n / 2);
  std::string c = y.substr(0, n / 2);
  std::string d = y.substr(n / 2);

  // (10 ^ n) * ac
  std::string ac = karatsuba(a, c, n / 2);
  for (int i = 0; i < n; ++i) {
    ac += "0";
  }

  // + (10 ^ (n / 2)) * (ad + bc)
  std::string adbc = string_add(karatsuba(a, d, n / 2), karatsuba(b, c, n / 2));
  for (int i = 0; i < n / 2; ++i) {
    adbc += "0";
  }

  // + bd
  std::string bd = karatsuba(b, d, n / 2);

  // = x * y
  return string_add(string_add(ac, adbc), bd);
}

int main(int argc, char** argv) {
  std::string x = "3141592653589793238462643383279502884197169399375105820974944592";
  std::string y = "2718281828459045235360287471352662497757247093699959574966967627";

  std::cout << karatsuba(x, y, x.length()) << std::endl;

  return 0;
}
