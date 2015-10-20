#include <iostream>
#include <vector>

using namespace std;

/*
A disjoint-set data structure is a data structure that keeps track of a set of elements partitioned
into a number of disjoint (non-overlapping) subsets. A union-find algorithm is an algorithm
that performs two useful operations on such a data structure:

Find: Determine which subset a particular element is in. This can be used for determining
if two elements are in the same subset.

Union: Join two subsets into a single subset.
 */
struct Edge {
  uint32_t src, dst;
  uint32_t weight;
};

struct UndirectedGraph {
  uint32_t V; // V-> Number of vertices //, E-> Number of edges
  // graph is represented as an array of edges
  vector<Edge> edges;

  void addEdge(const uint32_t src, const uint32_t dst) {
    edges.push_back({src, dst});
  }
};

struct UndirectedGraph2 {
  uint32_t V; // V-> Number of vertices //, E-> Number of edges
  vector<vector<uint32_t>> adjs;

  void addEdge(const uint32_t v, const uint32_t w) {
    adjs[v].push_back(w);
    adjs[w].push_back(v);
  }
};

bool UndirectedGraph::cycleExists() {
  int32_t parent[V];
  for (auto& i : parent)
    i = -1;

  function<const uint32_t(const uint32_t)> find = [&](const uint32_t i) {
    if (parent[i] == -1)
      return i;

    return find(parent[i]);
  };

  function<void(const uint32_t,const uint32_t)> Union =
    [&](const uint32_t x, const uint32_t y) {
    const uint32_t xset = find(x);
    const uint32_t yset = find(y);
    parent[xset] = yset;
  };

  // Iterate through all edges of graph, find subset of both vertices of every edge, if both subsets are same,
  // then there is cycle in graph.
  for (uint32_t i = 0; i < edges.size(); ++i) {
    const uint32_t x = find(edges[i].src);
    const uint32_t y = find(edges[i].dst);
    if (x == y)
      return true;

    Union(x, y);
  }

  return false;
}

/*
A Hamiltonian cycle (or Hamiltonian circuit) is a Hamiltonian Path such that there is an edge (in graph) from the last vertex
to the first vertex of the Hamiltonian Path. Determine whether a given graph contains Hamiltonian Cycle or not.
If it contains, then print the path. Following are the input and output of the required function.

Input:
A 2D array graph[V][V] where V is the number of vertices in graph and graph[V][V] is adjacency matrix representation
of the graph. A value graph[i][j] is 1 if there is a direct edge from i to j, otherwise graph[i][j] is 0.

Output:
An array path[V] that should contain the Hamiltonian Path. path[i] should represent the ith vertex in the Hamiltonian Path.
The code should also return false if there is no Hamiltonian Cycle in the graph.
 */
#define V 5

/* This function solves the Hamiltonian Cycle problem using backtracking.
   Please note that there may be more than one solutions, this function prints one of the feasible solutions. */
bool hamiltonianCycle(const bool graph[V][V], vector<int32_t>& path) {
  path.resize(V);
  for (auto& i : path)
    i = -1;
  path[0] = 0; /* put vertex 0 as the first vertex in the path. If there is a Hamiltonian Cycle,
                  then the path can be started from any point of the cycle as the graph is undirected */

  function<bool(const int32_t,const uint32_t)> isSafe =
    [&](const int32_t v, const uint32_t pos) { /* Check if the vertex v can be added at index 'pos'
                                                  in the Hamiltonian Cycle constructed so far (stored in 'path[]') */
    /* Check if this vertex is an adjacent vertex of the previously added vertex. */
    if (!graph[path[pos-1]][v])
      return false;

    /* Check if the vertex has already been included. This step can be optimized by creating an array of size V */
    for (uint32_t i = 0; i < pos; ++i)
      if (path[i] == v)
        return false;

    return true;
  };

  function<bool(const uint32_t)> solve = [&](const uint32_t pos) { // backtracking
    if (pos == V) { // If all vertices are included in Hamiltonian Cycle and
                    // if there is an edge from the last included vertex to the first vertex
      return graph[path[pos-1]][path[0]];
    }

    // Try different vertices as a next candidate in Hamiltonian Cycle.
    // We don't try for 0 as we included 0 as starting point
    for (uint32_t i = 1; i < V; ++i) {
      /* Check if this vertex can be added to Hamiltonian Cycle */
      if (isSafe(i, pos)) {
        path[pos] = i;

        /* recur to construct rest of the path */
        if (solve(pos+1))
          return true;

        /* If adding vertex doesn't lead to a solution, then remove it */
        path[pos] = -1;
      }
    }

    /* If no vertex can be added to Hamiltonian Cycle constructed so far, then return false */
    return false;
  };

  if (solve(1)) {
 //   cout << "Solution exists!" << endl;
    return true;
  }

  return false;
}

