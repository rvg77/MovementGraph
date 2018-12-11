#pragma once
#include "movementgraph.h"
//#include "log.h"

using namespace AL;


MovementGraph::MovementGraph(boost::shared_ptr<ALBroker> broker, const std::string& name):
    life_proxy(getParentBroker()),
    ALModule(broker, name),
    graph(getParentBroker()) {

   setModuleDescription("Module for robot movements.");
}

MovementGraph::~MovementGraph() {}

void MovementGraph::init() {
    // инициализируем граф
    graph.initialize();
    // отключаем ненужные процессы
    life_proxy.setState("disabled");
    while (true) {
        std::string command;
        std::cout << "> ENTER command\n> ";
        std::cin >> command;

        if (command == "REST") {
            graph.StrongRest();
        }
        else if (command == "WAKE") {
            graph.StrongWake();
        }
        else if (command == "ON_BUFF") {
            graph.SnapBuffer();
        }
        else if (command == "CALL_BUFF") {
            graph.CallBuffer();
        }
        else if (command == "RUN_BUFF") {
            graph.RunFromBuffer();
        }
        else if (command == "REFL_BUFF") {
            graph.ReflectBuffer();
        }
        else if (command == "LIKE_LEFT_BUFF") {
            graph.RightLikeLeftBuffer();
        }
        else if (command == "LIKE_RIGHT_BUFF") {
            graph.LeftLikeRightBuffer();
        }
        else if (command == "SAVE") {
            graph.RecordFromBuffer("test/vertex.txt");
        }
        else if (command == "SET") {
          if(!graph.Set()) {
              continue;
          }
        }
        else if (command == "TEST") {
            graph.Test();
        }
        else if (command == "TT") {
            graph.TT();
        }
    }
}