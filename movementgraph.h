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

  float GetHeadVerticalAngle();

  float GetHeadHorizontalAngle();

  void SetHeadVerticalAngle(float angle);

  void SetHeadHorizontalAngle(float angle);
 private:
  // KernelGraph graph_;
};