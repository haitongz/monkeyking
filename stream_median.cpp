/*
Create the data structure for a component that will receive a series of numbers over the time and, when asked,
returns the median of all received elements.

Note:
Might need to find the median multiple times. Median is the middle element in an odd length sorted array,
and in the even case it's the average of the middle elements.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class OnlineMedian {
  public:
    void add(const int32_t num) {
      if (max_heap.empty() || max_heap[0] > num) {
        max_heap.push_back(num);

        push_heap(max_heap.begin(), max_heap.end());

        if (max_heap.size() > min_heap.size()) {
          pop_heap(max_heap.begin(), max_heap.end());
          min_heap.push_back(max_heap.back());
          push_heap(min_heap.begin(), min_heap.end(), greater<int32_t>());
          max_heap.pop_back();
        }
      } else if (max_heap[0] <= num) {
        min_heap.push_back(num);
        push_heap(min_heap.begin(), min_heap.end(), greater<int32_t>());

        if (min_heap.size() > max_heap.size() && (min_heap.size()-max_heap.size() > 1)) {
          pop_heap(min_heap.begin(), min_heap.end(), greater<int32_t>());
          max_heap.push_back(min_heap.back());
          push_heap(max_heap.begin(), max_heap.end());
          min_heap.pop_back();
        }
      }
    }
    double getMedian() const {
      if (min_heap.empty())
        return 0;
      if (min_heap.size() == max_heap.size()) {
        return ((double)min_heap[0]+(double)max_heap[0])/2;
      } else {
        return min_heap[0];
      }
    }
private:
    vector<int32_t> max_heap, min_heap;
};
int main(int argc, char** argv) {
  OnlineMedian strm;
  strm.add(1);
  cout << strm.getMedian() << endl; // should be 1

  strm.add(5);
  strm.add(10);
  strm.add(12);
  strm.add(2);
  cout << strm.getMedian() << endl; // should be 5

  strm.add(3);
  strm.add(8);
  strm.add(9);
  cout << strm.getMedian() << endl; // should be 6.5

  return 0;
}