/*
Let the subset {0, 1, .. 9} be represented as below and find() is called
for element 3.
              9
         /    |    \
        4     5      6
     /     \        /  \
    0        3     7    8
            /  \
           1    2

When find() is called for 3, we traverse up and find 9 as representative of this subset.
With path compression, we also make 3 as child of 9 so that when find() is called next time for 1, 2 or 3,
the path to root is reduced.
               9
         /    /  \    \
        4    5    6     3
     /           /  \   /  \
    0           7    8  1   2

The two techniques complement each other. The time complexity of each operations becomes even smaller than O(Logn).
In fact, amortized time complexity effectively becomes small constant.
 */
struct Subset {
  uint32_t parent;
  uint32_t rank;
};

bool UndirectedGraph::cycleExists2() {
  Subset subsets[V];

  for (uint32_t v = 0; v < V; ++v) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  function<const uint32_t(const uint32_t)> find =
    [&](const uint32_t i) -> const uint32_t {
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
      subsets[i].parent = find(subsets[i].parent);

    return subsets[i].parent;
  };

  function<void(const uint32_t,const uint32_t)> Union =
    [&](const uint32_t x, const uint32_t y) {
    const uint32_t xroot = find(x);
    const uint32_t yroot = find(y);

    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
      subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
      subsets[yroot].parent = xroot;
    else { // If ranks are same, then make one as root and increment its rank by one
      subsets[yroot].parent = xroot;
      ++subsets[xroot].rank;
    }
  };

  // Iterate through all edges of graph, find sets of both vertices of every edge, if sets are same,
  // then there is cycle in graph.
  for (uint32_t e = 0; e < edges.size(); ++e) {
    const uint32_t x = find(edges[e].src);
    const uint32_t y = find(edges[e].dst);
    if (x == y)
      return true;

    Union(x, y);
  }

  return false;
}

/*
Given a graph and a source vertex src in graph, find shortest paths from src to all vertices in the given graph.
The graph may contain negative weight edges.

The algorithm calculates shortest paths in bottom-up manner. It first calculates the shortest distances for
the shortest paths which have at-most one edge in the path. Then, it calculates shortest paths with at-most 2 edges, and so on.
After the ith iteration of outer loop, the shortest paths with at most i edges are calculated.
There can be maximum |V|-1 edges in any simple path, that is why the outer loop runs |v|-1 times.
The idea is, assuming that there is no negative weight cycle, if we have calculated shortest paths with at most i edges,
then an iteration over all edges guarantees to give shortest path with at-most (i+1) edges.
 */
