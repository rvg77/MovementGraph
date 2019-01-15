#include <boost/shared_ptr.hpp>
#include <qi/log.hpp>
#include <queue>
#include <fstream>
#include <alcommon/albroker.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/albasicawarenessproxy.h>
#ifdef MOVEMENTGRAPH_IS_REMOTE
# include <alproxies/alautonomouslifeproxy.h>
#endif
#include <alproxies/alrobotpostureproxy.h>
#include "primalgraph.h"

namespace AL
{
  class ALBroker;
}

class KernelGraph : public PrimalGraph {
 public:
  KernelGraph(boost::shared_ptr<AL::ALBroker> broker_);

  Vertex GetCurrentState() const;

  bool RunChain(const std::vector <std::string>& chain,
                int cnt,
                float acceleration = DEFAULT_ACCELERATION);

  bool Run(const std::string& v_name, float time = DEFAULT_TIME);

  void Run(const Vertex* v, float time = DEFAULT_TIME);

  void Rest() const;

  void Wake() const;

  void StrongRest() const;

  void StrongWake() const;

  void BehaviorOff() const;

  void Move(float x, float y, float theta);

  void RightKick();

  void LeftKick();

<<<<<<< HEAD
  // void Fun();
=======
  void GetUpFront();

  void Fun();

  float GetHeadVerticalAngle();

  float GetHeadHorizontalAngle();

  void SetHeadVerticalAngle(float angle);

  void SetHeadHorizontalAngle(float angle);
>>>>>>> 428d483890e0ebac8279d2c6ce54331b1739906e

 private:
  void RunWay(std::vector <const Edge*> edges, float acceleration);

  void Rotate(float theta);

  void GoForward(float len);

  float GetRealAngle(float theta) const;

 private:
  mutable AL::ALMotionProxy motion_;
<<<<<<< HEAD
  // mutable AL::ALAutonomousLifeProxy life_proxy;
=======
#ifdef MOVEMENTGRAPH_IS_REMOTE
  mutable AL::ALAutonomousLifeProxy life_proxy_;
#endif
>>>>>>> 428d483890e0ebac8279d2c6ce54331b1739906e
  mutable AL::ALRobotPostureProxy posture_;
};