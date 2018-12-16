#include "graphcreator.h"

GraphCreator::GraphCreator(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName) :
  ALModule(broker, name),
  graph_(pBroker),
  vertex_buffer_(nullptr) {}

virtual void GraphCreator::init() {
  // инициализируем граф
  graph_.initialize();


  while (true) {
    std::string command;
    std::cout << "--> ENTER command\n> ";
    std::cin >> command;

    if (command == "REST") {
      Rest()
    }
    else if (command == "WAKE") {
      Wake()()
    }
    else if (command == "SNAP") {
      Snap();
    }
    else if (command == "SET_NAME") {
      SetName();
    }
    else if (command == "RUN_B") {
      RunBuffer();
    }
    else if (command == "REFL") {
      Reflect();
    }
    else if (command == "LIKE_LEFT") {
      CopyToRight();
    }
    else if (command == "LIKE_RIGHT") {
      CopyToLeft();
    }
    else if (command == "SAVE") {
      Save();
    }
    else if (command == "RUN") {
      Run();
    }
    else if (command == "TEST") {
      Test();
    }
    else if (command == "TT") {
      TT();
    }
    else {
      std::cout << "----> UNKNOWN COMMAND\n" ;
    }
  }
}

void GraphCreator::Rest() {
  std::cout << "----> Going to the rest Position\n";

  graph_.StrongRest();
}

void GraphCreator::Wake() {
  std::cout << "----> Waking up!\n";

  graph_.StrongWake();
}

void GraphCreator::Snap() {
  std::cout << "----> Copy current State to the buffer\n";

  Vertex curr(GetCurrentState());
  vertex_buffer_ = curr;
}

void GraphCreator::SetName() {
  std::cout << "----> ENTER name for buffer vertex:\n";

  std::string name;
  std::cout << "----| "

  std::cin >> name;

  vertex_buffer_.SetName(name);
}

void GraphCreator::RunBuffer() {
  std::cout << "---->  Going to the buffer position!\n"

  graph_.RunPosition(&vertex_buffer_);
}

void GraphCreator::Reflect() {
  std::cout << "----> Change Left and Right sides!\n"
  vertex_buffer_.Reflect();
}

void GraphCreator::CopyToRight() {
  std::cout << "----> Copy Left state  to Right side!\n"

  vertex_buffer_.CopyFromSide(LEFT);
}

void GraphCreator::CopyToLeft() {
  std::cout << "----> Copy Right state to Left side!\n"

  vertex_buffer_.CopyFromSide(RIGHT);
}

void GraphCreator::Save() const {
  std::ofstream out(VERTEXES_FILE, std::ios_base::app);

  vertex_buffer_.PrintState(out);
}

void GraphCreator::Run() {
  std::string v_name;
  std::cout << "---->  ENTER Vertex Name:\n";
  std::cout << "----| ";
  std::cin >> v_name;

  if (vertexes_by_name_.find(v_name) == vertexes_by_name_.end()) {
    std::cout << "\t> Wrong vertex name)))\n";
    return false;
  } else {
    RunPosition(&vertexes_[vertexes_by_name_[v_name]], 0.1);
    return true;
  }
}


/*------- PRIVAT SPACE ---------*/


bool GraphCreator::IsBufferEmpty() const {
  return vertex_buffer_ =
}

void GraphCreator::SetBuffer(const Vertex& v);

void GraphCreator::ClearBuffer();
