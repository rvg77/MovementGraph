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

    void AddEdge(Edge* new_edge);

    float GetMetrics(const Vertex& vertex);

			std::vector<float> GetParamValues();


   private:
    static const size_t PARAM_NUM_;
    static const std::vector <std::string> param_names_;

    std::vector <float> param_values_; // +? const

    std::vector <Edge*> adjacent_edges_;
  };

  class Edge {
   public:
    Edge() = delete;
    Edge(Vertex* from, Vertex* to, float velocity);
    Edge(const Edge & edge);

   private:
    const Vertex* begin_;
    const Vertex* end_;
    float velocity_;
  };

  bool FindWayToVertexFromVertexViaBFS(int start, 
                                       int finish, 
                                       std::vector <int> & way) const;
	int GetNearestVertex(boost::shared_ptr<ALBroker> broker_);

 private:
  std::vector <Vertex> vertexes_;
  std::vector <Edge> edges_;
  std::map <Vertex*, int> vertex_to_index_;
 private:
  std::vector <std::vector <int>> adjacency_list_;
};
