#include "vertex.h"

class Edge {
 public:
  Edge() = delete;
  Edge(const Vertex* from, const Vertex* to, float time);
  Edge(const Edge& edge);

  const Vertex* GetBegin() const;
  const Vertex* GetEnd() const;
  float GetTime() const;
 private:
  const Vertex* begin_;
  const Vertex* end_;
  float time_;
};