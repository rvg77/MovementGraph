
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>


#ifdef MOVEMENTGRAPH_IS_REMOTE
# include "graphcreator.h"
#else
# include "movementgraph.h"
#endif

extern "C"
{
  int _createModule(boost::shared_ptr<AL::ALBroker> broker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker);
    // create module instances
#ifdef MOVEMENTGRAPH_IS_REMOTE
    AL::ALModule::createModule<GraphCreator>(broker, "GraphCreator");
#else
    AL::ALModule::createModule<MovementGraph>(broker, "MovementGraph");
#endif
    return 0;
  }

  int _closeModule(  )
  {
    return 0;
  }
} // extern "C"

#ifdef MOVEMENTGRAPH_IS_REMOTE
  int main(int argc, char *argv[])
  {
    // pointer to createModule
    TMainType sig;
    sig = &_createModule;
    // call main
    return ALTools::mainFunction("GraphCreator", argc, argv, sig);
  }
#endif