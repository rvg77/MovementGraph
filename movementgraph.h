#pragma once
#include <functional>
#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>
#include "edge.h"


namespace AL
{
  class ALBroker;
}


class MovementGraph : public AL::ALModule {
 public:
  MovementGraph(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);
  ~MovementGraph();

  virtual void init();

 private:
  void RecordMovement(const std::string &output_file);
  
  bool FindWayToVertexFromVertex(const Vertex* start,
                                 const Vertex* finish,
                                 std::vector <const Edge*> &way) const;

  bool FindWayToVertexFromVertexViaBFS(int start,
                                       int finish,
                                       std::vector <int> & way) const;

  int GetNearestVertex();

  void RunWay(std::vector <const Edge*> edges);

  Vertex GetCurrentState() const;
 private:
  std::vector <Vertex> vertexes_;
  std::vector <Edge> edges_;

 private:
  mutable std::map <const Vertex*, int> vertex_to_index_;
  std::vector <std::vector <int>> adjacency_list_;
};
