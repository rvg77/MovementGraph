#pragma once
#include "vertex.h"

Vertex::Vertex(std::vector <float> new_param_values_)
    : param_values_(new_param_values_) {}


Vertex::Vertex(const Vertex & vertex)
    : param_values_(vertex.param_values_),
      adjacent_edges_(vertex.adjacent_edges_) {}



void Vertex::PrintState(std::ostream &out) {
  out << '{' << std::endl;
  for (size_t i = 0; i < PARAM_NUM_; ++i) {
    out << "    " << PARAM_NAMES[i] << " : " << param_values_[i] << std::endl;
  }
  out << "}" << std::endl;
}


void Vertex::AddEdge(const Edge* new_edge) {
  adjacent_edges_.push_back(new_edge);
}


float Vertex::GetMetrics(Vertex& vertex) {
	float result = 0;
	const std::vector<float> & cords = vertex.GetParamValues();
	for (int i=0; i < PARAM_NUM_ ; i++) {
		result += (param_values_[i] - cords[i])*(param_values_[i] - cords[i]);
	}

	return result;
}


std::vector<float> Vertex::GetParamValues() const {
	return param_values_;
}


std::vector<float> Vertex::GetDegreesValues() const {
	std::vector<float> cords;
	for (auto el : param_values_) {
		cords.push_back(el * 180.0/PI);
	}
	return cords;
}