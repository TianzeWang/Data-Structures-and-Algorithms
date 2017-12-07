#include <iostream>
#include <sstream>
#include <algorithm>
#include <climits>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <vector>

using namespace std;

struct Node;
struct Edge;

struct Node {
  int code = 0;
  int D = 0;
  list<Edge> adjacent_list;
  list<Edge> undirected_list;
  int degree = 0;
};

struct Edge {
  Node *end_node;
  int weight = 0;
};

bool comp_node_degree(const Node *a, const Node *b) {
  return a->degree < b->degree;
}

bool comp_node_code(const Node *a, const Node *b) {
  return a->code < b->code;
}

struct comp_Edge {
  bool operator()(const Node *a, const Node *b) const {
    return a->code < b->code;
  }
};

struct Graph {
  vector<Node *> NodeAll_vec; // compare by in_degree
  multimap<Node *, Edge, comp_Edge> EdgeAll_map; // compare by code
  multimap<Node *, Edge, comp_Edge> Undirected_EdgeAll_map; //compare by code
};

struct comp_D {
  bool operator()(const Node *a, const Node *b) const {
    return a->D < b->D;
  }
};

void DAG(Graph graph);

void Shortest_Path(Graph graph, int source_node_code, int destination_node_code);

void MST(Graph graph);

int main() {
  int N; // number of nodes in the graph
  int source_node_code, destination_node_code; // source node and destination node
  cin >> N >> source_node_code >> destination_node_code;
  Graph graph = Graph();
  for (int i = 0; i < N; i++) {
    graph.NodeAll_vec.push_back(new Node);
  }
  getchar();
  stringstream ss;
  while (!cin.eof()) {
    string str;
    getline(cin, str);
    if (str.empty()) {
      break;
    }
    ss.clear();
    ss.str(str);
    int node_start_code, node_end_code;
    Edge edge_temp;
    Edge undirected_edge_temp_1;
    Edge undirected_edge_temp_2;
    ss >> node_start_code >> node_end_code >> edge_temp.weight;
    undirected_edge_temp_1.weight = undirected_edge_temp_2.weight = edge_temp.weight;
    graph.NodeAll_vec[node_start_code]->code = node_start_code;
    graph.NodeAll_vec[node_end_code]->code = node_end_code;
    graph.NodeAll_vec[node_end_code]->degree++;
    graph.NodeAll_vec[node_start_code]->D = graph.NodeAll_vec[node_end_code]->D = 0;
    edge_temp.end_node = graph.NodeAll_vec[node_end_code];
    undirected_edge_temp_1.end_node = graph.NodeAll_vec[node_end_code];
    undirected_edge_temp_2.end_node = graph.NodeAll_vec[node_start_code];
    graph.NodeAll_vec[node_start_code]->adjacent_list.push_back(edge_temp);
    graph.NodeAll_vec[node_start_code]->undirected_list.push_back(undirected_edge_temp_1);
    graph.NodeAll_vec[node_end_code]->undirected_list.push_back(undirected_edge_temp_2);
    graph.EdgeAll_map.insert(make_pair(graph.NodeAll_vec[node_start_code], edge_temp));
    graph.Undirected_EdgeAll_map.insert(make_pair(graph.NodeAll_vec[node_start_code], undirected_edge_temp_1));
    graph.Undirected_EdgeAll_map.insert(make_pair(graph.NodeAll_vec[node_end_code], undirected_edge_temp_2));
  }
  // shortest path determination
  Shortest_Path(graph, source_node_code, destination_node_code);
  // DAG determination
  DAG(graph);
  // MST determination
  MST(graph);
  return 0;
}

void DAG(Graph graph) {
  std::sort(graph.NodeAll_vec.begin(), graph.NodeAll_vec.end(), comp_node_degree);
  vector<Node *> S; // construct a vector to store nodes whose in_degree is zero
  for (auto &it : graph.NodeAll_vec) {
    if (it->degree == 0) {
      S.push_back(it);
    } else {
      break;
    }
  }
  std::sort(graph.NodeAll_vec.begin(), graph.NodeAll_vec.end(), comp_node_code);
  while (!S.empty()) {
    auto n = *S.begin();
    S.erase(S.begin());
    for (auto it = n->adjacent_list.begin(); it != n->adjacent_list.end(); ++it) {
      auto m = it->end_node;
      for (auto tt = graph.EdgeAll_map.begin(); tt != graph.EdgeAll_map.end(); ++tt) {
        if (tt->first == n && tt->second.end_node == m) { // edge from n to m
          graph.EdgeAll_map.erase(tt); // erase this edge
          break;
        }
      }
      m->degree--;
      if (!m->degree) {
        S.push_back(m);
      }
    }
  }
  if (!graph.EdgeAll_map.empty()) {
    cout << "The graph is not a DAG" << endl;
  } else {
    cout << "The graph is a DAG" << endl;
  }
}

