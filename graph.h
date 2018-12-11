//
// Created by coolhatsker on 12.12.18.
//

#ifndef MOVEMENTGRAPH_GRAPH_H
#define MOVEMENTGRAPH_GRAPH_H
#include <functional>
#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>
#include <alcommon/albroker.h>
#include <qi/log.hpp>
#include <alproxies/almotionproxy.h>
#include <queue>
#include <fstream>
#include <alproxies/albasicawarenessproxy.h>
#include "edge.h"

namespace AL
{
    class ALBroker;
}

class Graph {
public:
    Graph(boost::shared_ptr<AL::ALBroker> broker_);

    boost::shared_ptr<AL::ALBroker> getParentBroker() const;

    void initialize();

    void Test();

    void TT();

    bool Set();

    void CallBuffer();

    void StrongRest() const;

    void StrongWake() const;

    void SnapBuffer();

    void LeftLikeRightBuffer();

    void RightLikeLeftBuffer();

    void RecordFromBuffer(const std::string &output_file);

    void ReflectBuffer();

    void RunFromBuffer();
private:
    void SetNameBuffer(std::string name);

    bool FindWayToVertexFromVertex(const Vertex* start,
                                   const Vertex* finish,
                                   std::vector <const Edge*> &way) const;

    bool FindWayToVertexFromVertexViaBFS(int start,
                                         int finish,
                                         std::vector <int> & way) const;

    int GetNearestVertex();

    void RunChain(const std::vector <std::string>& chain, int cnt);

    void RunWay(std::vector <const Edge*> edges);

    void RunPosition(const Vertex* v, float velocity = 0.3);

    Vertex GetCurrentState() const;
private:
    std::vector <Vertex> vertexes_;
    std::vector <Edge> edges_;
    std::map<std::string, int> vertexes_by_name_;
    Vertex vertex_buffer_;
    Edge edge_buffer_;
    mutable std::map <const Vertex*, int> vertex_to_index_;
    std::vector <std::vector <int>> adjacency_list_;
    boost::shared_ptr<AL::ALBroker> broker;
};


#endif //MOVEMENTGRAPH_GRAPH_H
