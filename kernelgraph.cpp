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

  std::vector <float> result = motion.getAngles(alvalue_names, useSensors);
  return Vertex(result, true);
}

bool KernelGraph::RunChain(const std::vector <std::string>& chain, int cnt) {
  assert(cnt > 0);
  assert(chain.size() > 1)

  std::vector <const Edge*> way, full_way;
  if (!FindWayThroughVertexes(chain, way)) {
    return false;
  }

  for (int i = 0; i < cnt; ++i) {
    for (int j = 0; j < way.size(); ++j) {
      full_way.push_back(way[j]);
    }
  }

  RunPosition(full_way[0]->GetBegin());
  RunWay(full_way);
}

bool KernelGraph::Run(const std::string& v_name, float time = 0.3) {
  if (!IsVertexContains(v_name)) {
    return false;
  }

  RunWay(GetVertex(v_name), time);
}

void KernelGraph::StrongRest() const {
  std::vector <float> param;
  for (int i = 0; i < PARAM_NUM_; ++i) {
    param.push_back(0);
  }
  motion.setStiffnesses(alvalue_names, param);
}

void KernelGraph::StrongWake() const {
  std::vector <float> param;
  for (int i = 0; i < PARAM_NUM_; ++i) {
    param.push_back(1);
  }
  motion.setStiffnesses(alvalue_names, param);
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

  motion.angleInterpolationBezier(PARAM_NAMES, timeLists, angleLists);
}

void KernelGraph::RunPosition(const Vertex* v, float time = 0.3) {
  motion.angleInterpolation(PARAM_NAMES, v->GetRadianValues(), time, true);
}