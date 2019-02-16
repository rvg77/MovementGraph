#pragma once

#include "kernelgraph.h"


class MovementGraph : public AL::ALModule {
 public:
  MovementGraph(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);
  ~MovementGraph();

  virtual void init();

  void Move(float x, float y, float theta);

  void SetTheta(float theta, float len);

  void StopMove();

  void RightKick();

  void LeftKick();

  float GetHeadVerticalAngle();

  float GetHeadHorizontalAngle();

  void SetHeadVerticalAngle(float angle);

  void SetHeadHorizontalAngle(float angle);

  void LookDown(int level);

  void ToInit();
  
  void GetUpFront();

  void GetUpBack();
 private:
  KernelGraph graph_;
};