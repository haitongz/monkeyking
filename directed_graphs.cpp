#include <iostream>
#include <vector>
#include <functional>

using namespace std;

static const uint32_t MAX_LIMIT = numeric_limits<uint32_t>::max();
static const uint32_t MIN_LIMIT = numeric_limits<uint32_t>::min();

struct DirectedGraph {
  const uint32_t V;
  vector<vector<uint32_t>> adjs;

  DirectedGraph(const uint32_t size)
      : V(size), adj(V, vector<int32_t>()) {
  }
  void addEdge(const uint32_t s, const uint32_t d) {
    adjs[s].push_back(d);
  }
  bool cycleExists() const;
  void DFSPrint();
  void BFS(const uint32_t s);
  bool isReachable(const uint32_t s, const uint32_t d) const;
  void topologicalSort();
};

// DFS traversal of the vertices reachable from v.
void DirectedGraph::DFSPrint() {//const uint32_t s) {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  function<void(const uint32_t)> solve = [&](const uint32_t v) { // only traverse vertices reachable from a given source vertex
    visited[v] = true;
    cout << v << " "; // shall change depends upon what needs to be done

    // Recur for all the vertices adjacent to this vertex
    for (auto i : adjs[v])
      if (!visited[i])
        solve(i);
  };

  for (uint32_t i = 0; i < V; ++i)
    if (!visited[i])
      solve(i);
}

void DirectedGraph::BFS(const uint32_t s) {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  // Create a queue for BFS
  deque<int32_t> q = {s};
  visited[s] = true;

  while (!q.empty()) {
    const uint32_t v = q.front();
    cout << v << " ";
    q.pop_front();

    // Get all adjacent vertices of the dequeued vertex s.
    // If a adjacent has not been visited, then mark it visited and enqueue it
    for (auto i : adjs[v]) {
      if (!visited[i]) {
        visited[i] = true;
        q.push_back(i);
      }
    }
  }
}

/*
Given a directed graph, a source vertex s and a destination vertex d, print all paths from given s to d.
 */
vector<vector<int32_t>> Graph::allPaths(const uint32_t src, const uint32_t dst) {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  vector<vector<uint32_t>> ret;
  vector<uint32_t> to_ext;
  uint32_t path_idx = 0;

  function<void(const uint32_t)> solve = [&](const uint32_t v) { // backtracking
    visited[v] = true;
    to_ext[path_idx] = v;
    ++path_idx;

    if (v == dst) {
      ret.push_back(to_ext);
      return;
    } else {
      for (auto i : adj[v])
        if (!visited[i])
          solve(i);
    }

    --path_idx;
    visited[v] = false;
  };

  solve(src);
  return ret;
}

/*
Find cycle in a directed graph
 */
bool DirectedGraph::cycleExists() const {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  bool recs[V];
  for (auto& i : recs)
    i = false;

  function<bool(const uint32_t)> solve = [&](const uint32_t v) { // DFS and backtracking
    if (!visited[v]) {
      visited[v] = true;

      recs[v] = true; // need recs because it is directed, no need if undirected
      for (auto i : adjs[v])
        if (!visited[i] && solve(i))
          return true;
        else if (recs[i])
          return true;
      }
      recs[v] = false;
    }

    return false;
  };

  for (uint32_t i = 0; i < V; ++i) {
    if (solve(i))
      return true;
  }

  return false;
}

/*
Given a Directed Graph and two vertices in it, check whether there is a path from the first given vertex to second.
 */
bool
DirectedGraph::isReachable(const uint32_t src, const uint32_t dst) const { // A BFS based function to check whether d is reachable from s.
  if (src == dst)
    return true;

  // Mark all the vertices as not visited
  bool visited[V];
  for (auto& i : visited)
    i = false;

  visited[src] = true;
  deque<const uint32_t> q = {src};

  while (!q.empty()) {
    const uint32_t v = q.front();
    q.pop_front();

    // Get all adjacent vertices of the dequeued vertex s.
    // If a adjacent has not been visited, then mark it visited and enqueue it
    for (auto i : adjs[v]) { // If this adjacent node is the destination node, then return true
      if (i == dst)
        return true;

      if (!visited[i]) {
        visited[i] = true;
        q.push_back(i);
      }
    }
  }

  return false;
}

