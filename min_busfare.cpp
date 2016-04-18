/*
Daily pass costs $2 and Weekly pass consts $7. Given days in a month that you have to take bus, find minimum bus fare.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <functional>
#include <iterator>

using namespace std;

static const uint DAILY = 2;
static const uint WEEKLY = 7;

vector<uint> getValidDays(const vector<string>& strs) {
    if (strs.empty())
        return {};

    set<uint> ret;

    for (const auto& s : strs) {
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

pair<int,uint> biggestWindow(const vector<uint>& days, const uint idx) {
    int i = idx-1;
    uint len = 1;

    while (i >= 0 && days[idx]-days[i] < 7) {
        ++len;
        --i;
    }

    return {i,len}; // i can be -1
}

uint minBusFare(const vector<uint>& days) {
    const uint n = days.size();
    if (n < 4) {
        return n*DAILY;
    }

    uint ret = 0;

    function<void(const int)> solve = [&](const int idx) {
        if (idx < 0) {
            return;
        }

        pair<int,uint> win = biggestWindow(days, idx);
        uint len = win.second; // length of biggest window
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
                pair<int,uint> win2 = biggestWindow(days, j);
                if (win2.second > len) {
                    next = j;
                    for (uint l = idx; l > j; --l) {
                        ret += DAILY;
                    }
                    break;
                } else if (win2.first < 0) { // optimization: cannot shift left anymore
                    break;
                }
            }

            if (next == win.first) {
                ret += WEEKLY;
            }
        }

        solve(next);
    };

    solve(n-1);

    return ret;
}

int main(int argc, char** argv) {
    while (true) {
        cout << "Space-separated days that you have to take bus: ";
        std::string line;
        getline(cin, line);
        istringstream iss(line);
        vector<string> arr{istream_iterator<string>{iss}, istream_iterator<string>{}};

        vector<uint> days = getValidDays(arr);
        if (days.empty()) {
            continue;
        }

        cout << "Minimum bus fare is: " << minBusFare(days) << endl;
    }
}
