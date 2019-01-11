#ifndef _WIN32
# include <signal.h>
#endif

#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>

#if MOVEMENTGRAPH_IS_REMOTE
# include "graphcreator.h"
# define ALCALL
#else
# include "movementgraph.h"
# ifdef _WIN32
#  define ALCALL __declspec(dllexport)
# else
#  define ALCALL
# endif
#endif


extern "C"
{
  ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> pBroker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(pBroker);
    // create module instances
#if MOVEMENTGRAPH_IS_REMOTE
    AL::ALModule::createModule<GraphCreator>(pBroker, "GraphCreator");
#else
    AL::ALModule::createModule<MovementGraph>(pBroker, "MovementGraph");
#endif
    return 0;
  }

  ALCALL int _closeModule(  )
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