/*
The Floyd Warshall Algorithm is for solving the All Pairs Shortest Path problem.
The problem is to find shortest distances between every pair of vertices in a given edge weighted directed Graph.
 */
void floydWarshall_dp(const uint32_t graph[][V]) {
  uint32_t dist[V][V]; // output matrix that will finally have the shortest distances between every pair of vertices */

  /* Initialize the solution matrix same as input graph matrix.
     Or we can say the initial values of shortest distances are based on shortest paths considering no intermediate vertex. */
  for (uint32_t i = 0; i < V; ++i)
    for (uint32_t j = 0; j < V; ++j)
      dist[i][j] = graph[i][j];

  /* Add all vertices one by one to the set of intermediate vertices.
     ---> Before start of a iteration, we have shortest distances between all
     pairs of vertices such that the shortest distances consider only the
     vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
     ----> After the end of a iteration, vertex no. k is added to the set of
     intermediate vertices and the set becomes {0, 1, 2, .. k} */
  for (uint32_t k = 0; k < V; ++k) {
    // Pick all vertices as source one by one
    for (uint32_t i = 0; i < V; ++i) {
      // Pick all vertices as destination for the above picked source
      for (uint32_t j = 0; j < V; j++) {
        // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
      }
    }
  }

  // Print the shortest distance matrix
  for (auto& i : dist)
    for (auto j : i)
      cout << (j == MAX_LIMIT ? "INF" : j) << " ";

  return 0;
}

/*
Given a directed graph, find out if a vertex j is reachable from another vertex i for all vertex pairs (i, j)
in the given graph. Here reachable mean that there is a path from vertex i to j. The reach-ability matrix is
called transitive closure of a graph.
 */
void transitiveClosure(const uint32_t graph[V][V]) {
  uint32_t reach[V][V]; /* the output matrix that will finally have the shortest distances between every pair of vertices */

  /* Initialize the solution matrix same as input graph matrix.
     Or we can say the initial values of shortest distances are based on shortest paths considering no intermediate vertex. */
  for (uint32_t i = 0; i < V; ++i)
    for (uint32_t j = 0; j < V; ++j)
      reach[i][j] = graph[i][j];

  /* Add all vertices one by one to the set of intermediate vertices.
     ---> Before start of a iteration, we have reachability values for all
     pairs of vertices such that the reachability values consider only the
     vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
     ----> After the end of a iteration, vertex no. k is added to the set of
     intermediate vertices and the set becomes {0, 1, 2, .. k} */
  for (uint32_t k = 0; k < V; ++k) {
    // Pick all vertices as source one by one
    for (uint32_t i = 0; i < V; ++i) {
      // Pick all vertices as destination for the above picked source
      for (uint32_t j = 0; j < V; ++j) {
        // If vertex k is on a path from i to j, then make sure that the value of reach[i][j] is 1
        reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
      }
    }
  }
}

/*
Topological Sorting is mainly used for scheduling jobs from the given dependencies among jobs. Time complexity is O(V+E).
 */
void DirectedGraph::topologicalSort() {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  stack<uint32_t> stk;

  function<void(const uint32_t)> solve = [&](const uint32_t v) {
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto i : adjs[v])
      if (!visited[i])
        solve(i);

    // Push current vertex to stack which stores result
    stk.push(v);
  };

  // Call the recursive helper function to store Topological Sort starting from all vertices one by one
  for (uint32_t i = 0; i < V; ++i)
    if (!visited[i])
      solve(i);

  // Print contents of stack
  while (!stk.empty()) {
    cout << stk.top() << " ";
    stk.pop();
  }
}

/*
Given a Weighted Directed Acyclic Graph and a source vertex in the graph,
find the shortest paths from given source to all other vertices.
 */
void DirectedGraph::shortestPath(int32_t s) {
  bool visited[V];
  for (auto& i : visited)
    i = false; // Mark all the vertices as not visited

  stack<uint32_t> stk;

  function<void(const uint32_t)> solve = [&](const uint32_t v) {
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto i : adjs[v])
      if (!visited[i])
        solve(i);

    // Push current vertex to stack which stores result
    stk.push(v);
  };

  uint32_t dist[V];
  for (auto& i : dist)
    i = MAX_LIMIT;
  dist[s] = 0;

  // Process vertices in topological order
  while (!stk.empty()) {
    // Get the next vertex from topological order
    int32_t u = stk.top();
    stk.pop();

    if (dist[u] != MAX_LIMIT) // Update distances of all adjacent vertices
      for (auto& i : adjs[u])
        dist[i.V] = min(dist[i.V], dist[u]+i.weight);
  }

  // Print the calculated shortest distances
  for (auto i : dist)
    cout << (i == MAX_LIMIT ? "INF" : dist[i]) << " ";
}

