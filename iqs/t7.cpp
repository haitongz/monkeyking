#include <iostream>

int main() {
  int A[4][2]={0};
  std::string sz = std::to_string(sizeof(A));
  std::cout << sz << std::endl;
}
