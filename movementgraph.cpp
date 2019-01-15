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

  functionName("KickLeft", getName(), "kick by left foot");
  BIND_METHOD(MovementGraph::KickLeft);
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

void MovementGraph::KickLeft() {
  LeftKick();
}