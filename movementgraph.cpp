#pragma once
#include "movementgraph.h"
//#include "log.h"



MovementGraph::MovementGraph(boost::shared_ptr<AL::ALBroker> broker, const std::string& name):
    AL::ALModule(broker, name),
    KernelGraph(broker) {

  setModuleDescription("Module for robot movements.");

  functionName("MoveTo", getName(), "move robot in other position");
  addParam("x", "displacement to the right in meters. Negative value to the left.");
  addParam("y", "displacement to front in meters. Negative value to back.");
  addParam("theta", "Its a rotate angle from start position");
  BIND_METHOD(MovementGraph::MoveTo);

  functionName("KickRight", getName(), "kick by right foot");
  BIND_METHOD(MovementGraph::KickRight);

  functionName("LeftKick", getName(), "kick by left foot");
  BIND_METHOD(MovementGraph::LeftKick);

  functionName("GetHeadVerticalAngle", getName(), "Current Head angle from left to right relative to body direction");
  setReturn("angle", "angle in degree");
  BIND_METHOD(MovementGraph::GetHeadVerticalAngle);

  functionName("GetHeadHorizontalAngle", getName(), "Current Head angle from down to up relative to horizon");
  setReturn("angle", "angle in degree");
  BIND_METHOD(MovementGraph::GetHeadHorizontalAngle);

  functionName("SetHeadVerticalAngle", getName(), "Set head angle due vertical axis");
  addParam("angle", "angle in degree");
  BIND_METHOD(MovementGraph::SetHeadVerticalAngle);

  functionName("SetHeadHorizontalAngle", getName(), "Set head angle due horizontal axis");
  addParam("angle", "angle in degree");
  BIND_METHOD(MovementGraph::SetHeadHorizontalAngle);
}

MovementGraph::~MovementGraph() {}

void MovementGraph::init() {
}

void MovementGraph::MoveTo(float x, float y, float theta) {
  Move(x, y, theta);
}

void MovementGraph::KickRight() {
  RightKick();
}

void MovementGraph::LeftKick() {
  graph_.LeftKick();
}

float MovementGraph::GetHeadVerticalAngle() {
  graph_.GetHeadVerticalAngle();
}

float MovementGraph::GetHeadHorizontalAngle() {
  graph_.GetHeadHorizontalAngle();
}

void MovementGraph::SetHeadVerticalAngle(float angle) {
  graph_.SetHeadVerticalAngle(angle);
}

void MovementGraph::SetHeadHorizontalAngle(float angle) {
  graph_.SetHeadHorizontalAngle(angle);
}