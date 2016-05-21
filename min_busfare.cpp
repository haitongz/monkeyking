#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <functional>
#include <iterator>

using namespace std;

static const uint DAILY = 2;
static const uint WEEKLY = 7;

vector<uint> validDays(const vector<string>& days) { // utility method to get valid days in a month
  if (days.empty())
    return {};

  set<uint> ret;

  for (const auto& s : days) {
    if (s.empty() ||
        s.length() > 2 ||
        !isdigit(s[0]) ||
        (s.length() == 1 && s[0] == '0') ||
        (s.length() == 2 && !isdigit(s[1]))) {
      cerr << "Invalid day: " << s << endl;
      continue;
    }

    uint day = atoi(s.c_str());
    if (day > 31) {
      cerr << "Invalid day: " << day << endl;
      return {};
    } else {
      ret.insert(day);
    }
  }

  return {ret.begin(), ret.end()};
}

uint minBusFare(const vector<uint>& days) {
  const uint n = days.size();
  if (n < 4) {
    return n*DAILY;
  }

  // this method finds window that's most days in same week ending at day idx
  function<pair<int,uint>(const uint)> window =
    [&](const uint idx) -> pair<int,uint> {
    int i = idx-1;
    uint len = 1;

    while (i >= 0 && days[idx]-days[i] < 7) {
      ++len;
      --i;
    }

    return {i, len}; // i can be -1
  };

  uint ret = 0;

  function<void(const int)> solve = [&](const int idx) {
    if (idx < 0) {
      return;
    }

    pair<int,uint> win = window(idx);
    uint len = win.second; // number of days in same week
    int next = idx-1;

    if (len <= 3) { // not worth buying a weekly pass
      ret += DAILY;
    } else if (len == 7) { // optimization: no left-side window can be bigger
      ret += WEEKLY;
      next = idx-7;
    } else {
      next = win.first;
      if (next < 0) { // optimization: cannot shift left anymore
        ret += WEEKLY;
        return;
      }

      for (uint j = idx-1; j > next; --j) {
        pair<int,uint> j_win = window(j);
        if (j_win.second > len) { // choose a week that covers more days than current one
          next = j;
          for (uint l = idx; l > j; --l) {
            ret += DAILY;
          }
          break;
        } else if (j_win.first < 0) { // optimization: cannot shift left anymore
          break;
        }
      }

      if (next == win.first) { // no previous week covers more days than current one
        ret += WEEKLY;
      }
    }

    solve(next);
  };

  solve(n-1);

  return ret;
}

int main(int argc, char** argv)
{
  while (true) {
    cout << "Space-separated days that you have to take bus: ";
    std::string line;
    getline(cin, line);
    istringstream iss(line);
    vector<string> arr{istream_iterator<string>{iss}, istream_iterator<string>{}};

    vector<uint> days = validDays(arr);
    if (days.empty()) {
      continue;
    }

    cout << "Minimum bus fare is: " << minBusFare(days) << endl;
  }
}
