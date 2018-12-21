#include <boost/shared_ptr.hpp>
#include <qi/log.hpp>
#include <queue>
#include <fstream>
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/albasicawarenessproxy.h>
#include <alproxies/alautonomouslifeproxy.h>
#include "primalgraph.h"

namespace AL
{
  class ALBroker;
}

class KernelGraph : public PrimalGraph {
 public:
  KernelGraph(boost::shared_ptr<AL::ALBroker> broker_);

  Vertex GetCurrentState() const;

  bool RunChain(const std::vector <std::string>& chain, int cnt);

  bool Run(const std::string& v_name, float time = DEFAULT_TIME);

  void Run(const Vertex* v, float time = DEFAULT_TIME);

  void StrongRest() const;

  void StrongWake() const;

  void BehaviorOff() const;
 private:
  void RunWay(std::vector <const Edge*> edges);

 private:
  boost::shared_ptr<AL::ALBroker> broker_;
  mutable AL::ALMotionProxy motion_;
  mutable AL::ALAutonomousLifeProxy life_proxy;
};