void bellmanFord(const UndirectedGraph* graph, int32_t src) {
  if (!graph)
    return;

  uint32_t dist[V];
  for (auto& i : dist)
    dist[i] = MAX_LIMIT;
  dist[src] = 0;

  // Relax all edges |V|-1 times. A simple shortest path from src to any other vertex can have at-most |V|-1 edges
  for (uint32_t i = 1; i < graph->V; ++i) {
    for (uint32_t j = 0; j < graph->edges.size(); ++j) {
      int32_t u = graph->edge[j].src;
      int32_t v = graph->edge[j].dst;
      int32_t weight = graph->edges[j].weight;

      if (dist[u] != MAX_LIMIT && dist[u]+weight < dist[v])
        dist[v] = dist[u]+weight;
    }
  }

  // Check for negative-weight cycles. The above step guarantees shortest distances if graph doesn't contain
  // negative weight cycle. If we get a shorter path, then there is a cycle.
  for (uint32_t i = 0; i < graph->edges.size(); i++) {
    int32_t u = graph->edge[i].src;
    int32_t v = graph->edge[i].dst;
    int32_t weight = graph->edge[i].weight;
    if (dist[u] != MAX_LIMIT && dist[u]+weight < dist[v])
      cout << "Graph contains negative weight cycle." << endl;
  }
}

bool isBipartite(int32_t G[][V], const int32_t src) {
  // Create a color array to store colors assigned to all veritces. Vertex number is used as index in this array.
  // The value '-1' of  colorArr[i] is used to indicate that no color is assigned to vertex 'i'.
  // The value 1 is used to indicate first color is assigned and value 0 indicates second color is assigned.
  int32_t colorArr[V];
  for (auto& i : colorArr)
    i = -1;
  colorArr[src] = 1;

  // Create a queue (FIFO) of vertex numbers and enqueue source vertex for BFS traversal
  deque<int32_t> q = {src};

  // Run while there are vertices in queue (Similar to BFS)
  while (!q.empty()) {
    // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
    int32_t u = q.front();
    q.pop_front();

    // Find all non-colored adjacent vertices
    for (uint32_t v = 0; v < V; ++v) {
      // An edge from u to v exists and destination v is not colored
      if (G[u][v] && colorArr[v] == -1) {
        // Assign alternate color to this adjacent v of u
        colorArr[v] = 1-colorArr[u];
        q.push(v);
      } else if (G[u][v] && colorArr[v] == colorArr[u]) // An edge from u to v exists and destination v is colored with same color as u
        return false;
    }
  }

  // If we reach here, then all adjacent vertices can be colored with alternate color
  return true;
}

/*
A vertex in an undirected connected graph is an articulation point (or cut vertex) if removing it (and edges through it)
disconnects the graph. Articulation points represent vulnerabilities in a connected network.
Single points whose failure would split the network into 2 or more disconnected components.
They are useful for designing reliable networks.
For a disconnected undirected graph, an articulation point is a vertex removing which increases number of connected components.

A O(V+E) algorithm to find all Articulation Points (APs)
The idea is to use DFS (Depth First Search). In DFS, we follow vertices in tree form called DFS tree.
In DFS tree, a vertex u is parent of another vertex v, if v is discovered by u (obviously v is an adjacent of u in graph).
In DFS tree, a vertex u is articulation point if one of the following two conditions is true:
1) u is root of DFS tree and it has at least two children.
2) u is not root of DFS tree and it has a child v such that no vertex in subtree rooted with v has a back edge to
   one of the ancestors (in DFS tree) of u.
 */
