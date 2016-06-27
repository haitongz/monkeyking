#include <iostream>
#include <functional>
#include <stack>
#include <set>
#include <map>

using namespace std;

/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 */
int evaluate(const string tokens[], const uint n) {
  if (!n) {
    cerr << "Invalid argument!" << endl;
    exit(1);
  }

  function<bool(const string&)> isnum =
    [&](const string& str) {
    const uint len = str.length();
    if (!len)
      return false;

    uint i = (str[0] == '-') ? 1 : 0;

    for (; i < len; ++i) {
      if (!isdigit(str[i])) {
        return false;
      }
    }

    return true;
  };

  stack<int> operands;

  for (uint i = 0; i < n; ++i) {
    const string& s = tokens[i];
    if (isnum(s)) {
      operands.push(atoi(s.c_str()));
    } else {
      int op1 = operands.top(); // this appears second
      operands.pop();
      int op2 = operands.top(); // this appears first
      operands.pop();

      if (s == "+") {
        operands.push(op2+op1);
      } else if (s == "-") {
        operands.push(op2-op1);
      } else if (s == "*") {
        operands.push(op2*op1);
      } else if (s == "/") {
        operands.push(op2/op1);
      } else {
        cerr << "Unsupported operator!" << endl;
        exit(1);
      }
    }
  }

  return operands.top();
}

/*
Convert RPN to Infix
 */
struct Entry {
  string expr;
  string op;
};

bool precedenceLess(const string& lhs, const string& rhs, bool assoc) {
  static const map<string,uint> KNOWN({{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}});
  static const set<string> ASSOCIATIVE({"+", "*"});
  return (KNOWN.count(lhs) ? KNOWN.find(lhs)->second : 0) <
         (KNOWN.count(rhs) ? KNOWN.find(rhs)->second : 0) + (assoc && !ASSOCIATIVE.count(rhs) ? 1 : 0);
}

void parenthesize(Entry& old, const string& token, bool assoc) {
  if (!old.op.empty() && precedenceLess(old.op, token, assoc))
    old.expr = '(' + old.expr + ')';
}

void addToken(stack<Entry>& stk, const string& token) {
  if (token.find_first_of("0123456789") != string::npos)
    stk.push(Entry({token, string()})); // it's a number
  else { // it's an operator
    if (stk.size() < 2) {
      cerr << "Stack underflow!" << endl;
      exit(1);
    }

    auto rhs = stk.top();
    parenthesize(rhs, token, false);
    stk.pop();
    auto lhs = stk.top();
    parenthesize(lhs, token, true);
    stk.top().expr = lhs.expr + ' ' + token + ' ' + rhs.expr;
    stk.top().op = token;
  }
}

string rpn2Infix(const string& src) {
  stack<Entry> stk;

  for (auto start = src.begin(), p = src.begin(); ; ++p) {
    if (p == src.end() || *p == ' ') {
      if (p > start)
        addToken(stk, string(start, p));
      if (p == src.end())
        break;

      start = p+1;
    }
  }

  if (stk.size() != 1) {
    cerr << "Incomplete expression!" << endl;
    exit(1);
  }

  return stk.top().expr;
}

int main(int argc, char** argv) {
  string a[] = {"2","1","+","3","*"};
  cout << evaluate(a, 5) << endl;
  string b[] = {"4","13","5","/","+"};
  cout << evaluate(b, 5) << endl;

  cout << rpn2Infix("3 4 2 * 1 5 - 2 3 ^ ^ / +") << "\n";
  cout << rpn2Infix("1 2 + 3 4 + ^ 5 6 + ^") << "\n";

  return 0;
}
