#include "movementgraph.h"
#include <iostream>
#include <alcommon/albroker.h>
#include <qi/log.hpp>
#include <alproxies/almotionproxy.h>
#include <assert.h>
using namespace AL;


MovementGraph::Edge::Edge(Vertex* from, Vertex* to, float velocity)
  : begin_(from), end_(to), velocity_(velocity) {}

MovementGraph::Edge::Edge(const Edge & edge)
  : begin_(edge.begin_), end_(edge.end_), velocity_(edge.velocity_) {}