#include <iostream>
#include <exception>

struct MyExp1 : /*virtual*/ std::exception {
};

struct MyExp2 : /*virtual*/ std::exception {
};

struct MyExp : MyExp1, MyExp2 {
};

int main() {
  try {
    throw MyExp1();
  } catch(std::exception const& e) {
    std::cout << "Caught std::exception: " << e.what() << std::endl;
  } catch( ... ) {
    std::cout << "Confused!" << std::endl;
  }
}
