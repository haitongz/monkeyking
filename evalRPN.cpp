#include <iostream>
#include <stack>

using namespace std;

/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 */
int32_t evalRPN(const vector<string>& tokens) {
  const uint32_t n = tokens.size();
  if (!n)
    throw exception();

  function<bool(const string&)> isnum =
    [&](const string& digit) {
    const uint32_t len = digit.length();
    if (len < 1)
      return false;

    if ((digit[0] == '-' && len > 1) || // negative number
        (digit[0] >= '0' && digit[0] <= '9')) // positive number
      return true;

    return false;
  };

  stack<int32_t> operands;

  for (uint32_t i = 0; i < n; ++i) {
    const string& s = tokens[i];
    if (isnum(s)) {
      operands.push(atoi(s.c_str()));
      continue;
    }

    int32_t op1 = operands.top();
    operands.pop();
    int32_t op2 = operands.top();
    operands.pop();

    if (s == "+")
      operands.push(op2+op1);
    if (s == "-")
      operands.push(op2-op1);
    if (s == "*")
      operands.push(op2*op1);
    if (s == "/")
      operands.push(op2/op1);
  }

  return operands.top();
}

/*
Parse a formula string (only contains "+-()", no '*\/').
For example,
5 + 2x - ( 3y + 2x - ( 7 - 2x) - 9 ) = 3 + 4y
Parse this string, with a given float of 'x' value, output a float for 'y' value.
 */
double parse(const string& f, double x) {
  double sum_y_left = 0, sum_y_right = 0;
  double sum_num_left = 0, sum_num_right = 0;
  double *cur_sum_y = &sum_y_left, *cur_sum_num = &sum_num_left;
  int last_op = 1, bracket_op = 1;
  stack<int> brackets;

  for (int i = 0; i <= f.size(); ++i) {
    char c = f[i];
    if (f[i] >= '0' && f[i] <= '9') {
      int over = i+1;
      while (f[over] >= '0' && f[over] <= '9')
        ++over;

      double number = atoi(f.substr(i, over-i).c_str()) * last_op * bracket_op;
      if (f[over] == 'x') {
        *cur_sum_num += number * x;
        i = over;
      } else if (f[over] == 'y') {
        *cur_sum_y += number;
        i = over;
      } else {
        *cur_sum_num += number;
        i = over-1;
      }
    } else if (c == 'x') {
      *cur_sum_num += last_op * bracket_op * x;
    } else if (c == 'y') {
      *cur_sum_y += last_op * bracket_op;
    } else if (c == '(') {
      brackets.push(last_op);
      bracket_op *= last_op;
      last_op = 1;
    } else if (c == ')') {
      bracket_op /= brackets.top();
      brackets.pop();
    } else if (c == '+' || c == '-') {
      last_op = c == '+' ? 1 : -1;
    } else if (c == '=' || c == '\0') {
      cur_sum_num = &sum_num_right;
      cur_sum_y = &sum_y_right;
      last_op = 1;
      brackets = stack<int>();
    }
  }

  return (sum_num_right-sum_num_left)/(sum_y_left-sum_y_right);
}

int main(int argc, char** argv) {
  cout << evaluate("x - (y - (5 + 3y)) = 3y + 2x - 1", 2) << endl;
  cout << evaluate("5 + 2x - ( 3y + 2x - ( 7 - 2x) - 9 ) = 3 + 4y", 2) << endl;
  cout << evaluate("2y-(y+5)=3y+6", 2) << endl;
  cout << evaluate("10x + y = 2y - 10", 2) << endl;
  cout << evaluate("x + 5 + y = 2y - 3x - 10", 2) << endl;

  vector<string> v;
  v.push_back(string("2"));
  v.push_back(string("1"));
  v.push_back(string("+"));
  v.push_back(string("3"));
  v.push_back(string("*"));
  cout << evalRPN(v) << endl;

  v.clear();
  v.push_back(string("4"));
  v.push_back(string("13"));
  v.push_back(string("5"));
  v.push_back(string("/"));
  v.push_back(string("+"));
  cout << evalRPN(v) << endl;

  return 0;
}
