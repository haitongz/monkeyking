/*
Given two strings str1 and str2, find the shortest string that has both str1 and str2 as subsequences.
 */
#include <iostream>

using namespace std;

#if 0
#include <algorithm>
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>
// See http://www-igm.univ-mlv.fr/~lecroq/seqcomp/node4.html.
class LCS
{
    class LCSTable
    {
        size_t   m_;
        size_t   n_;
        size_t*  data_;
    public:
        LCSTable(size_t m, size_t n)
        : m_(m)
        , n_(n)
        {
            data_ = new size_t[(m_ + 1) * (n_ + 1)];
        }
        ~LCSTable()
        {
            delete [] data_;
        }

        void setAt(size_t i, size_t j, size_t value)
        {
            data_[i + j * (m_ + 1)] = value;
        }

        size_t getAt(size_t i, size_t j) const
        {
            return data_[i + j * (m_ + 1)];
        }

        template<typename T> void
        build(const T* X, const T* Y)
        {
            for (size_t i=0; i<=m_; ++i)
                setAt(i, 0, 0);

            for (size_t j=0; j<=n_; ++j)
                setAt(0, j, 0);

            for (size_t i = 0; i < m_; ++i)
            {
                for (size_t j = 0; j < n_; ++j)
                {
                    if (X[i] == Y[j])
                        setAt(i+1, j+1, getAt(i, j)+1);
                    else
                        setAt(i+1, j+1, std::max(getAt(i+1, j), getAt(i, j+1)));
                }
            }
        }
    };

    template<typename T> static void
    backtrackOne(const LCSTable& table,
                 const T* X, const T* Y, size_t i, size_t j,
                 std::vector<T>& result)
    {
        result.clear();
        if (i == 0 || j == 0)
            return;
        if (X[i - 1] == Y[j - 1])
        {
            backtrackOne(table, X, Y, i - 1, j - 1, result);
            result.push_back(X[i - 1]);
            return;
        }
        if (table.getAt(i, j - 1) > table.getAt(i -1, j))
            backtrackOne(table, X, Y, i, j - 1, result);
        else
            backtrackOne(table, X, Y, i - 1, j, result);
    }

public:
    template<typename T> static void
    findOne(T* X, size_t m, T* Y, size_t n,
            std::vector<T>& result)
    {
        LCSTable table(m, n);
        table.build(X, Y);
        backtrackOne(table, X, Y, m, n, result);
    }
};
#endif

#define MAXN 1000001;

int32_t fail[MAXN];

int32_t kmp(const char* txt, const uint32_t t_len, int32_t& i,
            const char* pat, const uint32_t p_len, int32_t& j) {
  fail[0] = -1;

  for (j = 1; j < p_len; ++j) {
    for (i = fail[j-1]; i >= 0 && (pat[i+1] != pat[j]); i = fail[i])
      ;
    fail[j] = (pat[i+1] == pat[j]) ? i+1 : -1;
  }

  for (i = j = 0; i < t_len && j < p_len; ++i) {
    if (txt[i] == pat[j])
      ++j;
    else if (j) {
      j = fail[j-1]+1;
      --i;
    }
  }

  return j == p_len ? (i-p_len) : -1;
}

int main(int argc, char** argv) {
  // int i,j,t,u,v,len1,len2,pos;
  //   scanf("%d",&t),getchar();
  char str[2][MAXN];

  while (true) {
    gets(str[0]);
    gets(str[1]);

    const uint32_t len1 = strlen(str[0]);
    const uint32_t len2 = strlen(str[1]);

    int32_t i, j;
    int32_t pos = kmp(str[0], len1, i, str[1], len2, j);
    int32_t u = 0;
    if (pos != -1)
      u = len2;
    else if (i == len1 && j > 0 && (str[0][len1-1] == str[1][j-1]))
      u = j;

    pos = kmp(str[1], len2, i, str[0], len1, j);
    int32_t v = 0;
    if (pos != -1)
      v = len1;
    else if (i == len2 && j > 0 && str[1][len2-1] == str[0][j-1])
      v = j;

    cout << (len1+len2-max(u, v)) << endl;
  }

  return 0;
}

#if 0
string shortestSuperseq(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length(), len2 = s2.length();
  if (!len1 && !len2)
    return "";
  else if (!len1)
    return s2;
  else if (!len2)
    return s1;

  int32_t dp[len1+1][len2+1];
  for (auto& i : dp)
    for (auto& j : i)
      j = -1;

  function<uint32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t i, const uint32_t j) {
    if (i == len1 || j == len2)
      return dp[i][j] = 1;

    if (s1[i] == s2[j]) {
      if (dp[i+1][j+1] > 0)
        return (dp[i][j] = dp[i+1][j+1]);
      else
        return (dp[i][j] = solve(i+1, j+1));
    } else {
      if (dp[i+1][j] > 0 && dp[i][j+1] > 0)
        return (dp[i][j] = dp[i+1][j]+dp[i][j+1]);
      else if (dp[i+1][j] > 0)
        return (dp[i][j] = dp[i+1][j]+solve(i, j+1));
      else if (dp[i][j+1] > 0)
        return (dp[i][j] = dp[i][j+1]+solve(i+1,j));
      else
        return (dp[i][j] = solve(i+1, j)+solve(i, j+1));
    }
  };

  /* int f(int i, int j) {

  if(i ==strlen(S1) || j == strlen(S2))
      return 1;
  if(S1[i]==S2[j])
      return f(i+1, j+1);

  return f(i+1, j) + f(i, j+1);
  } */
  void create_answer(int n, int i, int j) {       

    if(i<strlen(S1)&&j<strlen(S2))
    if(S1[i] == S2[j]) {
      printf("%c",S1[i]);
      create_answer(n,i+1,j+1);
    }
    else if(S1[i]<S2[j]) {

      if(n <=a[i+1][j]) {
        printf("%c",S1[i]);
        create_answer(n, i+1, j);
      }
      else {

        printf("%c",S2[j]);

        create_answer(n-a[i+1][j], i, j+1);

      }
    }
    else {

      if(n <= a[i][j+1]) {

        printf("%c",S2[j]);
        create_answer(n, i, j+1);
      }
      else {
        printf("%c",S1[i]);
        create_answer(n-a[i][j+1], i+1, j);
      }
    }
    else if(i<strlen(S1)) {printf("%c",S1[i]); create_answer(n,i+1,j+1); }
    else if(j<strlen(S2)) {
      printf("%c",S2[j]); create_answer(n,i+1,j+1);
    }
    else {

    }

  }

int main(int argc, char** argv) {
  int32_t t, i;

  scanf("%d",&t);

  while(t--) {
    int n=1,i=0,j=0;

    scanf("%s",S1);
    scanf("%s",S2);
    scanf("%d",&n);

    for(i=0;i<=strlen(S1);i++)
      for(j=0;j<=strlen(S2);j++)
        a[i][j]=0;

    for(i=0;i<=strlen(S1);i++)
      for(j=0;j<=strlen(S2);j++)
        if(a[i][j]==0)
          f(i,j);

    if(a[0][0]<n)
      printf("NO ANSWER\n");
    else {
      create_answer(n,0,0);
      printf("\n");
    }
  } return 0;

}
#endif
