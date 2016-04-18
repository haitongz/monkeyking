#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <iterator>
#include <cstring>
#include <map>

using namespace std;

typedef pair<int,int> Coordinates;
typedef function<vector<Coordinates>(const Coordinates)> MovesFinder;

vector<vector<int>> grid; // store the input grid
map<const uint,Coordinates> coors; // for looking up coordinates of a valid value, 10 keys at most

// this method returns i and j of input value
Coordinates getCoordinates(const uint value) {
    return coors.count(value) ? coors[value] : Coordinates(-1,-1);
}

// check whether an input coordinates is in board and not -1
bool isValidCell(const Coordinates& c) {
    const uint rows = grid.size();
    const uint cols = grid[0].size();

    return c.first >= 0 && c.first < rows &&
           c.second >= 0 && c.second < cols &&
           grid[c.first][c.second] != -1;
}

// To calculate how many valied N-digit phone numbers can be constructed
// starting from a collection of different points, we have to find all possible
// next moves of certain piece.

// get next moves for Knight to start
vector<Coordinates>
nextKnightMoves(Coordinates start) {
    if (!isValidCell(start))
        return {};

    vector<Coordinates> ret;

    // can it choose to stay or not?
    // ret.push_back(start);

    const int i = start.first;
    const int j = start.second;

    if (isValidCell({i+1,j+2})) {
        ret.push_back({i+1,j+2});
    }
    if (isValidCell({i+1,j-2})) {
        ret.push_back({i+1,j-2});
    }
    if (isValidCell({i-1,j+2})) {
        ret.push_back({i-1,j+2});
    }
    if (isValidCell({i-1,j-2})) {
        ret.push_back({i-1,j-2});
    }
    if (isValidCell({i+2,j+1})) {
        ret.push_back({i+2,j+1});
    }
    if (isValidCell({i+2,j-1})) {
        ret.push_back({i+2,j-1});
    }
    if (isValidCell({i-2,j+1})) {
        ret.push_back({i-2,j+1});
    }
    if (isValidCell({i-2,j-1})) {
        ret.push_back({i-2,j-1});
    }

    return ret;
}

// get next moves for Bishop to start
vector<Coordinates>
nextBishopMoves(Coordinates start) {
    if (!isValidCell(start))
        return {};

    vector<Coordinates> ret;

    const uint i = start.first;
    const uint j = start.second;
    uint k = 0;
    uint l = 0;
    const uint rows = grid.size();
    const uint cols = grid[0].size();

    for (uint k = 0; k < rows; ++k) {
        for (uint l = 0; l < cols; ++l) {
            int xdiff = k-i, ydiff = l-j;
            if (xdiff &&
                abs(xdiff) == abs(ydiff) &&
                isValidCell({k,l})) {
                ret.push_back({k,l});
            }
        }
    }

    return ret;
}

// get the number of valid phone numbers with different functions
uint getNumber(const uint N,
                   const vector<uint>& starts,
                   const MovesFinder& func) {
    // If we want to calculate the number of 7-digit valid phone numbers that
    // Knight/Bishop can generate starting from point, for example 1, then
    // it should be sum of number of valid 6-digit phone numbers starting from
    // 8 and number of 6-digit valid phone numbers starting from 6.
    // Complexity: O(N) as we fill a matrix of dimension (N+1)*10 one cell a time.

    uint mtable[N+1][10]; // one extra row for digit 0

    for (uint i = 0; i < N+1; ++i) {
        for (uint j = 0; j < 10; ++j) {
            mtable[i][j] = 0; // initial cell values are 0
        }
    }
    for (uint i = 0; i < 10; ++i) {
        mtable[1][i] = 1; // there's only 1-digit number at any point
    }

    function<uint(const uint,const Coordinates)> solve =
    [&](const uint digits, const Coordinates& c) -> uint {
        if (!digits) {
            return 0;
        }

        uint value = grid[c.first][c.second];
        if (!mtable[digits][value]) {
            vector<Coordinates> moves = func(c);
            for (auto n : moves) {
                mtable[digits][value] += solve(digits-1, n);
            }
        }

        return mtable[digits][value];
    };

    uint ret = 0;
    for (const auto s : starts) {
        Coordinates c = getCoordinates(s);
        ret += solve(N, c);
    }

    return ret;
}

bool isValidNum(const string& numStr, const string& errMsg) {
    if (numStr.empty()) {
        cerr << errMsg << endl;
        return false;
    }

    bool ret = true;

    for (const auto c : numStr) { // since atoi has undefined behavior with invalid strings, I have to do this, sigh
        if (!isdigit(c)) {
            cerr << errMsg << endl;
            ret = false;
            break;
        }
    }

    return ret;
}

int main(int argc, char** argv) {
    while (true) {
        cout << "piece: ";
        string piece;
        getline(cin, piece);
        if (strcasecmp(piece.c_str(), "knight") && strcasecmp(piece.c_str(), "bishop")) {
            cerr << "Wrong piece!" << endl;
            continue;
        }

        string numStr; // variable used to read input numbers
        cout << "number length: ";
        getline(cin, numStr);
        if (!isValidNum(numStr, "Wrong number of digits!")) {
            continue;
        }

        const uint digits = atoi(numStr.c_str());
        if (!digits) {
            cerr << "Wrong number of digits!" << endl;
            continue;
        }

        cout << "space-separated valid starting digits: ";
        getline(cin, numStr);
        istringstream iss(numStr);
        vector<string> arr{istream_iterator<string>{iss}, istream_iterator<string>{}};
        vector<uint> starts;
        bool restart = false;

        for (const auto& i : arr) {
            if (!isdigit(i[0]) ||
                (digits == 7 && (i == "0" || i == "1"))) {
                cerr << "Wrong starting numbers!" << endl;
                restart = true;
                break;
            }

            starts.push_back(atoi(i.c_str()));
        }
        if (restart) {
            continue;
        }

        cout << "rows: ";
        getline(cin, numStr);
        if (!isValidNum(numStr, "Wrong number of rows!")) {
            continue;
        }

        const uint rows = atoi(numStr.c_str());

        cout << "columns: ";
        getline(cin, numStr);
        if (!isValidNum(numStr, "Wrong number of colums!")) {
            continue;
        }

        const uint cols = atoi(numStr.c_str());

        for (uint i = 0; i < rows; ++i) {
            grid.push_back(vector<int>());
            cout << "space-separated characters: ";
            getline(cin, numStr);
            istringstream iss2(numStr);
            vector<string> digits{istream_iterator<string>{iss2}, istream_iterator<string>{}};
            if (digits.size() != cols) {
                cerr << "Wrong row content!" << endl;
                restart = true;
                break;
            }

            for (uint j = 0; j < cols; ++j) {
                if (digits[j].length() != 1) {
                    cerr << "Wrong row content!" << endl;
                    restart = true;
                    break;
                }

                if (isdigit(digits[j][0])) {
                    uint value = atoi(digits[j].c_str());
                    grid.back().push_back(value);
                    coors[value] = {i,j};
                } else {
                    grid.back().push_back(-1);
                }
            }
        }
        if (restart) {
            continue;
        }

        if (!strcasecmp(piece.c_str(), "knight")) {
            cout << "There are " << getNumber(digits, starts, nextKnightMoves) << " " << digits << "-digit numbers." << endl;
        } else if (!strcasecmp(piece.c_str(), "bishop")) {
            cout << "There are " << getNumber(digits, starts, nextBishopMoves) << " " << digits << "-digit numbers." << endl;
        }

        grid.clear();
    }
}
