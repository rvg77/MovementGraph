#include "movementgraph.h"
#include <iostream>
#include <alcommon/albroker.h>
#include <qi/log.hpp>
#include <alproxies/almotionproxy.h>
#include <assert.h>

using namespace AL;

const size_t MovementGraph::Vertex::PARAM_NUM_ = 25;

const std::vector <std::string> MovementGraph::Vertex::param_names_ = {
    "HeadPitch",
    "LShoulderPitch",
    "LShoulderRoll",
    "LElbowYaw",
    "LElbowRoll",
    "LWristYaw",
    "LHipYawPitch",
    "LHipRoll",
    "LHipPitch",
    "LKneePitch",
    "LAnklePitch",
    "LAnkleRoll",
    "RHipYawPitch",
    "RHipRoll",
    "RHipPitch",
    "RKneePitch",
    "RAnklePitch",
    "RAnkleRoll",
    "RShoulderPitch",
    "RShoulderRoll",
    "RElbowYaw",
    "RElbowRoll",
    "RWristYaw",
    "LHand",
    "RHand" };



MovementGraph::Vertex::Vertex(std::vector <float> new_param_values_)
    : param_values_(new_param_values_) {}

MovementGraph::Vertex::Vertex(const Vertex & vertex)
    : param_values_(vertex.param_values_),
      adjacent_edges_(vertex.adjacent_edges_) {}

void MovementGraph::Vertex::GetCurrentState(boost::shared_ptr<ALBroker> broker_ ) {
  ALMotionProxy motion(broker_);
  ALValue names = param_names_;
  bool useSensors = true;

  std::vector <float> result = motion.getAngles(names, useSensors);
  param_values_ = result;
  return;
}

void MovementGraph::Vertex::Run(float velocity_, boost::shared_ptr<ALBroker> broker_) {
  ALMotionProxy motion(broker_);
  ALValue names = param_names_;
  float maxSpeedFraction = velocity_;

  motion.angleInterpolationWithSpeed(names, param_values_, maxSpeedFraction);
  return;
}

void MovementGraph::Vertex::AddEdge(const Edge* new_edge) {
  adjacent_edges_.push_back(new_edge);
}
