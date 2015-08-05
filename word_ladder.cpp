/*
Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that:
Only one letter can be changed at a time
Each intermediate word must exist in the dictionary

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
 */
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <queue>
#include <algorithm>

using namespace std;

uint32_t minLadderLen_dp(const string& start, const string& end, unordered_set<string>& dict) {
  uint32_t res = 1;
  dict.erase(start);
  dict.erase(end);

  deque<string> qs[2];
  qs[0].push_back(start);
  uint8_t idx = 0;

  while (!qs[idx].empty()) {
    ++res;

    while (!qs[idx].empty()) {
      string s = qs[idx].front();
      qs[idx].pop_front();

      for (uint32_t i = 0; i < s.length(); ++i) {
        char a = s[i];
        for (char az = 'a'; az <= 'z'; ++az) {
          s[i] = az;
          if (s == end)
            return res;
          if (dict.count(s)) {
            dict.erase(s);
            qs[!idx].push_back(s);
          }
        }
        s[i] = a;
      } //for
    } //while

    idx = !idx;
  } //while

  return 0;
}

// double BFS, speed up
uint32_t minLadderLen_2bfs(const string& start, const string& end, const unordered_set<string>& dict) {
  deque<string> q0 = {start}, q1 = {end};
  unordered_map<string,uint32_t> dis0 = {{start,1}}, dis1 = {{end,1}};

  while (!q0.empty() || !q1.empty()) {
    deque<string>* curr_q = &q0, *other_q = &q1;
    unordered_map<string,uint32_t> *curr_dis = &dis0, *other_dis = &dis1;

    if (!q1.empty() && (q0.empty() || q0.size() >= q1.size())) {
      swap(curr_q, other_q);
      swap(curr_dis, other_dis);
    }

    auto curr = curr_q->front();
    curr_q->pop_front();

    const uint32_t step = curr_dis->at(curr);
    for (uint32_t i = 0; i < start.length(); ++i) {
      for (char c = 'a'; c <= 'z'; ++c) {
        if (curr[i] == c)
          continue;

        auto old = curr[i];
        curr[i] = c;
        if (other_dis->count(curr))
          return step+other_dis->at(curr)+1;
        if (dict.count(curr) && !curr_dis->count(curr)) {
          curr_dis->emplace(curr, step+1);
          curr_q->push_back(curr);
        }

        curr[i] = old;
      }
    }
  }

  return 0;
}
#if 0
/*
Follow up:
How about output all results?
 */
vector<vector<string>> allLadders(const string& start, const string& end, unordered_set<string>& dict) {
  vector<vector<string>> res;
  unordered_map<string,vector<string>> prev;
  unordered_set<string> visited;
  unordered_map<string,uint32_t> distance;
  deque<string> q;
  q.push_back(start);
  distance[start] = 1;
  dict.insert(start);
  dict.insert(end);

  function<void(const string&,vector<string>&)> getPath = [&](const string& word, vector<string>& curr_path) {
    if (!prev.count(word)){
      vector<string> sln;
      sln.push_back(word);
      sln.insert(sln.end(), curr_path.begin(), curr_path.end());
      if (!curr_path.empty())
        reverse(sln.begin()+1, sln.end());
      res.push_back(sln);
    } else {
      for (string& s : prev[word]){
        curr_path.push_back(word);
        getPath(s, curr_path);
        curr_path.pop_back();
      }
    }
  };

  while (!q.empty()){
    string word = q.front();
    q.pop_front();

    if (word == end)
      break;

    visited.insert(word);
    uint32_t dist = distance[word]+1;
    vector<string> adj;

    for (uint32_t i = 0; i < word.size(); ++i) {
      char old = word[i];
      for (char c = 'a'; c <= 'z'; ++c) {
        word[i] = c;
        if (dict.count(word) && !visited.count(word)) {
          adj.push_back(word);
        }
      }
      word[i] = old;
    }

    for (string& w : adj) {
      if (distance[w] == 0) {
        prev[w].push_back(word);
        distance[w] = dist;
        q.push_back(w);
      } else if (distance[w] == dist) {
        prev[w].push_back(word);
      }
    }
  }

  if (!prev.empty()) {
    vector<string> curr_path;
    getPath(end, curr_path);
  }

  return res;
}
#endif
/*
Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.
 */
vector<vector<string>> shortestTransSeqs(const string& start,
                                         const string& end,
                                         unordered_set<string>& dict) {
  vector<vector<string>> res;
  unordered_map<string,vector<string>> recs;
  dict.erase(start);
  dict.erase(end);
  vector<string> to_ext(1, end);

  function<void(const string&)> backtrack =
    [&](const string& curr) {
    if (curr == start) {
      res.push_back(to_ext);
      reverse(res.back().begin(), res.back().end());
      return;
    }

    vector<string> v = recs[curr];
    for (uint32_t i = 0; i < v.size(); ++i) {
      to_ext.push_back(v[i]);
      backtrack(v[i]);
      to_ext.pop_back();
    }
  };

  vector<string> qs[2];
  unordered_set<string> sst;
  qs[0].push_back(start);
  uint8_t idx = 0;
  bool done = false;

  while (!qs[idx].empty()) {
    while (!qs[idx].empty()) {
      string s = qs[idx].back();
      for (uint32_t i = 0; i < s.length(); ++i) {
        char a = s[i];
        for (char az = 'a'; az <= 'z'; ++az) {
          s[i] = az;
          if (s == end) {
            done = true;
            recs[s].push_back(qs[idx].back());
          } else if (dict.count(s)) {
            recs[s].push_back(qs[idx].back());
            qs[!idx].push_back(s);
          }
        }
        s[i] = a;
      } //for
      qs[idx].pop_back();
    } //while

    if (done)
      break;

    idx = !idx;
    sst.clear();
    sst.insert(qs[idx].begin(), qs[idx].end());
    qs[idx].assign(sst.begin(), sst.end());

    for (uint32_t i = 0; i < qs[idx].size(); ++i)
      dict.erase(qs[idx][i]);
  } //while

  if (!recs.count(end))
    return res;

  backtrack(end);
  return res;
}

int main(int argc, char** argv) {
  const string start = "hit";
  const string end = "cog";
  unordered_set<string> dict;
  dict.insert("hot");
  dict.insert("dot");
  dict.insert("dog");
  dict.insert("lot");
  dict.insert("log");
  cout << "Minimum length of word ladder: " << minLadderLen_dp(start, end, dict) << endl;
 // cout << "Minimum length of word ladder: " << minLadderLen_2bfs(start, end, dict) << endl;

  dict.clear();
  dict.insert("hot");
  dict.insert("dot");
  dict.insert("dog");
  dict.insert("lot");
  dict.insert("log");
  vector<vector<string>> res = /*allLadders(start, end, dict);
  for (uint32_t i = 0; i < res.size(); ++i) {
    cout << "[";
    for (uint32_t j = 0; j < res[i].size(); ++j)
      cout << "\"" << res[i][j] << "\",";
    cout << "]," << endl;
  }

  res = */shortestTransSeqs(start, end, dict);
  for (uint32_t i = 0; i < res.size(); ++i) {
    cout << "[";
    for (uint32_t j = 0; j < res[i].size(); ++j) {
      cout << "\"" << res[i][j] << "\",";
    }
    cout << "]," << endl;
  }

  return 0;
}
