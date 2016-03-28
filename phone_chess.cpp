#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <iterator>
#include <cstring>

using namespace std;

vector<vector<int8_t>> grid;

typedef pair<int8_t,int8_t> Coordinates;

Coordinates getCoordinates(const uint8_t value) {
    const uint8_t rows = grid.size();
    const uint8_t cols = grid[0].size();

    for (int8_t i = 0; i < rows; ++i) {
        for (int8_t j = 0; i < cols; ++j) {
            if (grid[i][j] == value) {
                return {i,j};
            }
        }
    }

    return {-1,-1};
}

bool isValid(const Coordinates& c) {
    const int8_t rows = grid.size();
    const int8_t cols = grid[0].size();

    return c.first >= 0 && c.first < rows &&
           c.second >= 0 && c.second < cols &&
           grid[c.first][c.second] != -1;
}

vector<Coordinates>
nextKnightMoves(Coordinates start) {
    if (!isValid(start))
        return {};

    vector<Coordinates> ret;

    // can it choose to stay or not?
    // ret.push_back(start);

    const int8_t i = start.first;
    const int8_t j = start.second;

    if (isValid({i+1,j+2})) {
        ret.push_back({i+1,j+2});
    }
    if (isValid({i+1,j-2})) {
        ret.push_back({i+1,j-2});
    }
    if (isValid({i-1,j+2})) {
        ret.push_back({i-1,j+2});
    }
    if (isValid({i-1,j-2})) {
        ret.push_back({i-1,j-2});
    }
    if (isValid({i+2,j+1})) {
        ret.push_back({i+2,j+1});
    }
    if (isValid({i+2,j-1})) {
        ret.push_back({i+2,j-1});
    }
    if (isValid({i-2,j+1})) {
        ret.push_back({i-2,j+1});
    }
    if (isValid({i-2,j-1})) {
        ret.push_back({i-2,j-1});
    }

    return ret;
}

vector<Coordinates>
nextBishopMoves(Coordinates start) {
    if (!isValid(start))
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
            isValid({k,l})) {
            ret.push_back({k,l});
        }
        ++k;
        ++l;
    }

    return ret;
}

uint32_t getNumbers(const uint8_t totalDigits, const vector<uint8_t>& starts, function<vector<Coordinates>(const Coordinates)> func) {
    uint32_t mgrid[totalDigits+1][10]; // one extra row for digit 0

    for (uint8_t i = 0; i <= totalDigits; ++i) {
        for (uint8_t j = 0; j < 10; ++j) {
            mgrid[i][j] = 0;
        }
    }
    for (uint8_t i = 0; i < 10; ++i) {
        mgrid[1][i] = 1;
    }

    function<uint32_t(const uint8_t,const Coordinates)> solve =
    [&](const uint8_t digits, const Coordinates& c) -> uint32_t {
        if (!digits) {
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
        ret += solve(totalDigits, c);
    }

    return ret;
}

int main(int argc, char** argv) {
    while (true) {
        cout << "piece: ";
        string piece;
        getline(cin, piece);

        cout << "number length: ";
        string totalDigits;
        getline(cin, totalDigits);

        cout << "space-separated valid starting digits: ";
        string tmp;
        getline(cin, tmp);
        istringstream iss(tmp);
        vector<string> arr{istream_iterator<string>{iss}, istream_iterator<string>{}};
        vector<uint8_t> starts;
        for (const auto& i : arr) {
            if (!isdigit(i[0]) ||
                (totalDigits == "7" && (i == "0" || i == "1"))) {
                cerr << "Wrong starting digit!" << endl;
                return -1;
            }

            starts.push_back(atoi(i.c_str()));
        }

        cout << "rows: ";
        getline(cin, tmp);
        const uint8_t rows = atoi(tmp.c_str());
        if (rows <= 0) {
            cerr << "Wrong row number!" << endl;
            return -1;
        }

        cout << "columns: ";
        getline(cin, tmp);
        const uint8_t cols = atoi(tmp.c_str());
        if (cols <= 0) {
            cerr << "Wrong column number!" << endl;
            return -1;
        }

        for (uint8_t i = 0; i < rows; ++i) {
            grid.push_back(vector<int8_t>());
            cout << "space-separated characters: ";
            getline(cin, tmp);
            istringstream iss2(tmp);
            vector<string> digits{istream_iterator<string>{iss2}, istream_iterator<string>{}};
            if (digits.size() != cols) {
                cerr << "Wrong row content!" << endl;
                return -1;
            }

            for (uint8_t j = 0; j < cols; ++j) {
                if (digits[j].length() != 1) {
                    cerr << "Wrong row content!" << endl;
                    return -1;
                }
                char c = digits[j][0];
                grid.back().push_back(isdigit(c) ? atoi(&c) : -1);
            }
        }

        if (!strcasecmp(piece.c_str(), "knight")) {
            cout << "There are " << getNumbers(atoi(totalDigits.c_str()), starts, nextKnightMoves) << " " << totalDigits << "-digit numbers." << endl;
        } else if (!strcasecmp(piece.c_str(), "bishop")) {
            cout << "There are " << getNumbers(atoi(totalDigits.c_str()), starts, nextBishopMoves) << " " << totalDigits << "-digit numbers." << endl;
        } else {
            cerr << "Invalid piece!" << endl;
        }

        grid.clear();
    }
}
