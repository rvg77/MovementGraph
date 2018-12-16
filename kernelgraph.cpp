#include "kernelgraph.h"

KernelGraph::KernelGraph(boost::shared_ptr<AL::ALBroker> broker) :
    broker_(broker),
    motion_(broker),
    life_proxy(broker) {
  Initialize();
  life_proxy.setState("disabled");
}

Vertex KernelGraph::GetCurrentState() const {
  bool useSensors = true;

  std::vector <float> result = motion_.getAngles(PARAM_NAMES, useSensors);
  return Vertex(result, true);
}

bool KernelGraph::RunChain(const std::vector <std::string>& chain, int cnt) {
  assert(cnt > 0);
  assert(chain.size() > 1);

  std::vector <const Edge*> way, full_way;
  if (!FindWayThroughVertexes(chain, way)) {
    return false;
  }

  for (int i = 0; i < cnt; ++i) {
    for (int j = 0; j < way.size(); ++j) {
      full_way.push_back(way[j]);
    }
  }

  Run(full_way[0]->GetBegin());
  RunWay(full_way);
}

bool KernelGraph::Run(const std::string& v_name, float time) {
  if (!IsVertexContains(v_name)) {
    return false;
  }

  Run(GetVertex(v_name), time);
}

void KernelGraph::Run(const Vertex* v, float time) {
  assert(v != nullptr);

  motion_.angleInterpolation(PARAM_NAMES, v->GetRadianValues(), time, true);
}

void KernelGraph::StrongRest() const {
  std::vector <float> param;
  for (int i = 0; i < PARAM_NUM_; ++i) {
    param.push_back(0);
  }
  motion_.setStiffnesses(PARAM_NAMES, param);
}

void KernelGraph::StrongWake() const {
  std::vector <float> param;
  for (int i = 0; i < PARAM_NUM_; ++i) {
    param.push_back(1);
  }
  motion_.setStiffnesses(PARAM_NAMES, param);
}


/*------- PRIVAT SPACE ---------*/


void KernelGraph::RunWay(std::vector <const Edge*> edges) {
  if (edges.empty()) {
    return;
  }

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

  motion_.angleInterpolationBezier(PARAM_NAMES, timeLists, angleLists);
}

