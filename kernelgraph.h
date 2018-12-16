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

  bool RunName(const std::string& v_name, float time = 1.3);

  void RunPosition(const Vertex* v, float time = 1.3);

  void StrongRest() const;

  void StrongWake() const;

 private:
  void RunWay(std::vector <const Edge*> edges);

 private:
  boost::shared_ptr<AL::ALBroker> broker_;
  mutable AL::ALMotionProxy motion_;
  mutable AL::ALAutonomousLifeProxy life_proxy;
};