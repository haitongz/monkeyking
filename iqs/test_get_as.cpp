#include <iostream>
#include <type_traits>

template <typename C>
class X {
public:
  template <typename T, typename std::enable_if<!std::is_same<double,T>::value>::type* = nullptr>
  void get() {
    std::cout << "get as T" << std::endl;
  }

  template <typename T, typename std::enable_if<std::is_same<double,T>::value>::type* = nullptr>
  void get() {
    std::cout << "get as double" << std::endl;
  }
};

int main(int argc, char** argv) {
  X<int> d;
  d.get<double>();

  return 0;
}