void UndirectedGraph::AP() {
  // Mark all the vertices as not visited
  bool visited[V];
  int32_t disc[V];
  int32_t low[V];
  int32_t parent[V];
  bool ap[V]; // To store articulation points

  // Initialize parent and visited, and ap(articulation point) arrays
  for (uint32_t i = 0; i < V; ++i) {
    parent[i] = -1;
    visited[i] = false;
    ap[i] = false;
  }

  function<void(const uint32_t)> solve = [&](const uint32_t u) {
    // A static variable is used for simplicity, we can avoid use of static
    // variable by passing a pointer.
    static uint32_t time = 0;

    // Count of children in DFS Tree
    uint32_t children = 0;
    // Mark the current node as visited
    visited[u] = true;
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    for (auto i : adjs[u]) {
      int32_t v = i;  // v is current adjacent of u
      // If v is not visited yet, then make it a child of u in DFS tree and recur for it
      if (!visited[v]) {
        ++children;
        parent[v] = u;
        solve(v);

        // Check if the subtree rooted with v has a connection to one of the ancestors of u
        low[u] = min(low[u], low[v]);

        // u is an articulation point in following cases:
        // (1) u is root of DFS tree and has two or more chilren.
        if (parent[u] == -1 && children > 1)
          ap[u] = true;
        // (2) If u is not root and low value of one of its child is more than discovery value of u.
        if (parent[u] != -1 && low[v] >= disc[u])
          ap[u] = true;
      } else if (v != parent[u]) // Update low value of u for parent function calls.
        low[u] = min(low[u], disc[v]);
    }
  };

  // Call the recursive helper function to find articulation points in DFS tree rooted with vertex 'i'
  for (uint32_t i = 0; i < V; ++i)
    if (!visited[i])
      solve(i);

  // Now ap[] contains articulation points, print them
  for (uint32_t i = 0; i < V; ++i)
    if (ap[i] == true)
      cout << i << " ";
}

/*
An edge in an undirected connected graph is a bridge iff removing it disconnects the graph.
For a disconnected undirected graph, definition is similar, a bridge is an edge removing which increases number of
connected components.
Like Articulation Points,bridges represent vulnerabilities in a connected network and are useful for
designing reliable networks. For example, in a wired computer network, an articulation point indicates
the critical computers and a bridge indicates the critical wires or connections.

A O(V+E) algorithm to find all Bridges
The idea is similar to O(V+E) algorithm for Articulation Points. We do DFS traversal of the given graph.
In DFS tree an edge (u, v) (u is parent of v in DFS tree) is bridge if there does not exit any other alternative to
reach u or an ancestor of u from subtree rooted with v. As discussed in the previous post,
the value low[v] indicates earliest visited vertex reachable from subtree rooted with v.
The condition for an edge (u, v) to be a bridge is, low[v] > disc[u].
 */
void UndirectedGraph::bridge() {
  // Mark all the vertices as not visited
  bool visited[V];
  int32_t disc[V];
  int32_t low[V];
  int32_t parent[V];

  for (uint32_t i = 0; i < V; ++i) {
    parent[i] = -1;
    visited[i] = false;
  }

  function<void(const uint32_t)> solve = [&](const uint32_t u) {
    // A static variable is used for simplicity, we can avoid use of static variable by passing a pointer.
    static uint32_t time = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    for (auto i : adjs[u]) {
      int32_t v = i;  // v is current adjacent of u
      // If v is not visited yet, then recur for it
      if (!visited[v]) {
        parent[v] = u;
        solve(v);

        // Check if the subtree rooted with v has a connection to one of the ancestors of u
        low[u] = min(low[u], low[v]);
        // If the lowest vertex reachable from subtree under v is below u in DFS tree, then u-v is a bridge
        if (low[v] > disc[u])
          cout << u <<" " << v << endl;
      } else if (v != parent[u]) // Update low value of u for parent function calls.
        low[u] = min(low[u], disc[v]);
    }
  };

  // Call the recursive helper function to find Bridges in DFS tree rooted with vertex 'i'
  for (uint32_t i = 0; i < V; ++i)
    if (!visited[i])
      solve(i);
}

/*
An undirected graph is called Biconnected if there are two vertex-disjoint paths between any two vertices.
In a Biconnected Graph, there is a simple cycle through any two vertices.
By convention, two nodes connected by an edge form a biconnected graph, but this does not verify the above properties.
For a graph with more than two vertices, the above properties must be there for it to be Biconnected.

A connected graph is Biconnected if it is connected and doesn't have any Articulation Point.
We mainly need to check two things in a graph.
1) The graph is connected.
2) There is not articulation point in graph.
 */
