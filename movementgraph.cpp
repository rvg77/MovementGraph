#pragma once
#include "movementgraph.h"
#include <alcommon/albroker.h>
#include <qi/log.hpp>
#include <alproxies/albasicawarenessproxy.h>
#include <alproxies/almotionproxy.h>
#include <queue>
#include <fstream>
//#include "log.h"

using namespace AL;


MovementGraph::MovementGraph(boost::shared_ptr<ALBroker> broker, const std::string& name):
    ALModule(broker, name), life_proxy(getParentBroker()) {

  setModuleDescription("Module for robot movements.");

  #include "automaticInitGeneration.h"
      
  adjacency_list_.clear();
  vertex_to_index_.clear();
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    const Vertex * ind = &vertexes_[i];
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

MovementGraph::~MovementGraph() {}

void MovementGraph::init() {
  life_proxy.setState("disabled");
  while (true) {
    std::string command;
    std::cout << "> ENTER command\n> ";
    std::cin >> command;
    if (command == "RECORD") {
      RecordMovement("test/vertex.txt");
    } else if (command == "REST") {
      StrongRest();
    } else if (command == "WAKE") {
      StrongWake();
    } else if (command == "SET") {
      std::string v_name = "";
      std::cout << "\t>  ENTER Vertex Name:\n";
      std::cin >> v_name;
      if (fromStringNameToNumber_.find(v_name) == fromStringNameToNumber_.end()) {
        std::cout << "wrong vertex name)))\n";
        continue;
      } else {
        RunPosition(&vertexes_[fromStringNameToNumber_[v_name]]);
      }
    } else if (command == "SET_NUMBER") {
      int v_num = 0;
      std::cout << "\t>  ENTER Vertex Number:\n";
      std::cin >> v_num;
      if (v_num >= vertexes_.size()) {
        std::cout << "wrong vertex number)))\n";
        continue;
      } else {
        RunPosition(&vertexes_[v_num]);
      }
    } else if (command == "TEST_NUMBER") {
      std::vector <const Edge*> vec;
      
      int count, s, f;

      std::cout << "PLEASE give my INDEX VERTEX (START and FINAL)\n";
      std::cin >> s >> f;

      std::cout << "PLEASE give my COUNT STEPS\n";
      std::cin >> count;
      FindWayToVertexFromVertex(&vertexes_[s], &vertexes_[f], vec);
        
      for (int i = 0; i < count; ++i) {
        RunWay(vec);
      }
    }
    else if (command == "TEST") {
      std::vector <const Edge*> vec;
      
      int count;
      std::string s, f;

      std::cout << "PLEASE give my NAME VERTEX (START and FINAL)\n";
      std::cin >> s >> f;

      std::cout << "PLEASE give my COUNT STEPS\n";
      std::cin >> count;
      FindWayToVertexFromVertex(&vertexes_[fromStringNameToNumber_[s]], &vertexes_[fromStringNameToNumber_[f]], vec);

      for (int i = 0; i < count; ++i) {
        RunWay(vec);
      }
    }
    else if (command == "TT") {
      std::vector <const Edge*> vec;
      
      int count;
      std::string s, f;

      std::cout << "PLEASE give my COUNT STEPS\n";
      std::cin >> count;

      std::vector <const Edge*> way;

      //std::vector <std::pair<std::string, int>> tr({{"A", 0}, {"ALL", 0}, {"ALL", 0}, {"A", 1}, {"ARR", 0}, {"ARR", 0}});
      //std::vector <std::pair<std::string, int>> tr({{"A", 2}, {"B1", 0}, {"B2", 0}});
      std::vector <std::pair<std::string, int>> tr({{"A", 0}, {"ML", 0}, {"ST1", 0}, {"MR", 0}, {"ST2", 0}, {"ML", 0}, {"A", 1}});
      
      for (int i = 0; i < tr.size(); ++i) {
        vec.push_back(vertexes_[fromStringNameToNumber_[tr[i].first]].GetEdge(tr[i].second));
      }

      for (int i = 0; i < count; ++i) {
        for (int j = 0; j < vec.size(); ++j) {
          way.push_back(vec[j]);
        }
      }
      way.push_back(vec[0]);
      RunWay(way);
    }
  }
}

void MovementGraph::RecordMovement(const std::string &output_file) {
  std::ofstream out(output_file, std::ios_base::app);

  while (true) {
    std::cout << "\t> PRINT current robot state.\n\t> ENTER Vertex name or\n\t> EXIT to finish recording: \n\t> ";
    std::string vertex_name;
    std::cin >> vertex_name;

    if (vertex_name == "EXIT") {
      break;
    }
    out << vertex_name << ' ';
    Vertex curr(GetCurrentState());
    curr.PrintState(out);
  }
}


bool MovementGraph::FindWayToVertexFromVertex(const Vertex* start, const Vertex* finish,
                                              std::vector <const Edge*> &way) const {
  assert(way.empty());
  assert(adjacency_list_.size() == vertexes_.size());
  int begin = vertex_to_index_[start];
  int end   = vertex_to_index_[finish];
  std::vector <int> wayInt;

  if (!FindWayToVertexFromVertexViaBFS(begin, end, wayInt)) {
    return false;
  }

  const Vertex* ind = start;
  for (size_t i = 0; i < wayInt.size(); ++i) {
    way.push_back(ind->GetEdge(wayInt[i]));
    ind = ind->GetEdge(wayInt[i])->GetEnd();
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


int MovementGraph::GetNearestVertex() {
  Vertex dummy(GetCurrentState());

  int min_index = 0;
  float min = dummy.Dist(vertexes_[0]);

  for (int i = 1; i < vertexes_.size(); i++) {
    float metrics = dummy.Dist(vertexes_[i]);
    if (metrics < min) {
      min = metrics;
      min_index = i;
    }
  }

  return min_index;
}


void MovementGraph::RunWay(std::vector<const Edge*> edges, bool only_start) {
  if (edges.empty()) {
      return;
  }
  AL::ALValue angleLists;
  AL::ALValue timeLists;
  std::vector <std::vector <float> > params_list;
  std::vector <float> time_list;

  time_list.push_back(1);
  params_list.push_back(edges[0]->GetBegin()->GetRadianValues());

  for (int i = 0; !only_start && i < edges.size(); ++i) {
    time_list.push_back(time_list[i] + edges[i]->GetTime());
    params_list.push_back(edges[i]->GetEnd()->GetRadianValues());
  }

  for (int i = 0; i < 25; ++i) {
    std::vector <float> joint_path;
    for (int j = 0; j < params_list.size(); ++j) {
      joint_path.push_back(params_list[j][i]);
    }
    timeLists.arrayPush(time_list);
    angleLists.arrayPush(joint_path);
  }

  ALMotionProxy motion(getParentBroker());
  motion.angleInterpolationBezier(PARAM_NAMES, timeLists, angleLists);
}


Vertex MovementGraph::GetCurrentState() const {
  ALMotionProxy motion(getParentBroker());
  ALValue names = PARAM_NAMES;
  bool useSensors = true;

  std::vector <float> result = motion.getAngles(names, useSensors);
  return Vertex(result, true);
}

void MovementGraph::StrongRest() const {
  ALMotionProxy motion(getParentBroker());
  ALValue names = PARAM_NAMES;

  std::vector <float> param;
  for (int i = 0; i < PARAM_NUM_; ++i) {
    param.push_back(0);
  }
  motion.setStiffnesses(names, param);
}

void MovementGraph::StrongWake() const {
  ALMotionProxy motion(getParentBroker());
  ALValue names = PARAM_NAMES;

  std::vector <float> param;
  for (int i = 0; i < PARAM_NUM_; ++i) {
    param.push_back(1);
  }
  motion.setStiffnesses(names, param);
}

void MovementGraph::RunPosition(const Vertex* v) {
  Edge e(v, v, 2);
  std::vector <const Edge*> vec;
  vec.push_back(&e);
  RunWay(vec, 1);
}