void Shortest_Path(Graph graph, int source_node_code, int destination_node_code) {
  multiset<Node *, comp_D> R; // construct a set to store nodes by their D value
  std::sort(graph.NodeAll_vec.begin(),
            graph.NodeAll_vec.end(),
            comp_node_code); // make NodeAll.vec ordered by node_code
  for (auto &it : graph.NodeAll_vec) { // initialize each node
    it->D = INT_MAX;
  }
  graph.NodeAll_vec[source_node_code]->D = 0;  // set D(s) to zero
  for (auto &it : graph.NodeAll_vec) { // insert each node into set
    R.insert(it);
  }
  while (!R.empty()) {
    auto v = *R.begin();
    if (v == graph.NodeAll_vec[destination_node_code]) {
      break;
    }
    R.erase(R.begin());

    auto size = v->adjacent_list.size();
    if (!size) {
      continue;
    }

    for (auto v_neighbor_it = v->adjacent_list.begin(); v_neighbor_it != v->adjacent_list.end(); ++v_neighbor_it) {
      auto u = v_neighbor_it->end_node; // u is v's neighbor
      for (auto it = R.begin(); it != R.end(); ++it) {
        if (*it == u) {
          auto it_u = it;
          int W_u_v = 0;
          for (auto &tt : graph.EdgeAll_map) {
            if (tt.first == v && tt.second.end_node == u) {
              W_u_v = tt.second.weight;
              break;
            }
          }
          if (v->D + W_u_v < u->D) {
            u->D = v->D + W_u_v;
          }
          R.erase(it_u); // erase and insert node u to get the correct order in next loop
          R.insert(u);
        }
      }
    }
  }

  if (graph.NodeAll_vec[destination_node_code]->D == INT_MAX) {
    cout << "No path exists!" << endl;
  } else {
    cout << "Shortest path length is " << graph.NodeAll_vec[destination_node_code]->D << endl;
  }
}

void MST(Graph graph) {
  multiset<Node *, comp_D> T; // construct a set T to store the used node
  multiset<Node *, comp_D> T_; // construct a set T_ to store the unused node
  std::sort(graph.NodeAll_vec.begin(),
            graph.NodeAll_vec.end(),
            comp_node_code); // make NodeAll.vec ordered by node_code
  auto size = graph.NodeAll_vec.size();
  for (int i = 0; i < size; ++i) {
    graph.NodeAll_vec[i]->D = INT_MAX;
  }
  graph.NodeAll_vec[0]->D = 0;
  T.clear();
  for (int i = 0; i < size; ++i) {
    T_.insert(graph.NodeAll_vec[i]);
  }
  int len = 0;
  int flag = 0;
  while (!T_.empty()) {
    auto v = *T_.begin();
    if (v->D == INT_MAX) {
      flag = 1;
      break;
    }
    len += v->D;
    T.insert(v);
    T_.erase(T_.begin());
    for (auto v_neighbor_it = v->undirected_list.begin(); v_neighbor_it != v->undirected_list.end();
         ++v_neighbor_it) {
      auto u = v_neighbor_it->end_node; // u is v's neighbor
      for (auto it_T_ = T_.begin(); it_T_ != T_.end(); ++it_T_) {
        if ((*it_T_) == u) {
          auto it_u = it_T_;
          int W_u_v = 0;
          for (auto it = graph.Undirected_EdgeAll_map.begin(); it != graph.Undirected_EdgeAll_map.end();) {
            if (it->second.end_node == u && it->first == v) { // edge from v to u
              W_u_v = it->second.weight;
              it = graph.Undirected_EdgeAll_map.erase(it);
              break;
            } else {
              it++;
            }
          }
          if (u->D > W_u_v) { // update u's D
            u->D = W_u_v;
          }
          for (auto it = graph.Undirected_EdgeAll_map.begin(); it != graph.Undirected_EdgeAll_map.end();) {
            if (it->first == u && it->second.end_node == v) { // edge from u to v
              it = graph.Undirected_EdgeAll_map.erase(it);
              break;
            } else {
              it++;
            }
          }
          for (auto it = u->undirected_list.begin(); it != u->undirected_list.end();) {
            if (it->end_node == v) { // remove v from u's neighbor
              it = u->undirected_list.erase(it);
              break;
            } else {
              it++;
            }
          }
          T_.erase(it_u); // erase and insert node u to get the correct order in next loop
          T_.insert(u);
          break;
        }
      }
    }
  }
  if (!flag) {
    cout << "The total weight of MST is " << len << endl;
  } else {
    cout << "No MST exists!" << endl;
  }
}