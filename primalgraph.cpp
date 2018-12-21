#include "primalgraph.h"

PrimalGraph::PrimalGraph() {}

void PrimalGraph::Initialize() {
  #include "automaticInitGeneration.h"

  adjacency_list_.clear();
  vertex_to_index_.clear();

  for (size_t i = 0; i < vertexes_.size(); ++i) {
    const Vertex* ind = &vertexes_[i];
    vertex_to_index_[ind] = i;
    adjacency_list_.push_back(std::vector<int>());
  }

  for (size_t i = 0; i < edges_.size(); ++i) {
    int u = vertex_to_index_[edges_[i].GetBegin()];
    int v = vertex_to_index_[edges_[i].GetEnd()];
    adjacency_list_[u].push_back(v);

    vertexes_[u].AddEdge(&edges_[i]);
  }
}

void PrimalGraph::AddVertex(const Vertex& v) {
  assert(v.GetName() != "");
  assert(v.GetAdjacentCount() == 0);
  assert(!IsVertexContains(v.GetName()));

  int n = vertexes_.size();
  vertexes_.push_back(v);
  adjacency_list_.push_back(std::vector <int> ());

  Vertex* v_ptr = &vertexes_[n];
  vertexes_by_name_[v.GetName()] = n;
  vertex_to_index_[v_ptr] = n;
}

void PrimalGraph::AddEdge(const std::string& from, const std::string& to, float time) {
  Edge e(GetVertex(from), GetVertex(to), time);

  assert(IsEdgeContains(e));
  edges_.push_back(e);

  int n = edges_.size();
  int u = vertexes_by_name_[from];
  int v = vertexes_by_name_[to];
  Edge* e_ptr = &edges_[n];

  adjacency_list_[u].push_back(v);
  vertexes_[u].AddEdge(e_ptr);
}

const Vertex* PrimalGraph::GetVertex(const std::string& name) const {
  assert(IsVertexContains(name));
  int ind = vertexes_by_name_.at(name);
  assert(ind < vertexes_.size());

  return &vertexes_[ind];
}

const Vertex* PrimalGraph::GetNearestVertex(Vertex* v) const {
  assert(!vertexes_.empty());

  int min_index = 0;
  float min = v->Dist(vertexes_[0]);

  for (int i = 1; i < vertexes_.size(); i++) {
    float metrics = v->Dist(vertexes_[i]);
    if (metrics < min) {
      min = metrics;
      min_index = i;
    }
  }

  return &vertexes_[min_index];
}

bool PrimalGraph::FindWayToVertexFromVertex(const std::string& start,
                                            const std::string& finish,
                                            std::vector <const Edge*>& way) const {
  assert(way.empty());
  assert(adjacency_list_.size() == vertexes_.size());
  assert(IsVertexContains(start));
  assert(IsVertexContains(finish));

  int begin = vertexes_by_name_.at(start);
  int end   = vertexes_by_name_.at(finish);
  std::vector <int> wayInt;


  if (!FindWayToVertexFromVertexViaBFS(begin, end, wayInt)) {
    return false;
  }

  std::cout << "DEBUG: ";
  for (int i = 0; i < wayInt.size(); ++i) {
    std::cout << wayInt[i] << ' ';
  }
  std::cout << std::endl;
  const Vertex* ind = GetVertex(start);
  for (size_t i = 0; i < wayInt.size(); ++i) {
    way.push_back(ind->GetEdge(wayInt[i]));
    ind = ind->GetEdge(wayInt[i])->GetEnd();
  }

  return true;
}

bool PrimalGraph::FindWayThroughVertexes(const std::vector <std::string>& names,
                                         std::vector <const Edge*>& way) const {
  int n = names.size();

  for (int i = 1; i < n; ++i) {
    std::vector <const Edge*> vec;

    if (!FindWayToVertexFromVertex(names[i - 1], names[i], vec)) {
      return false;
    }

    for (int j = 0; j < vec.size(); ++j) {
      way.push_back(vec[j]);
    }
  }
  return true;
}

bool PrimalGraph::IsVertexContains(const std::string& name) const {
  return vertexes_by_name_.find(name) != vertexes_by_name_.end();
}


/*------- PRIVAT SPACE ---------*/


bool PrimalGraph::IsEdgeContains(const Edge& e) const {
  for (size_t i = 0; i < edges_.size(); ++i) {
    if (edges_[i] == e) {
      return true;
    }
  }
  return false;
}

bool PrimalGraph::FindWayToVertexFromVertexViaBFS(int start,
                                     int finish,
                                     std::vector <int> & way) const {
  assert(way.empty());
  assert(adjacency_list_.size() == vertexes_.size());

  size_t size = adjacency_list_.size();

  std::vector <bool> flags(size, 0);
  std::vector <int>  parent(size, -1);
  std::vector <int>  edgeToNext(size, -1);
  std::queue  <int>  bfs;

  if (finish == start) {
    return true;
  }

  bfs.push(start);

  flags[start]        =  1;
  parent[start]       = -1;
  edgeToNext[finish]  = -1;

  while (!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();

    if (u == finish) break;
    for (int i = 0; i < adjacency_list_[u].size(); ++i) {
      int v = adjacency_list_[u][i];
      if (flags[v] == 0) {
        flags[v] = 1;
        parent[v] = u;
        edgeToNext[v] = i; // this is not bag))) I want remember edge to next for u into v))) sorry
        bfs.push(v);
      }
    }
  }

  if (parent[finish] == -1) {
    return false;
  }

  int ind = finish;

  while (ind != start) {
    way.push_back(edgeToNext[ind]);
    ind = parent[ind];
  }

  std::reverse(way.begin(), way.end());

  assert(!way.empty());
  return true;
}