/*
A directed graph is strongly connected if there is a path between all pairs of vertices.
A strongly connected component (ScC) of a directed graph is a maximal strongly connected subgraph.
 */
DirectedGraph DirectedGraph::getTranspose() {
  DirectedGraph g(V);
  for (uint32_t v = 0; v < V; ++v) {
    for (auto i : adjs[v]) {
      g.adjs[i].push_back(v);
    }
  }

  return g;
}

void DirectedGraph::ScC() {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  stack<int32_t> stk;

  function<void(const uint32_t)> fillOrder = [&](const uint32_t v) {
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto i : adjs[v])
      if (!visited[i])
        fillOrder(i);

    // All vertices reachable from v are processed by now, push v to Stack
    stk.push(v);
  };

  // Fill vertices in stack according to their finishing times
  for (uint32_t i = 0; i < V; ++i)
    if (!visited[i])
      fillOrder(i);

  // Create a reversed graph
  DirectedGraph gr = getTranspose();

  // Mark all the vertices as not visited (For second DFS)
  for (auto& i : visited)
    i = false;

  function<void(const int32_t)> solve = [&](const int32_t n) {
    visited[n] = true;
    cout << n << " ";

    // Recur for all the vertices adjacent to this vertex
    for (auto i : gr.adjs[n])
      if (!visited[i])
        solve(i);
  };

  // Now process all vertices in order defined by Stack
  while (!stk.empty()) {
    // Pop a vertex from stack
    int32_t v = stk.top();
    stk.pop();

    // Print strongly connected component of the popped vertex
    if (!visited[v]) {
      solve(v);
      cout << endl;
    }
  }
}

/*
Given a directed graph, find out whether the graph is strongly connected or not.
A directed graph is strongly connected if there is a path between any two pair of vertices.
 */
bool DirectedGraph::isSC() {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  function<void(DirectedGraph&,const int32_t)> solve =
    [&](DirectedGraph& g, const int32_t n) { // DFS traversal
    visited[n] = true;
    cout << n << " ";

    // Recur for all the vertices adjacent to this vertex
    for (auto i : g.adjs[n])
      if (!visited[i])
        solve(i);
  };

  // Step 2: Do DFS traversal starting from first vertex.
  solve(*this, 0);

  // If DFS traversal doesn¿t visit all vertices, then return false.
  for (auto i : visited)
    if (!i)
      return false;

  // Step 3: Create a reversed graph
  DirectedGraph gr = getTranspose();

  // Step 4: Mark all the vertices as not visited (For second DFS)
  for (auto& i : visited)
    i = false;

  // Step 5: Do DFS for reversed graph starting from first vertex. Staring Vertex must be same starting point of first DFS
  solve(gr, 0);

  // If all vertices are not visited in second DFS, then return false
  for (auto i : visited)
    if (!i)
      return false;

  return true;
}

/*
There are N stations on route of a train. The train goes from station 0 to N-1.
The ticket cost for all pair of stations (i, j) is given where j is greater than i.
Find the minimum cost to reach the destination.

Input:
cost[N][N] = {{0, 15, 80, 90},
              {INF, 0, 40, 50},
              {INF, INF, 0, 70},
              {INF, INF, INF, 0}};
There are 4 stations and cost[i][j] indicates cost to reach j from i. The entries where j < i are meaningless.

Output:
The minimum cost is 65
The minimum cost can be obtained by first going to station 1 from 0. Then from station 1 to station 3.

minCost(0, N-1) = MIN {cost[0][n-1],
                       cost[0][1]+minCost(1, N-1),
                       minCost(0, 2)+minCost(2, N-1),
                       ........,
                       minCost(0, N-2)+cost[N-2][n-1] }
 */
