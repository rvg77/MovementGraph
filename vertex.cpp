#pragma once
#include "vertex.h"

Vertex::Vertex(std::vector <float> new_param_values_, bool is_radian)
		: degree_values_(new_param_values_) {
	for (int i = 0; i < PARAM_NUM_; ++i) {
		float val = degree_values_[i];
		if (is_radian) {
      val = val * 180 / PI;
		} else {
      val = val * PI / 180;
		}
		radian_values_.push_back(val);
	}
	if (is_radian) {
		std::swap(degree_values_, radian_values_);
	}
}


Vertex::Vertex(const Vertex& vertex)
    : degree_values_(vertex.degree_values_),
    	radian_values_(vertex.radian_values_),
      adjacent_edges_(vertex.adjacent_edges_) {}



void Vertex::PrintState(std::ostream &out) {
  out << '{' << std::endl;
  for (size_t i = 0; i < PARAM_NUM_; ++i) {
    out << "    " << PARAM_NAMES[i] << " : " << degree_values_[i] << std::endl;
  }
  out << "}" << std::endl;
}


void Vertex::AddEdge(const Edge* new_edge) {
  adjacent_edges_.push_back(new_edge);
}


float Vertex::Dist(const Vertex& vertex) const {
	float result = 0;
	for (int i = 0; i < PARAM_NUM_; ++i) {
		float lin_dist = degree_values_[i] - vertex.degree_values_[i];
		result += lin_dist * lin_dist;
	}

	return result;
}


std::vector<float> Vertex::GetRadianValues() const {
	return radian_values_;
}


std::vector<float> Vertex::GetDegreesValues() const {
	return degree_values_;
}

const Edge* Vertex::GetEdge(int ind) const {
	assert(ind < adjacent_edges_.size());

	return adjacent_edges_[ind];
}