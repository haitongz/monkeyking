/*
Implement int sqrt(int x).

Follow up:
Can you implement double sqrt(double x)?
*/
#include <iostream>

using namespace std;

int sqrt(int x) {
  if (x <= 0)
    return 0;

  int32_t target = x, left = 1, right = x;
  while (left <= right) {
    int32_t mid = left + (right-left)/2;
    if (mid*mid <= target && (mid+1)*(mid+1) > target)
      return mid;
    if (mid*mid > target)
      right = mid-1;
    else if (mid*mid < target)
      left = mid+1;
  }

  return 0;
}

double sqrt(double x) {
  if (x <= 0)
    return 0;

  double l = 0, r = x;
  if (r < 1)
    r = 1;

  double mid = (l+r)/2.0;
  while (fabs(mid*mid-x) > 1e-5) {
    if (mid*mid > x)
      r = mid;
    else
      l = mid;

    mid = (l+r)/2.0;
  }

  return mid;
}

double sqrt_newton(double v) {
  double x, nx = 1;
  while (abs(nx-x) > 1e-5) {
    x = nx;
    nx = (v/x + x) / 2;
  }
  return nx;
}

int main(int argc, char** argv) {
}
