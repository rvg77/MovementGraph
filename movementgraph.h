#pragma once

#include "kernelgraph.h"


class MovementGraph : public AL::ALModule {
 public:
  MovementGraph(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);
  ~MovementGraph();

  virtual void init();

 private:
  KernelGraph graph_;
};