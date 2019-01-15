#pragma once

#include "kernelgraph.h"


class MovementGraph : public AL::ALModule, public KernelGraph {
 public:
  MovementGraph(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);
  virtual ~MovementGraph();

  virtual void init();

  void MoveTo(float x, float y, float theta);

  void KickRight();

  void KickLeft();

 private:
  // KernelGraph graph_;
};