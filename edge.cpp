#pragma once
#include "edge.h"

Edge::Edge(bool flag) {
  assert(flag == true);
}

Edge::Edge(const Vertex* from, const Vertex* to, float time)
  : begin_(from), end_(to), time_(time) {}

Edge::Edge(const Edge & edge)
  : begin_(edge.begin_), end_(edge.end_), time_(edge.time_) {}

const Vertex* Edge::GetBegin() const {
  return begin_;
}
const Vertex* Edge::GetEnd() const {
  return end_;
}
float Edge::GetTime() const {
  return time_;
}
