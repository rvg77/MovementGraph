#pragma once
#include "movementgraph.h"
//#include "log.h"

using namespace AL;


MovementGraph::MovementGraph(boost::shared_ptr<ALBroker> broker, const std::string& name):
    life_proxy(getParentBroker()),
    ALModule(broker, name),
    graph(getParentBroker()) {

  setModuleDescription("Module for robot movements.");
}

MovementGraph::~MovementGraph() {}

void MovementGraph::init() {
}