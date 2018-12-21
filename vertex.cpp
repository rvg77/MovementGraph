#pragma once
#include <assert.h>
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
      adjacent_edges_(vertex.adjacent_edges_),
      name_(vertex.name_){}


Vertex& Vertex::operator =(const Vertex& vertex) {
	degree_values_ = vertex.degree_values_;
	radian_values_ = vertex.radian_values_;
	adjacent_edges_ = vertex.adjacent_edges_;
	name_ = vertex.name_;
}

void Vertex::PrintState(std::ostream &out) const {
  out << name_ << " {" << std::endl;
  for (size_t i = 0; i < PARAM_NUM_; ++i) {
    out << "    " << PARAM_NAMES[i] << " : " << degree_values_[i] << std::endl;
  }
  out << "}" << std::endl;
}

void Vertex::SetName(const std::string& name) {
	name_ = name;
}

std::string Vertex::GetName() const {
	return name_;
}

int Vertex::GetAdjacentCount() const {
	return adjacent_edges_.size();
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

void Vertex::Reflect() {
	for (int i = 0; i < PARAM_NUM_; ++i) {
		if (JOINT_TYPES[i] == RIGHT) {
			continue;
		}
    int k = PAIR_JOINT[i] < 0 ? -1 : 1;
		int j = abs(PAIR_JOINT[i]);
    radian_values_[i] *= k;
    degree_values_[i] *= k;
		std::swap(radian_values_[i], radian_values_[j]);
		std::swap(degree_values_[i], degree_values_[j]);
    radian_values_[i] *= k;
    degree_values_[i] *= k;
	}
}

void Vertex::CopyFromSide(JOINT_TYPE side_name) {
  for (int i = 0; i < PARAM_NUM_; ++i) {
  	if (JOINT_TYPES[i] == side_name) {
  		int k = PAIR_JOINT[i] < 0 ? -1 : 1;
  		int j = abs(PAIR_JOINT[i]);
  		assert(j < PARAM_NUM_);

  		radian_values_[j] = k * radian_values_[i];
			degree_values_[j] = k * degree_values_[i];
  	}
  }
}
