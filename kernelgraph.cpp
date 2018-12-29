#include "kernelgraph.h"

KernelGraph::KernelGraph(boost::shared_ptr<AL::ALBroker> broker) :
    broker_(broker),
    motion_(broker),
    life_proxy(broker),
    posture_(broker) {}

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

  std::cout << "DEBUG" << std::endl;
  Run(full_way[0]->GetBegin());
  std::cout << "DEBUG" << std::endl;
  RunWay(full_way);
  return true;
}

bool KernelGraph::Run(const std::string& v_name, float time) {
  if (!IsVertexContains(v_name)) {
    return false;
  }

  Run(GetVertex(v_name), time);
  return true;
}

void KernelGraph::Run(const Vertex* v, float time) {
  assert(v != nullptr);
  assert(time > 0);

  motion_.angleInterpolation(PARAM_NAMES, v->GetRadianValues(), time, true);
}

void KernelGraph::Rest() const {
  motion_.rest();
}

void KernelGraph::Wake() const {
  motion_.wakeUp();
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

void KernelGraph::BehaviorOff() const {
  life_proxy.setState("disabled");
}

void KernelGraph::Move(float x, float y, float theta) {
  motion_.wakeUp();


  float first_rotate = atan2(y, x) - PI / 2;
  float len = sqrt(x * x + y * y);
  float second_rotate = theta - first_rotate;

  if (len > EPS) {
    Rotate(first_rotate);
    GoForward(len);
    Rotate(second_rotate);
  } else {
    Rotate(theta);
  }
  posture_.goToPosture("StandInit", 0.5);
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

void KernelGraph::Rotate(float theta) {
  assert(fabs(theta) <= PI);

  posture_.goToPosture("StandInit", 0.5);

  theta = GetRealAngle(theta);
  float x_speed, y_speed, t_speed, time_rotate;
  time_rotate = fabs(theta / theta_velocity);
  x_speed     = 0;
  y_speed     = 0;
  t_speed     = theta / time_rotate;

  MoveParams params;
  params.SetParam("MaxStepFrequency", 1.0);
  params.SetParam("MaxStepX", 0.02);
  params.SetParam("MaxStepY", 0.10);
  params.SetParam("StepHeight", 0.02);

  motion_.move(x_speed, y_speed, t_speed, params.GetParams());
  sleep(time_rotate);
  motion_.stopMove();
}

void KernelGraph::GoForward(float len) {
  assert(len >= 0);

  posture_.goToPosture("StandInit", 0.5);

  float x_speed, y_speed, t_speed, time_walk;
  time_walk = len / x_velocity;
  x_speed   = x_velocity;
  y_speed   = 0;
  t_speed   = 0;

  MoveParams params;

  params.SetParam("MaxStepX", 0.06);
  params.SetParam("StepHeight", 0.027);
  params.SetParam("TorsoWy", 0.01);
  /*
  params.SetParam("MaxStepFrequency", 0.0);

  params.SetParam("TorsoWy", 0.12);


  */

  motion_.setMoveArmsEnabled(true, true);
  motion_.move(x_speed, y_speed, t_speed, params.GetParams());
  sleep(time_walk);
  motion_.stopMove();
  motion_.setMoveArmsEnabled(false, false);
}

float KernelGraph::GetRealAngle(float theta) const {
  float sign = (theta < 0) ? -1 : 1;
  float new_theta = (fabs(theta) + 30 * TO_RAD) * 9 / 10;
  return sign * new_theta;
}

