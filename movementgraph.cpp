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
}

MovementGraph::~MovementGraph() {}

void MovementGraph::init() {}

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