bool UndirectedGraph::isBc() {
  bool visited[V];
  int32_t disc[V];
  int32_t low[V];
  int32_t parent[V];

  for (uint32_t i = 0; i < V; ++i) {
    parent[i] = -1;
    visited[i] = false;
  }

  function<bool(const uint32_t)> solve = [&](const uint32_t u) {
    // A static variable is used for simplicity, we can avoid use of static variable by passing a pointer.
    static uint32_t time = 0;

    // Count of children in DFS Tree
    uint32_t children = 0;
    // Mark the current node as visited
    visited[u] = true;
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    // Go through all vertices aadjacent to this
    for (auto i : adjs[u]) {
      int32_t v = i;  // v is current adjacent of u
      // If v is not visited yet, then make it a child of u in DFS tree and recur for it
      if (!visited[v]) {
        ++children;
        parent[v] = u;

        // check if subgraph rooted with v has an articulation point
        if (solve(v))
          return true;

        // Check if the subtree rooted with v has a connection to one of the ancestors of u
        low[u] = min(low[u], low[v]);
        // u is an articulation point in following cases
        // (1) u is root of DFS tree and has two or more chilren.
        if (parent[u] == -1 && children > 1)
          return true;

        // (2) If u is not root and low value of one of its child is more than discovery value of u.
        if (parent[u] != -1 && low[v] >= disc[u])
          return true;
      } else if (v != parent[u]) // Update low value of u for parent function calls.
        low[u]  = min(low[u], disc[v]);
    }

    return false;
  };

  // Call the recursive helper function to find if there is an articulation point in given graph.
  // We do DFS traversal starring from vertex 0
  if (solve(0))
    return false;

  // Now check whether the given graph is connected or not.
  // An undirected graph is connected if all vertices are reachable from
  // any starting point (we have taken 0 as starting point)
  for (auto i : visited)
    if (!i)
      return false;

  return true;
}

/* The function returns one of the following values
   0 --> If grpah is not Eulerian
   1 --> If graph has an Euler path (Semi-Eulerian)
   2 --> If graph has an Euler Circuit (Eulerian)  */
uint8_t UndirectedGraph::isEulerian() {
  function<bool(void)> isConnected = []() {
    bool visited[V];
    for (auto& i : visited)
      i = false;

    // Find a vertex with non-zero degree
    uint32_t i = 0;
    for (; i < V; ++i)
      if (adjs[i].size())
        break;

    // If there are no edges in the graph, return true
    if (i == V)
      return true;

    // Start DFS traversal from a vertex with non-zero degree
    DFS(i, visited);

    // Check if all non-zero degree vertices are visited
    for (i = 0; i < V; ++i)
      if (!visited[i] && adjs[i].size() > 0)
        return false;

    return true;
  };

  // Check if all non-zero degree vertices are connected
  if (!isConnected())
    return 0;

  // Count vertices with odd degree
  uint32_t odd = 0;
  for (uint32_t i = 0; i < V; ++i)
    if (adjs[i].size() & 1)
      ++odd;

  // If count is more than 2, then graph is not Eulerian
  if (odd > 2)
    return 0;

  // If odd count is 2, then semi-eulerian.
  // If odd count is 0, then eulerian
  // Note that odd count can never be 1 for undirected graph
  return (odd) ? 1 : 2;
}

/*
 */
int32_t fordFulkerson(int32_t graph[V][V], int s, int t) {
  int u, v;

  // Create a residual graph and fill the residual graph with given capacities in the original graph
  // as residual capacities in residual graph
  int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates residual capacity of edge from i to j
                    // (if there is an edge. If rGraph[i][j] is 0, then there is not)
  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++)
      rGraph[u][v] = graph[u][v];

  int32_t parent[V];  // This array is filled by BFS and to store path
  uint32_t max_flow = 0;  // There is no flow initially

  // Augment the flow while tere is path from source to sink
  while (bfs(rGraph, s, t, parent)) {
    // Find minimum residual capacity of the edhes along the path filled by BFS.
    // Or we can say find the maximum flow through the path found.
    int path_flow = INT_MAX;
    for (v=t; v!=s; v=parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rGraph[u][v]);
    }

    // update residual capacities of the edges and reverse edges along the path
    for (v=t; v != s; v=parent[v]) {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }

    // Add path flow to overall flow
    max_flow += path_flow;
  }

  // Return the overall flow
  return max_flow;
}