// This function returns the smallest possible cost to reach station N-1 from
// station 0. Time complexity of the above implementation is exponential as it
// tries every possible path from 0 to N-1.
uint32_t minCost_dp(const uint32_t cost[][N]) {
  function<uint32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t s, const uint32_t d) {
    if (s > d)
      return MAX_LIMIT;
    // If source is same as destination or destination is next to source
    else if (s == d || s+1 == d)
      return cost[s][d];

    // Initialize min cost as direct ticket from source 's' to destination 'd'.
    uint32_t min_cost = cost[s][d];

    // Try every intermediate vertex to find minimum
    for (uint32_t i = s+1; i < d; ++i) {
      uint32_t tmp = solve(s, i)+solve(i, d);
      min_cost = min(tmp, min_cost);
    }
    return min_cost;
  };

  return solve(0, N-1);
}

// We can solve this problem using O(N) extra space and O(N2) time.
// The idea is based on the fact that given input matrix is a Directed Acyclic Graph (DAG).
uint32_t minCost_DAG(const uint32_t cost[][N]) {
  // dist[i] stores minimum cost to reach station i from station 0.
  uint32_t dist[N];

  for (uint32_t i = 0; i < N; ++i)
    dist[i] = MAX_LIMIT;
  dist[0] = 0;

  // Go through every station and check if using it as an intermediate station gives better path
  for (uint32_t i = 0; i < N; ++i)
    for (uint32_t j = i+1; j < N; ++j)
      dist[j] = min(dist[j], dist[i]+cost[i][j]);

  return dist[N-1];
}

/*
A person is determined to finish the book in ¿k¿ days but he never wants to stop a chapter in between.
Find the optimal assignment of chapters, such that the person doesn¿t read too many extra/less pages overall.

Example 1:
Input:  Number of Days to Finish book = 2
        Number of pages in chapters = {10, 5, 5}
Output: Day 1:  Chapter 1
        Day 2:  Chapters 2 and 3

Example 2:
Input:  Number of Days to Finish book = 3
        Number of pages in chapters = {8, 5, 6, 12}
Output: Day 1:  Chapter 1
        Day 2:  Chapters 2 and 3
        Day 2:  Chapter 4
 */
// This function finds and prints optimal read list.  It first creates DAG.
void minAssignment(const uint32_t pages[]) {
  // 1) ............CONSTRUCT GRAPH.................
  // Partial sum array construction S[i] = total pages till ith chapter
  uint32_t avg_pages = 0, sum = 0, S[CHAPTERS+1], path[DAYS+1];
  S[0] = 0;

  for (uint32_t i = 0; i < CHAPTERS; ++i) {
    sum += pages[i];
    S[i+1] = sum;
  }

  // Average pages to be read in a day
  avg_pages = round(sum/DAYS);

  /* DAG construction vertices being chapter name & Edge weight being
     |avg_pages-pages in a chapter| Adjacency matrix representation  */
  for (uint32_t i = 0; i < CHAPTERS+1; ++i) {
    for (uint32_t j = 0; j < CHAPTERS+1; ++j) {
      if (j <= i)
        DAG[i][j] = NOLINK;
      else {
        sum = abs(avg_pages-(S[j]-S[i]));
        DAG[i][j] = sum;
      }
    }
  }
    // 2) ............FIND OPTIMAL PATH................
    function<void()> solve = [&](int u, int* path, int path_len, int sum, int k) {
      static int min = INT_MAX;
  
      // Ignore the assignment which requires more than required days
      if (k < 0)
          return;
  
      // Current assignment of chapters to days
      path[path_len] = u;
      path_len++;
  
      // Update the optimal assignment if necessary
      if (k == 0 && u == CHAPTERS)
      {
          if (sum < min)
          {
              updateAssignment(path, path_len);
              min = sum;
          }
      }
  
      // DFS - Depth First Search for sink
      for (int v = u+1; v <= CHAPTERS; v++)
      {
          sum += DAG[u][v];
          assignChapters(v, path, path_len, sum, k-1);
          sum -= DAG[u][v];
      }
  };
  

    assignChapters(0, path, 0, 0, DAYS);
 
    // 3) ..PRINT OPTIMAL READ LIST USING OPTIMAL PATH....
    cout << "Optimal Chapter Assignment :" << endl;
    int ch;
    for (int i = 0; i < DAYS; i++)
    {
        ch = optimal_path[i];
        cout << "Day" << i+1 << ": " << ch << " ";
        ch++;
        while ( (i < DAYS-1 && ch < optimal_path[i+1]) ||
                (i == DAYS-1 && ch <= CHAPTERS))
        {
           cout <<  ch << " ";
           ch++;
        }
        cout << endl;
    }
}

