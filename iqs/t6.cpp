#include <iostream>

int main() {
int x[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' }; 

int *ptr, y; 

ptr  = x + 4; 

y = ptr - x;
std::cout << y << std::endl;
}