/*
Given an undirected and unweighted graph, find the smallest cut
(smallest number of edges that disconnects the graph into two components).
The input graph may have parallel edges.
 */
// A very basic implementation of Karger's randomized algorithm for finding the
// minimum cut. Please note that Karger's algorithm is a Monte Carlo Randomized
// algo and the cut returned by the algorithm may not be minimum always.
uint32_t kargerMinCut(UndirectedGraph* graph) {
  if (!graph)
    return 0;

  Subset subsets[V];
  for (uint32_t v = 0; v < V; ++v) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  function<int32_t(const uint32_t)> find = [&](const uint32_t i) {
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
      subsets[i].parent = find(subsets[i].parent);

    return subsets[i].parent;
  };

  // A function that does union of two sets of x and y (uses union by rank)
  function<void(const int32_t,const int32_t)> Union = [&](const int32_t x, const int32_t y) {
    int32_t xroot = find(x);
    int32_t yroot = find(y);

    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
      subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
      subsets[yroot].parent = xroot;
    else { // If ranks are same, then make one as root and increment its rank by one
      subsets[yroot].parent = xroot;
      ++subsets[xroot].rank;
    }
  };

  // Initially there are V vertices in contracted graph
  uint32_t vertices = V;

  // Keep contracting vertices until there are 2 vertices.
  while (vertices > 2) {
    // Pick a random edge
    uint32_t i = rand() % graph->edges.size(0;

    // Find vertices (or sets) of two corners of current edge
    int32_t subset1 = find(subsets, edge[i].src);
    int32_t subset2 = find(subsets, edge[i].dst);

    // If two corners belong to same subset then no point considering this edge
    if (subset1 == subset2)
      continue;
    else { // Else contract the edge (or combine the corners of edge into one vertex)
      cout << "Contracting edge " << edges[i].src << "-" << edges[i].dst;
      --vertices;
      Union(subset1, subset2);
    }
  }

  // Now we have two vertices (or subsets) left in the contracted graph, so count the edges
  // between two components and return the count.
  uint32_t cutedges = 0;
  for (uint32_t i = 0; i < graph->edges.size(); ++i) {
    int32_t subset1 = find(subsets, edge[i].src);
    int32_t subset2 = find(subsets, edge[i].dst);
    if (subset1 != subset2)
      ++cutedges;
  }

  return cutedges;
}

/*
Given a dictionary, a method to do lookup in dictionary and a M x N board where every cell has one character.
Find all possible words that can be formed by a sequence of adjacent characters.
Note that we can move to any of 8 adjacent characters, but a word should not have multiple instances of same cell.

Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
       boggle[][]   = {{'G','I','Z'},
                       {'U','E','K'},
                       {'Q','S','E'}};
       isWord(str): returns true if str is present in dictionary, else false.

Output:  Following words of dictionary are present
         GEEKS
         QUIZ
 */
vector<string> findWords(const char boggle[M][N], const set<string>& dict) {
  vector<string> ret;
  bool visited[M][N] = {{false}};
  string to_ext = "";

  function<void(const uint8_t,const uint8_t)> backtrack =
    [&](const uint8_t row, const uint8_t col) {
    visited[row][col] = true;
    to_ext += boggle[row][col];

    // If str is present in dictionary, then print it
    if (dict.count(to_ext))
      ret.push_back(to_ext);

    // Traverse 8 adjacent cells of boggle[i][j]
    for (uint8_t i = row-1; i <= row+1 && i < M; ++i)
      for (uint8_t j = col-1; j <= col+1 && j < N; ++j)
        if (i >= 0 && j >= 0 && !visited[i][j])
          backtrack(i, j);

    // Erase current character from string and mark visited of current cell as false
    to_ext.erase(to_ext.length()-1);
    visited[row][col] = false;
  };

  // Consider every character and look for all words starting with this character
  for (uint8_t i = 0; i < M; ++i)
    for (uint8_t j = 0; j < N; ++j)
      backtrack(i, j);
}

/*
A vertex cover of an undirected graph is a subset of its vertices such that for every edge (u, v) of the graph,
either u or v is in vertex cover. Although the name is Vertex Cover, the set covers all edges of the given graph.
Given an undirected graph, the vertex cover problem is to find minimum size vertex cover.
 */
void UndirectedGraph::vertexCover() {
  bool visited[V];
  for (auto& i : visited)
    i = false;

  // Consider all edges one by one
  for (uint32_t u = 0; u < V; ++u) {
    // An edge is only picked when both visited[u] and visited[v] are false
    if (!visited[u]) {
      // Go through all adjacents of u and pick the first not yet visited vertex
      // (We are basically picking an edge (u, v) from remaining edges.
      for (auto i : adj[u]) {
        uint32_t v = i;
        if (!visited[v]) {
          // Add the vertices (u, v) to the result set. We make the vertex u and v visited
          // so that all edges from/to them would be ignored
          visited[v] = true;
          visited[u]  = true;
          break;
        }
      }
    }
  }

  for (uint32_t i = 0; i < V; ++i)
    if (visited[i])
      cout << i << " ";
}

int main(int argc, char** argv) {
  /* Let us create the following graph
    (0)--(1)--(2)
      |   / \   |
      |  /   \  |
      | /     \ |
    (3)-------(4)    */
  bool graph1[V][V] = {{0, 1, 0, 1, 0},
                       {1, 0, 1, 1, 1},
                       {0, 1, 0, 0, 1},
                       {1, 1, 0, 0, 1},
                       {0, 1, 1, 1, 0}};

  hamiltonianCycle(graph1);

  /* Let us create the following graph
    (0)--(1)--(2)
      |   / \   |
      |  /   \  |
      | /     \ |
    (3)       (4)    */
  bool graph2[V][V] = {{0, 1, 0, 1, 0},
                       {1, 0, 1, 1, 1},
                       {0, 1, 0, 0, 1},
                       {1, 1, 0, 0, 0},
                       {0, 1, 1, 0, 0}};

  hamiltonianCycle(graph2);

  /*
  adjacency_list_t adjs(6);
  // 0 = a
  adjs[0].push_back(Neighbor(1, 7));
  adjs[0].push_back(Neighbor(2, 9));
  adjs[0].push_back(Neighbor(5, 14));
  // 1 = b
  adjs[1].push_back(Neighbor(0, 7));
  adjs[1].push_back(Neighbor(2, 10));
  adjs[1].push_back(Neighbor(3, 15));
  // 2 = c
  adjs[2].push_back(Neighbor(0, 9));
  adjs[2].push_back(Neighbor(1, 10));
  adjs[2].push_back(Neighbor(3, 11));
  adjs[2].push_back(Neighbor(5, 2));
  // 3 = d
  adjs[3].push_back(Neighbor(1, 15));
  adjs[3].push_back(Neighbor(2, 11));
  adjs[3].push_back(Neighbor(4, 6));
  // 4 = e
  adjs[4].push_back(Neighbor(3, 6));
  adjs[4].push_back(Neighbor(5, 9));
  // 5 = f
  adjs[5].push_back(Neighbor(0, 14));
  adjs[5].push_back(Neighbor(2, 2));
  adjs[5].push_back(Neighbor(4, 9));

  vector<weight_t> min_dist;
  vector<vertex_t> previous;
  Dijkstra(0, adjs, min_dist, previous);
  cout << "Distance from 0 to 4: " << min_dist[4] << std::endl;
  list<vertex_t> path = shortestPathTo(4, previous);
  cout << "Path: ";
  copy(path.begin(), path.end(), ostream_iterator<vertex_t>(cout, " "));
  cout << endl;
*/
  return 0;
}
