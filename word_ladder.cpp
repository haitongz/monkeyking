#include <iostream>
#include <set>
#include <map>
#include <functional>
#include <queue>
#include <algorithm>

using namespace std;

/*
Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end,
such that:
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
uint32_t minLadderLen_dp(const string& start, const string& end, set<string>& dict) {
  dict.erase(start);
  dict.erase(end);

  deque<string> q[2];
  q[0].push_back(start);
  bool idx = 0;
  uint32_t ret = 1;

  while (!q[idx].empty()) {
    ++ret;

    while (!q[idx].empty()) {
      string s = q[idx].front();
      q[idx].pop_front();

      for (uint32_t i = 0; i < s.length(); ++i) {
        char a = s[i];
        for (char c = 'a'; c <= 'z'; ++c) {
          s[i] = c;
          if (s == end)
            return ret;
          if (dict.count(s)) {
            dict.erase(s);
            q[!idx].push_back(s);
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
uint32_t minLadderLen_2bfs(const string& start, const string& end, const set<string>& dict) { // has issues
  deque<string> q0 = {start}, q1 = {end};
  map<string,uint32_t> dis0 = {{start,1}}, dis1 = {{end,1}};

  while (!q0.empty() || !q1.empty()) {
    deque<string>* curr_q = &q0, *other_q = &q1;
    map<string,uint32_t>* curr_dis = &dis0, *other_dis = &dis1;

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

/*
Follow up:
How about output all results?

another implementation of shortedTransSeqs

vector<vector<string>> allLadders(const string& start, const string& end, set<string>& dict) {
  map<string,vector<string>> prev;
  deque<string> q = {start};
  dict.insert(start);
  dict.insert(end);
  vector<vector<string>> ret;

  function<void(const string&,vector<string>&)> getPath =
    [&](const string& word, vector<string>& curr_path) {
    if (!prev.count(word)){
      vector<string> sln;
      sln.push_back(word);
      sln.insert(sln.end(), curr_path.begin(), curr_path.end());
      if (!curr_path.empty())
        reverse(sln.begin()+1, sln.end());
      ret.push_back(sln);
    } else {
      for (const auto& s : prev[word]){
        curr_path.push_back(word);
        getPath(s, curr_path);
        curr_path.pop_back();
      }
    }
  };

  map<string,uint32_t> distance;
  distance[start] = 1;
  set<string> visited;
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

    for (auto& w : adj) {
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

  return ret;
}
*/

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
                                         set<string>& dict) {
  dict.erase(start);
  dict.erase(end);

  vector<vector<string>> ret;
  map<string,vector<string>> recs;
  vector<string> to_ext(1, end);

  function<void(const string&)> solve = // backtracking
    [&](const string& curr) {
    if (curr == start) {
      ret.push_back(to_ext);
      reverse(ret.back().begin(), ret.back().end());
      return;
    }

    vector<string> v = recs[curr];
    for (uint32_t i = 0; i < v.size(); ++i) {
      to_ext.push_back(v[i]);
      solve(v[i]);
      to_ext.pop_back();
    }
  };

  vector<string> q[2];
  set<string> sst;
  q[0].push_back(start);
  bool idx = 0;
  bool done = false;

  while (!q[idx].empty()) {

    while (!q[idx].empty()) {
      string s = q[idx].back();
      for (uint32_t i = 0; i < s.length(); ++i) {
        char a = s[i];
        for (char c = 'a'; c <= 'z'; ++c) {
          s[i] = c;
          if (s == end) {
            done = true;
            recs[s].push_back(q[idx].back());
          } else if (dict.count(s)) {
            recs[s].push_back(q[idx].back());
            q[!idx].push_back(s);
          }
        }
        s[i] = a;
      } //for

      q[idx].pop_back();
    } //while

    if (done)
      break;

    idx = !idx;
    sst.clear();
    sst.insert(q[idx].begin(), q[idx].end());
    q[idx].assign(sst.begin(), sst.end());

    for (uint32_t i = 0; i < q[idx].size(); ++i)
      dict.erase(q[idx][i]);
  } //while

  if (!recs.count(end))
    return ret;

  solve(end);
  return ret;
}

int main(int argc, char** argv) {
  const string start = "hit";
  const string end = "cog";
  set<string> dict;
  dict.insert("hot");
  dict.insert("dot");
  dict.insert("dog");
  dict.insert("lot");
  dict.insert("log");
  cout << "Minimum length of word ladder: " << minLadderLen_dp(start, end, dict) << endl;

  /*
  dict.insert("hot");
  dict.insert("dot");
  dict.insert("dog");
  dict.insert("lot");
  dict.insert("log");
  cout << "Minimum length of word ladder: " << minLadderLen_2bfs(start, end, dict) << endl; */

  dict.clear();
  dict.insert("hot");
  dict.insert("dot");
  dict.insert("dog");
  dict.insert("lot");
  dict.insert("log");
  vector<vector<string>> res = /*allLadders(start, end, dict);
  for (const auto& i : res) {
    cout << "[";
    for (const auto& j : i)
      cout << "\"" << j << "\",";
    cout << "]," << endl;
  }

  res = */shortestTransSeqs(start, end, dict);
  cout << "Shortest transform sequences:" << endl;
  for (const auto& i : res) {
    cout << "[";
    for (const auto& j : i)
      cout << "\"" << j << "\",";
    cout << "]," << endl;
  }

  return 0;
}