/*
Given a number of friends who have to give or take some amount of money from one another.
Design an algorithm by which the total cash flow among all the friends is minimized.
O(N2) where N is the number of persons.
 */
// Given a set of persons as graph[] where graph[i][j] indicates/ the amount that person i needs to pay person j,
// this function finds and prints the minimum cash flow to settle all debts.
void minCashFlow(const uint32_t graph[][N]) {
  int32_t amount[N] = {0};

  // Calculate the net amount to be paid to person 'p', and stores it in amount[p].
  // The value of amount[p] can be calculated by subtracting debts of 'p' from credits of 'p'
  for (uint32_t p = 0; p < N; ++p)
    for (uint32_t i = 0; i < N; ++i)
      amount[p] += graph[i][p]-graph[p][i];

  function<uint32_t()> getMaxIdx = [&]() {
    uint32_t ret = 0;
    for (auto i : amount)
      if (i > amount[ret]
        ret = i;

    return ret;
  };
  function<uint32_t()> getMinIdx = [&]() {
    uint32_t ret = 0;
    for (auto i : amount)
      if (i < amount[ret])
        ret = i;

    return ret;
  };
  function<void()> solve = [&]() {
    // Find the indices of minimum and maximum values in amount[].
    // amount[maxcredit_idx] indicates the maximum amount to be given (or
    // credited) to any person. And amount[maxdebit_idx] indicates
    // the maximum amount to be taken (or debited) from any person.
    // So if there is a positive value in amount[], then there must be a negative value
    uint32_t maxcredit_idx = getMaxIdx(), maxdebit_idx = getMinIdx();

    // If both amounts are 0, then all amounts are settled
    if (!amount[maxcredit_idx] && !amount[maxdebit_idx])
      return;

    // Find the minimum of two amounts
    uint32_t min_amt = min(-amount[maxdebit_idx], amount[maxcredit_idx]);
    amount[maxcredit_idx] -= min_amt;
    amount[maxdebit_idx]  += min_amt;

    // If minimum is the maximum amount to be
    cout << "Person " << maxdebit_idx << " pays " << min_amt << " to " << "Person " << maxcredit_idx << endl;

    // it is guaranteed that the recursion would terminate as either
    // amount[maxcredit_idx] or amount[maxdebit_idx] becomes 0
    solve();
  };

  solve();
}

/*
Biconnected Components: store visited edges in a stack while DFS on a graph and keep looking for Articulation Points.
As soon as an Articulation Point u is found, all edges visited while DFS from node u onwards will form one biconnected
component. When DFS completes for one connected component, all edges present in stack will form a biconnected component.
If there is no Articulation Point in graph, then graph is biconnected and so there will be one biconnected component
which is the graph itself.
 */
void DirectedGraph::BcC() {
  int32_t disc[V];
  int32_t low[V];
  int32_t parent[V];

  // Initialize disc and low, and parent arrays
  for (uint32_t i = 0; i < V; ++i) {
    disc[i] = -1;
    low[i] = -1;
    parent[i] = -1;
  }

  vector<Edge> stk;
  function<void(const uint32_t)> backtrack =
    [&](const uint32_t u) {
    // A static variable is used for simplicity, we can avoid use
    // of static variable by passing a pointer.
    static uint32_t time = 0;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    uint32_t children = 0;
    // Go through all vertices adjacent to this
    for (auto i : adjs[u]) {
      uint32_t v = i; // v is current adjacent of 'u'
      // If v is not visited yet, then recur for it
      if (disc[v] == -1) {
        ++children;
        parent[v] = u;
        stk.push_back({u, v});
        backtrack(v);

        // Check if the subtree rooted with 'v' has a connection to one of the
        // ancestors of 'u':
        // Case 1 -- per Strongly Connected Components Article
        low[u] = min(low[u], low[v]);
        //If u is an articulation point, pop all edges from stack till u -- v
        if ((disc[u] == 1 && children > 1) ||
            (disc[u] > 1 && low[v] >= disc[u])) {
          while (stk.back().u != u || st->back().v != v) {
            cout << stt.back().u << "--" << stk.back().v << " ";
            stk->pop_back();
          }

          cout << stk.back().u << "--" << st->back().v;
          stk.pop_back();
          cout << endl;
          ++count;
        }
      } else if(v != parent[u] && disc[v] < low[u]) {
        // Update low value of 'u' only of 'v' is still in stack
        // (i.e. it's a back edge, not cross edge).
        // Case 2 -- per Strongly Connected Components Article
        low[u] = min(low[u], disc[v]);
        stk.push_back({u, v});
      }
    }
  };

  for (uint32_t i = 0; i < V; ++i) {
    if (disc[i] == -1)
      backtrack(i);

    uint32_t j = 0;
    while (stk.size() > 0) {
      j = 1;
      cout << stk.back().u << "--" << stk.back().v << " ";
      stk.pop_back();
    }

    if (j == 1) {
      cout << endl;
      ++count;
    }
  }
}

/*
Given a snake and ladder board, find the minimum number of dice throws required to reach the destination
or last cell from source or 1st cell. Basically, the player has total control over outcome of dice throw
and wants to find out minimum number of throws required to reach last cell.

If the player reaches a cell which is base of a ladder, the player has to climb up that ladder and if reaches
a cell is mouth of the snake, has to go down to the tail of snake without a dice throw.
 */
struct Entry {
  uint32_t v;     // Vertex number
  uint32_t dist;  // Distance of this vertex from source
};

/*
Given a snake and ladder board, find the minimum number of dice throws required to reach the destination or last cell
from source or 1st cell. Basically, the player has total control over outcome of dice throw and wants to find out
minimum number of throws required to reach last cell.

If the player reaches a cell which is base of a ladder, the player has to climb up that ladder and if reaches a cell
is mouth of the snake, has to go down to the tail of snake without a dice throw.
 */
uint32_t snakeAndLadder(const uint32_t move[], const uint32_t N) {
  bool visited[N];
  for (auto& i : visited)
    i = false;
  visited[0] = true;

  // Create a queue for BFS
  deque<Entry> q = {{0,0}};
  Entry ret;

  while (!q.empty()) {
    ret = q.front();
    uint32_t v = ret.v; // vertex no. of queue entry

    // If front vertex is the destination vertex, we are done
    if (v == N-1)
      break;

    // Otherwise dequeue the front vertex and enqueue its adjacent vertices (or cell numbers reachable through a dice throw)
    q.pop_front();
    for (uint32_t j = v+1; j <= v+6 && j < N; ++j) {
      // If this cell is already visited, then ignore
      if (!visited[j]) { // Otherwise calculate its distance and mark it as visited
        Entry a;
        a.dist = ret.dist+1;
        visited[j] = true;

        // Check if there a snake or ladder at 'j' then tail of snake or top of ladder become the adjacent of 'i'
        if (move[j] != -1)
          a.v = move[j];
        else
          a.v = j;
        q.push(a);
      }
    }
  }

  return ret.dist;
}

/*
Given a directed and two vertices u and v in it, find shortest path from u to v with exactly k edges on the path.
 */
uint32_t shortestPath(uint32_t graph[][V],
                      const uint32_t u, const uint32_t v, const uint32_t k) {
{
  uint32_t ret = MAX_LIMIT;
  function<uint32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t s, const uint32_t remaining) {
    if (!remaining && s == v)
      return 0;
    if (remaining == 1 && graph[s][v] != MAX_LIMIT)
      return graph[s][v];
    if (remaining <= 0)
      return MAX_LIMIT;

    // Initialize result
    uint32_t ret = MAX_LIMIT;

    // Go to all adjacents of u and recur
    for (uint32_t i = 0; i < V; ++i) {
      if (graph[s][i] != MAX_LIMIT && s != i && v != i) {
        uint32_t rec_res = solve(i, remaining-1);
        if (rec_res != MAX_LIMIT)
          ret = min(ret, graph[s][i]+rec_res);
      }
    }
  };

  solve(u, k);
  return ret;
}

int main(int argc, char** argv) {
  DirectedGraph g(4);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);
  g.addEdge(2, 0);
  g.addEdge(2, 3);
  g.addEdge(3, 3);

  if (g.cycleExists())
    cout << "Graph contains cycle." << endl;
  else
    cout << "Graph doesn't contain cycle." << endl;

  uint32_t graph[N][N] = {{0, 1000, 2000},
                          {0, 0, 5000},
                          {0, 0, 0},};

  minCashFlow(graph);
  return 0;
}
