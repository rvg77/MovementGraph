#pragma once

#include "kernelgraph.h"


class MovementGraph : public AL::ALModule {
 public:
  MovementGraph(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);
  ~MovementGraph();

  virtual void init();

  void Move(float x, float y, float theta);

  void RightKick();

  void LeftKick();

 private:
  KernelGraph graph_;
};