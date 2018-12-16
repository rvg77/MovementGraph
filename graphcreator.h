#include "kernelgraph.h"

class GraphCreator : public AL::ALModule {
 public:
  GraphCreator(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);

  virtual void init();

  void Rest();

  void Wake();

  void Snap();

  void SetName();

  void RunBuffer();

  void Reflect();

  void CopyToRight();

  void CopyToLeft();

  void Save() const;

  void Run();

  void Test();

  void TT();

 private:
  bool IsBufferEmpty() const;

  void SetBuffer(const Vertex& v);

  void ClearBuffer();

  std::string SmallLog(const std::string ) {

  }
 private:
  KernelGraph graph_;
  Vertex* vertex_buffer_;
};