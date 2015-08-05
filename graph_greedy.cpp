#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct Edge {
  uint32_t src, dst;
  uint32_t weight;
};

struct UndirectedGraph {
  uint32_t V; // number of vertices
  vector<Edge> edges; // graph is represented as an array of edges

  void addEdge(const uint32_t src, const uint32_t dst, const uint32_t weight) {
    edges.push_back({src, dst, weight});
  }
};

struct Subset {
  uint32_t parent;
  uint32_t rank;
};

/*
Given a connected and undirected graph, a spanning tree of that graph is a subgraph that is a tree and connects all the vertices together. A single graph can have many different spanning trees. A minimum spanning tree (MST) or minimum weight spanning tree for a weighted, connected and undirected graph is a spanning tree with weight less than or equal to the weight of every other spanning tree. The weight of a spanning tree is the sum of weights given to each edge of the spanning tree.

The algorithm is a Greedy Algorithm. The Greedy Choice is to pick the smallest weight edge that does not cause a cycle in the MST constructed so far.
 */
void UndirectedGraph::Kruskal() {
  Edge result[V];

  // Step 1: sort all the edges in non-decreasing order of their weight.
  //qsort(graph->edges, graph->E, sizeof(graph->edge[0]), myComp);
  sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.weight > b.weight; });

  Subset subsets[V];
  // Create V subsets with single elements
  for (uint32_t v = 0; v < V; ++v) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  function<uint32_t(const uint32_t)> find = [&](const uint32_t i) { // find set of an element i (uses path compression technique)
    if (subsets[i].parent != i) // find root and make root as parent of i (path compression)
      subsets[i].parent = find(subsets[i].parent);

    return subsets[i].parent;
  };

  function<void(const uint32_t,const uint32_t)> Union = // union of two sets of x and y (uses union by rank)
    [&](const uint32_t x, const uint32_t y) {
    uint32_t xroot = find(x);
    uint32_t yroot = find(y);

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

  uint32_t i = 0; // index for sorted edges
  uint32_t e = 0;
  while (e < V-1) { // V-1 edges to be taken now
    const Edge& next_edge = edges[i++]; // Step 2: pick the smallest edge and increment the index for next iteration
    uint32_t x = find(next_edge.src);
    uint32_t y = find(next_edge.dst);
    if (x != y) { // If including this edge does't cause cycle, include it in result and increment the index of result for next edge
      result[e++] = next_edge;
      Union(x, y);
    }
    // discard next_edge if it creates cycle
  }
}

/*
Given a graph and a source vertex in graph, find shortest paths from source to all vertices in the given graph.

Dijkstra's algorithm generates a SPT (shortest path tree) with given source as root. We maintain two sets, one set contains vertices included in shortest path tree, other set includes vertices not yet included in shortest path tree. At every step of the algorithm, we find a vertex which is in the other set (set of not yet included) and has minimum distance from source.
 */
