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