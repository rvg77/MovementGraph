#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>

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
  class Edge;

  class Vertex {
   public:
    Vertex() = delete;
    Vertex(std::vector <float> new_param_values_);

    Vertex(const Vertex & vertex);

    void GetCurrentState(boost::shared_ptr<AL::ALBroker> broker_ );
    void Run(float velocity_, boost::shared_ptr<AL::ALBroker> broker_);

    void AddEdge(const Edge* new_edge);
   private:
    static const size_t PARAM_NUM_;
    static const std::vector <std::string> param_names_;

    std::vector <float> param_values_; // +? const

    std::vector <const Edge*> adjacent_edges_;
  };

  class Edge {
   public:
    Edge() = delete;
    Edge(const Vertex* from, const Vertex* to, float velocity);
    Edge(const Edge & edge);
    const Vertex* GetBegin() const;
    const Vertex* GetEnd() const;

   private:
    const Vertex* begin_;
    const Vertex* end_;
    float velocity_;
  };

  bool FindWayToVertexFromVertexViaBFS(int start, 
                                       int finish, 
                                       std::vector <int> & way) const;


 void RunWay(std::vector <Edge *> edges);

 private:
  std::vector <Vertex> vertexes_;
  std::vector <Edge> edges_;
  std::map <const Vertex*, int> vertex_to_index_;
 private:
  std::vector <std::vector <int>> adjacency_list_;
};
