#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <iterator>
#include <cstring>

using namespace std;

vector<vector<int8_t>> grid; // store the input grid

typedef pair<int8_t,int8_t> Coordinates;
typedef function<vector<Coordinates>(const Coordinates)> MovesFinder;

// this method returns i and j of input value
Coordinates getCoordinates(const uint8_t value) {
    const uint8_t rows = grid.size();
    const uint8_t cols = grid[0].size();

    for (int8_t i = 0; i < rows; ++i) {
        for (int8_t j = 0; j < cols; ++j) {
            if (grid[i][j] == value) {
                return {i,j};
            }
        }
    }

    return {-1,-1};
}

// check whether an input coordinates is in board and not -1
bool isValidCell(const Coordinates& c) {
    const int8_t rows = grid.size();
    const int8_t cols = grid[0].size();

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

    const int8_t i = start.first;
    const int8_t j = start.second;

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

    const int8_t i = start.first;
    const int8_t j = start.second;
    uint8_t k = 0;
    uint8_t l = 0;
    const int8_t rows = grid.size();
    const int8_t cols = grid[0].size();

    while (k < rows && l < cols) {
        if (k != i && // can we choose to stay?
            abs(k-i) == abs(l-j) &&
            isValidCell({k,l})) {
            ret.push_back({k,l});
        }
        ++k;
        ++l;
    }

    return ret;
}

// get the number of valid phone numbers with different functions
uint32_t getNumbers(const uint8_t N,
                    const vector<uint8_t>& starts,
                    const MovesFinder& func) {
    // Algorithm: for example if we want to calculate
    // number of 7-digit valid phone numbers that Knight can generate starting from point 1, then
    // the total number of valid phone numbers should be the number of 6-digit
    // numbers starting from 8 + number of 6-digit numbers starting from 6.
    // Complexity: O(N) as we fill a matrix of dimension (N+1)*10 one cell a time.

    uint32_t mgrid[N+1][10]; // one extra row for digit 0

    for (uint8_t i = 0; i < N+1; ++i) {
        for (uint8_t j = 0; j < 10; ++j) {
            mgrid[i][j] = 0; // initial cell values are 0
        }
    }
    for (uint8_t i = 0; i < 10; ++i) {
        mgrid[1][i] = 1; // there's only 1-digit number at any point
    }

    function<uint32_t(const uint8_t,const Coordinates)> solve =
    [&](const uint8_t digits, const Coordinates& c) -> uint32_t {
        if (!digits || !isValidCell(c)) {
            return 0;
        }

        uint8_t value = grid[c.first][c.second];
        if (mgrid[digits][value] == 0) {
            vector<Coordinates> moves = func(c);
            if (moves.empty()) {
                return 0;
            }

            for (auto n : moves) {
                mgrid[digits][value] += solve(digits-1, n);
            }
        }

        return mgrid[digits][value];
    };

    uint32_t ret = 0;
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

        const uint32_t digits = atoi(numStr.c_str());
        if (!digits) {
            cerr << "Wrong number of digits!" << endl;
            continue;
        }

        cout << "space-separated valid starting digits: ";
        getline(cin, numStr);
        istringstream iss(numStr);
        vector<string> arr{istream_iterator<string>{iss}, istream_iterator<string>{}};
        vector<uint8_t> starts;
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

        const uint8_t rows = atoi(numStr.c_str());

        cout << "columns: ";
        getline(cin, numStr);
        if (!isValidNum(numStr, "Wrong number of colums!")) {
            continue;
        }

        const uint8_t cols = atoi(numStr.c_str());

        for (uint8_t i = 0; i < rows; ++i) {
            grid.push_back(vector<int8_t>());
            cout << "space-separated characters: ";
            getline(cin, numStr);
            istringstream iss2(numStr);
            vector<string> digits{istream_iterator<string>{iss2}, istream_iterator<string>{}};
            if (digits.size() != cols) {
                cerr << "Wrong row content!" << endl;
                restart = true;
                break;
            }

            for (uint8_t j = 0; j < cols; ++j) {
                if (digits[j].length() != 1) {
                    cerr << "Wrong row content!" << endl;
                    restart = true;
                    break;
                }
                char c = digits[j][0];
                grid.back().push_back(isdigit(c) ? atoi(&c) : -1);
            }
        }
        if (restart) {
            continue;
        }

        if (!strcasecmp(piece.c_str(), "knight")) {
            cout << "There are " << getNumbers(digits, starts, nextKnightMoves) << " " << digits << "-digit numbers." << endl;
        } else if (!strcasecmp(piece.c_str(), "bishop")) {
            cout << "There are " << getNumbers(digits, starts, nextBishopMoves) << " " << digits << "-digit numbers." << endl;
        }

        grid.clear();
    }
}
