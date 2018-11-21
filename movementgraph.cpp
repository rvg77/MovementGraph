#include "movementgraph.h"
#include <iostream>
#include <alcommon/albroker.h>
#include <qi/log.hpp>
#include <alproxies/almotionproxy.h>
#include <assert.h>
#include <queue>

using namespace AL;

MovementGraph::MovementGraph(boost::shared_ptr<ALBroker> broker, const std::string& name):
    ALModule(broker, name) {

  setModuleDescription("Module for robot movements.");

  #include "automaticInitGeneration.h"
      
  adjacency_list_.clear();
  vertex_to_index_.clear();
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    const Vertex * dd = &vertexes_[i];
    vertex_to_index_[dd] = i;
    adjacency_list_.push_back(std::vector<int>());
  }

  for (size_t i = 0; i < edges_.size(); ++i) {
    int u = vertex_to_index_[edges_[i].GetBegin()];
    int v = vertex_to_index_[edges_[i].GetEnd()];
    adjacency_list_[u].push_back(v);
  }
}

MovementGraph::~MovementGraph() {}

void MovementGraph::init() {
  RecordMovement("test/vertex.txt");
}

void MovementGraph::RecordMovement(const std::string &output_file) {
  {
    ALMotionProxy motion(getParentBroker());
    motion.rest();
  }
  std::vector <float> params = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  Vertex curr(params);
  std::ofstream out("test/vertex.txt");

  while (true) {
    std::cout << "> PRINT current robot state. > \nENTER Vertex name or\n > EXIT to finish recording: \n> ";
    std::string vertex_name;
    std::cin >> vertex_name;


    out << vertex_name << ' ';
    curr.GetCurrentState(getParentBroker());
    curr.PrintState(out);
  }
}


bool MovementGraph::FindWayToVertexFromVertex(const Vertex* start, const Vertex* finish,
                                              std::vector <const Edge*> way) const { 
  assert(way.empty());
  assert(adjacency_list_.size() == vertexes_.size());
  int begin = vertex_to_index_[start];
  int end   = vertex_to_index_[finish];
  std::vector <int> wayInt;

  if (!FindWayToVertexFromVertexViaBFS(begin, end, wayInt)) {
    return false;
  }

  for (size_t i = 0; i < wayInt.size(); ++i) {
    way.push_back(&edges_[wayInt[i]]);
  }

  return true;
}

bool MovementGraph::FindWayToVertexFromVertexViaBFS(int start,
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



//vertex_count >= 1
int MovementGraph::GetNearestVertex(boost::shared_ptr<ALBroker> broker_) {
  Vertex dummy = vertexes_[0];
  dummy.GetCurrentState(broker_);

  int min_index = 0;
  float min = dummy.GetMetrics(vertexes_[0]);

  for (int i = 1; i < vertexes_.size(); i++) {
    float metrics = dummy.GetMetrics(vertexes_[i]);
	if (metrics < min) {
	  min = metrics;
	  min_index = i;
	}
  }
  return min_index;
}

void MovementGraph::RunWay(std::vector<Edge*> edges) {
    if (edges.empty()) {
        return;
    }
    edges[0]->GetBegin()->Run(0.0,getParentBroker());

    for (int i = 0; i < edges.size(); i++) {
        edges[i]->GetEnd()->Run(0.0, getParentBroker());
    }
}
