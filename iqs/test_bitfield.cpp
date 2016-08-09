#include <iostream>

using namespace std;

/* define simple structure */
struct {
  uint widthValidated;
  uint heightValidated;
} status1;

/* define a structure with bit fields */
struct {
  uint widthValidated : 1;
  uint heightValidated : 1;
} status2;

int main(int argc, char** argv) {
  cout << "Memory size occupied by status1 : " << sizeof(status1) << endl;
  cout << "Memory size occupied by status2 : " << sizeof(status2) << endl;

  return 0;
}