/*
typedef uint32_t vertex_t;
typedef double weight_t;

const weight_t max_weight = numeric_limits<double>::infinity();

struct Neighbor {
  vertex_t target;
  weight_t weight;

  Neighbor(const vertex_t target_, const weight_t weight_)
      : target(target_), weight(weight_) {
  }
};

typedef vector<vector<Neighbor>> adjacency_list_t;

void Dijkstra(vertex_t source,
              const adjacency_list_t& adjs,
              vector<weight_t>& min_dist,
              vector<vertex_t>& previous) {
  const uint32_t n = adjs.size();
  min_dist.clear();
  min_dist.resize(n, max_weight);
  min_dist[source] = 0;
  previous.clear();
  previous.resize(n, -1);
  set<pair<weight_t,vertex_t>> vertex_q;
  vertex_q.insert(make_pair(min_dist[source], source));

  while (!vertex_q.empty()) {
    weight_t dist = vertex_q.begin()->first;
    vertex_t u = vertex_q.begin()->second;
    vertex_q.erase(vertex_q.begin());

    // Visit each edge exiting u
    const vector<Neighbor>& neighbors = adjs[u];
    for (auto& i : neighbors) {
      vertex_t v = i.target;
      weight_t weight = i.weight;
      weight_t dist_thru_u = dist+weight;
      if (dist_thru_u < min_dist[v]) {
        vertex_q.erase(make_pair(min_dist[v], v));
        min_dist[v] = dist_thru_u;
        previous[v] = u;
        vertex_q.insert(make_pair(min_dist[v], v));
      }
    }
  }
}

list<vertex_t> shortestPathTo(const vertex_t vertex, const vector<vertex_t>& previous) {
  list<vertex_t> ret;
  for (; vertex != -1; vertex = previous[vertex])
    ret.push_front(vertex);

  return ret;
}
*/
void Dijkstra(const uint32_t graph[V][V], const uint32_t src) {
  uint32_t min_dist[V]; // dist[i] will hold the shortest distance from src to i
  bool spt[V]; // spt[i] will true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

  for (uint32_t i = 0; i < V; ++i) {
    min_dist[i] = MAX_LIMIT;
    spt[i] = false;
  }
  min_dist[src] = 0; // Distance of source vertex from itself is always 0

  function<uint32_t(void)> minDist = [&](void) { // find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
    // Initialize min value
    uint32_t tmp = MAX_LIMIT;
    uint32_t min_idx = src;

    for (uint32_t v = 0; v < V; ++v) {
      if (!spt[v] && min_dist[v] <= tmp) {
        tmp = min_dist[v];
        min_idx = v;
      }
    }

    return min_idx;
  };

  // Find shortest path for all vertices
  for (uint32_t i = 0; i < V-1; ++i) {
    // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in first iteration.
    const uint32_t u = minDist();
    spt[u] = true; // Mark the picked vertex as processed

    // Update dist value of the adjacent vertices of the picked vertex.
    for (uint32_t v = 0; v < V; ++v) {
      // Update new_dist[v] only if is not in spt, there is an edge from u to
      // v, and total weight of path from src to v through u is smaller than
      // current value of min_dist[v]
      const uint32_t new_dist = min_dist[u]+graph[u][v];
      if (!spt[v] && graph[u][v] && min_dist[u] != MAX_LIMIT && new_dist < min_dist[v])
        min_dist[v] = new_dist;
    }
  }

  for (auto i : dist)
    cout << i << " ";
}

/*
 */
void Prim(const uint32_t graph[V][V]) {
  int32_t parent[V]; // Array to store constructed MST
  int32_t key[V];   // Key values used to pick minimum weight edge in cut
  bool mst[V];  // To represent set of vertices not yet included in MST

  for (uint32_t i = 0; i < V; ++i) {
    key[i] = MAX_LIMIT;
    mst[i] = false;
  }

  function<uint32_t(void)> minkey = [&]() {
    uint32_t min = MAX_LIMIT;
    uint32_t min_idx;

    for (uint32_t v = 0; v < V; ++v)
      if (!mst[v] && key[v] < min)
        min = key[v], min_idx = v;

    return min_idx;
  };

  // Always include first 1st vertex in MST.
  key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
  parent[0] = -1; // First node is always root of MST

  // The MST will have V vertices
  for (uint32_t i = 0; i < V-1; ++i) {
    // Pick thd minimum key vertex from the set of vertices not yet included in MST
    uint32_t u = minkey();
    // Add the picked vertex to the MST Set
    mst[u] = true;

    // Update key value and parent index of the adjacent vertices of the picked vertex. Consider only those vertices which are not yet included in MST
    for (uint32_t v = 0; v < V; i++)
      // graph[u][v] is non zero only for adjacent vertices of m, mst[v] is
      // false for vertices not yet included in MST. Update the key only if graph[u][v] is smaller than key[v]
      if (graph[u][v] && !mst[v] && graph[u][v] < key[v])
        parent[v]  = u, key[v] = graph[u][v];
  }
}

int main(int argc, char** argv) {
  /* Create following weighted graph
             10
        0--------1
        |  \     |
       6|   5\   |15
        |      \ |
        2--------3
            4
   */

  uint32_t V = 4;  // Number of vertices in graph
 //   int E = 5;  // Number of edges in graph
  UndirectedGraph graph;
  graph.V = V;
  graph.edges.resize(5);

  // add edge 0-1
  graph.edges[0].src = 0;
  graph.edges[0].dst = 1;
  graph.edges[0].weight = 10;

  // add edge 0-2
  graph.edges[1].src = 0;
  graph.edges[1].dst = 2;
  graph.edges[1].weight = 6;

  // add edge 0-3
  graph.edges[2].src = 0;
  graph.edges[2].dst = 3;
  graph.edges[2].weight = 5;

  // add edge 1-3
  graph.edges[3].src = 1;
  graph.edges[3].dst = 3;
  graph.edges[3].weight = 15;

  // add edge 2-3
  graph.edges[4].src = 2;
  graph.edges[4].dst = 3;
  graph.edges[4].weight = 4;

  graph.kruskalMST();

  return 0;
}
