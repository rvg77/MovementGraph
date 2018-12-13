#pragma once

#include <alproxies/alautonomouslifeproxy.h>
#include "graph.h"


namespace AL
{
  class ALBroker;
}


class MovementGraph : public AL::ALModule {
 public:
  MovementGraph(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);
  ~MovementGraph();

  virtual void init();

 private:
    AL::ALAutonomousLifeProxy life_proxy;
    Graph graph;
};
