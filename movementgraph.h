#include <functional>
#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>

const float PI = 3.14159265;

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
    void Run(float velocity_, boost::shared_ptr<AL::ALBroker> broker_) const;

    float GetMetrics(Vertex& vertex);

    std::vector<float>  const & GetParamValues();

    std::vector<float>  const & GetDegreesValues();

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

  bool FindWayToVertexFromVertex(const Vertex* start, const Vertex* finish,
                                 std::vector <const Edge*> way) const;

  bool FindWayToVertexFromVertexViaBFS(int start, 
                                       int finish, 
                                       std::vector <int> & way) const;

  int GetNearestVertex(boost::shared_ptr<AL::ALBroker> broker_);

  void RunWay(std::vector <Edge *> edges);


 private:
  std::vector <Vertex> vertexes_;
  std::vector <Edge> edges_;
  mutable std::map <const Vertex*, int> vertex_to_index_;
 private:
  std::vector <std::vector <int>> adjacency_list_;
};
