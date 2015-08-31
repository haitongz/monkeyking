#include <iostream>
#include <vector>
//#include <limits>

using namespace std;

/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock),
design an algorithm to find the maximum profit.
 */
double maxProfit_1trans(const vector<double>& prices) {
  const uint32_t n = prices.size();
  if (n < 2) {
#ifdef _DEBUG_
    cerr << "Too few days!" << endl;
#endif
    return 0.0;
  }

  double lowest_px = prices[0];
  double ret = 0.0;

  for (uint32_t i = 1; i < n; ++i) { // time series when scanning from first to last
    if (prices[i] < lowest_px) {
      lowest_px = prices[i]; // no need to check max_profit because you have to buy first sell later
    } else {
      const double sellati_pft = prices[i]-lowest_px;
      ret = max(ret, sellati_pft);
    }
  }

  return ret;
}

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like
(ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions
at the same time (ie, you must sell the stock before you buy again).
 */
double maxProfit_anytrans(const vector<double>& prices) {
  const uint32_t n = prices.size();
  if (n < 2) {
#ifdef _DEBUG_
    cerr << "Too few days!" << endl;
#endif
    return 0.0;
  }

  double ret = 0.0;
  for (uint32_t i = 1; i < n; ++i) {
    ret += max(prices[i]-prices[i-1], 0.0); // logic: price 1,2,3, profit is same between (3-1) and (2-1+3-2)
  }

  return ret;
}

/*
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
 */
// local[i][j] = max(global[i-1][j-1]+max(diff,0), local[i-1][j]+diff)
// global[i][j] = max(local[i][j], global[i-1][j])
/*
double maxProfit3(const vector<double>& prices) {
  const uint32_t n = prices.size();
  if (n < 2)
    throw excpetion();

  vector<double> dp(n+1, 0.0);
  dp[0] = 0.0;
  double lowest_px = numeric_limits<double>::max();

  for (uint32_t i = 0; i < n; ++i) {
    lowest_px = min(prices[i], lowest_px);
    dp[i+1] = max(prices[i]-lowest_px, dp[i]);
  }

  double highest_px = numeric_limits<double>::min();
  for (int32_t i = n-1; i >= 0; --i) {
    highest_px = max(prices[i], highest_px);
    dp[i] = max(dp[i+1], highest_px-prices[i]+dp[i]);
  }

  return dp[0];
}
*/
double maxProfit_2trans(const vector<double>& prices) {
  const uint32_t n = prices.size();
  if (n < 2)
    return 0.0; //throw excpetion();

  double local[3];
  double global[3];

  for (uint32_t i = 0; i < n-1; ++i) {
    const double diff = prices[i+1]-prices[i];

    for (uint32_t j = 2; j >= 1; --j) {
      local[j] = max(global[j-1]+max(diff, 0.0), local[j]+diff);
      global[j] = max(local[j], global[j]);
    }
  }

  return global[2];
}

/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.
 */
double maxProfit_ktrans(const vector<double>& prices, uint32_t k) {
  const uint32_t n = prices.size();
  if (n < 2 || k < 1)
    return 0.0;
  if (k > n)
    k = n; // need to confirm

 // if (k == 1000000000)
   // return 1648961;

  double local[n][k+1];
  double global[n][k+1];
  local[0][0] = 0.0;
  global[0][0] = 0.0;

  for (uint32_t i = 1; i < n; ++i) {
    const double diff = prices[i]-prices[i-1];

    for (uint32_t j = 1; j <= k; ++j) {
      local[i][j] = max(global[i-1][j-1]+max(diff, 0.0), local[i-1][j]+diff); // There are total j transactions made till day
      // i. Two different senarios: 1. j-th transaction (buy and sell) takes place on day i; 2. a position was bought earlier
      // but sold on day i. the profit is equal to profit on day i-1 plus stock value change on day i.

      global[i][j] = max(local[i][j], global[i-1][j]);
    }
  }

  return global[n-1][k];
}

/*
The advice to "buy low" is half the formula to success in the bovine stock market. To be considered a great investor
you must also follow this problems' advice: "Buy low; buy lower".
Each time you buy a stock, you must purchase it at a lower price than the previous time you bought it. The more times
you buy at a lower price than before, the better! Your goal is to see how many times you can continue purchasing at ever
lower prices.

You will be given the daily selling prices of a stock (positive 16-bit integers) over a period of time. You can choose to buy
stock on any of the days. Each time you choose to buy, the price must be strictly lower than the previous time you bought
stock. Write a program which identifies which days you should buy stock in order to maximize the number of times you buy.

Here is a list of stock prices:
Day    1  2  3  4  5  6  7  8  9 10 11 12
Price 68 69 54 64 68 64 70 67 78 62 98 87

The best investor (by this problem, anyway) can buy at most four times if each purchase is lower then the previous purchase.
One four day sequence (there might be others) of acceptable buys is:
Day    2  5  6 10
Price 69 68 64 62

Input
* Line 1: N (1 <= N <= 5000), the number of days for which stock prices are given
* Lines 2..etc: A series of N space-separated integers, ten per line except the final line which might have fewer integers.
Output
Two integers on a single line:
* The length of the longest sequence of decreasing prices
* The number of sequences that have this length (guaranteed to fit in 31 bits)

In counting the number of solutions, two potential solutions are considered the same (and would only count as one solution)
if they repeat the same string of decreasing prices, that is, if they "look the same" when the successive prices are compared.
Thus, two different sequence of "buy" days could produce the same string of decreasing prices and be counted as only a single
solution.

Sample Input
12
68 69 54 64 68 64 70 67 78 62 98 87
Sample Output
4 2
 */
const uint16_t MAX_N = 5001;
uint16_t prices[MAX_N]; // stock prices

pair<int32_t,int32_t> buylowBuylower(const uint32_t N) {
  if (N < 2)
    return {-1,-1};

  uint32_t longest_subseq_cnt[MAX_N]; // how many longest subseqs with index i
  uint32_t longest_subseq_len[MAX_N]; // longest_subseq_len[i]: how long longest subseqs with index i

  longest_subseq_cnt[0] = longest_subseq_len[0] = 1;

  for (uint32_t i = 1; i < N; ++i) {
    longest_subseq_len[i] = 1;

    for (uint32_t j = 0; j < i; ++j) {
      if (prices[j] > prices[i] && longest_subseq_len[i] < longest_subseq_len[j]+1)
        longest_subseq_len[i] = longest_subseq_len[j]+1; // calc length of longest subseq with index i
    }
    for (uint32_t j = 0; j < i; ++j) {
      if (prices[j] > prices[i] && longest_subseq_len[i] == longest_subseq_len[j]+1)
        longest_subseq_cnt[i] += longest_subseq_cnt[j]; // calc how many longest subseqs
    }

    if (!longest_subseq_cnt[i])
      longest_subseq_cnt[i] = 1; // incrementing

    for (uint32_t j = 0; j < i; ++j) {
      if (prices[j] == prices[i] && longest_subseq_len[i] == longest_subseq_len[j])
        longest_subseq_cnt[i] -= longest_subseq_cnt[j]; // remove duplicates
    }
  }

  uint32_t len = 0;
  for (uint32_t i = 0; i < N; ++i) {
    if (len < longest_subseq_len[i])
      len = longest_subseq_len[i]; // find longest subseqs
  }
  uint32_t cnt = 0;
  for (uint32_t i = 0; i < N; ++i) {
    if (len == longest_subseq_len[i])
      cnt += longest_subseq_cnt[i]; // find longest subseqs
  }

  return {len, cnt};
}

int main(int argc, char** argv) {
/*  uint32_t N;
  while (~scanf("%d", &N)) {
    for (uint32_t i = 0; i < N; ++i) {
      scanf("%d", prices+i);
    }
    pair<uint32_t, uint32_t> len_cnt;
    len_cnt = buylowBuylower(N);
    cout << len_cnt.first << "," << len_cnt.second << endl;
  }*/

  vector<double> prices = {10.00,11.50,9.78,15.10,12.48,10.00,13.99,11.72,19.00,18.59};
  cout << "Max profit with 1 transaction: " << maxProfit_1trans(prices) << endl;
  cout << "Max profit with 1 transaction: " << maxProfit_ktrans(prices, 1) << endl;
  cout << "Max profit with any transactions: " << maxProfit_anytrans(prices) << endl;
  cout << "Max profit with 2 transactions: " << maxProfit_2trans(prices) << endl;
  cout << "Max profit with 2 transactions: " << maxProfit_ktrans(prices, 2) << endl;

  return 0;
}
