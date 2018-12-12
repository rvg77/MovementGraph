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
    ALModule(broker, name),
    vertex_buffer_(true),
    edge_buffer_(true) {

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
  while (true) {
    std::string command;
    std::cout << "> ENTER command\n> ";
    std::cin >> command;

    if (command == "ACT_OFF") {
      AL::ALAutonomousLifeProxy life_proxy(getParentBroker());
      life_proxy.setState("disabled");
    }
    else if (command == "ACT_ON") {

    }
    else if (command == "REST") {
      StrongRest();
    }
    else if (command == "WAKE") {
      StrongWake();
    }
    else if (command == "ON_BUFF") {
      SnapBuffer();
    }
    else if (command == "CALL_BUFF") {
      std::string name;
      std::cout << "\t> ENTER name for buffer vertex:\n\t- ";
      std::cin >> name;

      SetNameBuffer(name);
    }
    else if (command == "RUN_BUFF") {
      RunFromBuffer();
    }
    else if (command == "REFL_BUFF") {
      ReflectBuffer();
    }
    else if (command == "LIKE_LEFT_BUFF") {
      RightLikeLeftBuffer();
    }
    else if (command == "LIKE_RIGHT_BUFF") {
      LeftLikeRightBuffer();
    }
    else if (command == "SAVE") {
      RecordFromBuffer("test/vertex.txt");
    }
    else if (command == "SET") {
      std::string v_name;

      std::cout << "\t>  ENTER Vertex Name:\n";
      std::cin >> v_name;
      if (vertexes_by_name_.find(v_name) == vertexes_by_name_.end()) {
        std::cout << "\t> Wrong vertex name)))\n";
        continue;
      } else {
        RunPosition(&vertexes_[vertexes_by_name_[v_name]], 0.1);
      }
    }
    else if (command == "TEST") {
      int n, cnt;
      std::vector <const Edge*> way;
      std::vector <std::string> path;

      std::cout << "> Please enter Len of chain:\n\t- ";
      std::cin >> n;

      std::cout << "> ENTER vertexes names:\n\t- ";
      for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        path.push_back(s);
      }
      std::cout << "> ENTER repeat number:\n\t- ";
      std::cin >> cnt;

      RunChain(path, cnt);
    }
    else if (command == "TT") {
      int cnt;
      std::vector <std::string> path({"START", "LUP", "START", "RUP", "START"});

      std::cout << "> ENTER repeat number:\n\t- ";
      std::cin >> cnt;

      RunChain(path, cnt);
    }
  }
}

void MovementGraph::SnapBuffer() {
  Vertex curr(GetCurrentState());
  vertex_buffer_ = curr;
}

void MovementGraph::SetNameBuffer(std::string name) {
  vertex_buffer_.SetName(name);
}

void MovementGraph::LeftLikeRightBuffer() {
  vertex_buffer_.CopyFromSide(RIGHT);
}

void MovementGraph::RightLikeLeftBuffer() {
  vertex_buffer_.CopyFromSide(LEFT);
}

void MovementGraph::ReflectBuffer() {
  vertex_buffer_.Reflect();
}

void MovementGraph::RecordFromBuffer(const std::string &output_file) {
  std::ofstream out(output_file, std::ios_base::app);

  vertex_buffer_.PrintState(out);

}

void MovementGraph::RunFromBuffer() {
  RunPosition(&vertex_buffer_, 0.2);
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

void MovementGraph::RunChain(const std::vector <std::string>& chain, int cnt) {
  int n = chain.size();
  std::vector <const Edge*> way, full_way;

  for (int i = 1; i < n; ++i) {
    std::vector <const Edge*> vec;
    Vertex* s = &vertexes_[vertexes_by_name_[chain[i - 1]]];
    Vertex* f = &vertexes_[vertexes_by_name_[chain[i]]];

    FindWayToVertexFromVertex(s, f, vec);
    for (int j = 0; j < vec.size(); ++j) {
      way.push_back(vec[j]);
    }
  }

  for (int i = 0; i < cnt; ++i) {
    for (int j = 0; j < n; ++j) {
      full_way.push_back(way[j]);
    }
  }

  RunPosition(full_way[0]->GetBegin());
  RunWay(full_way);
}

void MovementGraph::RunWay(std::vector<const Edge*> edges) {
  if (edges.empty()) {
      return;
  }
  std::cout << "!!! " << edges.size() << std::endl;
  AL::ALValue angleLists;
  AL::ALValue timeLists;
  std::vector <std::vector <float> > params_list;
  std::vector <float> time_list;
  float curr_time = 0;

  for (int i = 0; i < edges.size(); ++i) {
    curr_time += edges[i]->GetTime();
    time_list.push_back(curr_time);
    params_list.push_back(edges[i]->GetEnd()->GetRadianValues());
  }


  for (int i = 0; i < PARAM_NUM_; ++i) {
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

void MovementGraph::RunPosition(const Vertex* v, float time) {
  ALMotionProxy motion(getParentBroker());
  motion.angleInterpolation(PARAM_NAMES, v->GetRadianValues(), time, true);
}
