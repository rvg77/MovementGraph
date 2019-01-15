#pragma once
#include "movementgraph.h"
//#include "log.h"

using namespace AL;


MovementGraph::MovementGraph(boost::shared_ptr<ALBroker> broker, const std::string& name):
    ALModule(broker, name),
    graph_(broker) {

  setModuleDescription("Module for robot movements.");

  functionName("Move", getName(), "move robot in other position");
  addParam("x", "displacement to the right in meters. Negative value to the left.");
  addParam("y", "displacement to front in meters. Negative value to back.");
  addParam("theta", "Its a rotate angle from start position");
  BIND_METHOD(MovementGraph::Move);

  functionName("RightKick", getName(), "kick by right foot");
  BIND_METHOD(MovementGraph::RightKick);

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

  functionName("ToInit", getName(), "go to init position");
  BIND_METHOD(MovementGraph::ToInit);

  functionName("LookDown", getName(), "position to looking for the ball");
  addParam("level", "degree tilt from 0 to 7");
  BIND_METHOD(MovementGraph::LookDown);

}

MovementGraph::~MovementGraph() {}

void MovementGraph::init() {
}


void MovementGraph::Move(float x, float y, float theta) {
  graph_.Move(x, y, theta);
}

void MovementGraph::RightKick() {
  graph_.RightKick();
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

void MovementGraph::ToInit() {
  graph_.ToInit();
}

void MovementGraph::LookDown(int level) {
  graph_.LookDown(level);
}