#include <vector>
#include <string>
#include <iostream>

class Edge;

const float PI = 3.14159265;

const size_t PARAM_NUM_ = 25;

const std::vector <std::string> PARAM_NAMES = {
    "HeadPitch",
    "LShoulderPitch",
    "LShoulderRoll",
    "LElbowYaw",
    "LElbowRoll",
    "LWristYaw",
    "LHipYawPitch",
    "LHipRoll",
    "LHipPitch",
    "LKneePitch",
    "LAnklePitch",
    "LAnkleRoll",
    "RHipYawPitch",
    "RHipRoll",
    "RHipPitch",
    "RKneePitch",
    "RAnklePitch",
    "RAnkleRoll",
    "RShoulderPitch",
    "RShoulderRoll",
    "RElbowYaw",
    "RElbowRoll",
    "RWristYaw",
    "LHand",
    "RHand" };


class Vertex {
 public:
  Vertex() = delete;
  Vertex(std::vector <float> new_param_values_);
  Vertex(const Vertex& vertex);

  float GetMetrics(Vertex& vertex);

  std::vector<float> GetParamValues() const;

  std::vector<float> GetDegreesValues() const;

  void AddEdge(const Edge* new_edge);

  void PrintState(std::ostream &out);

  void AddEdge(Edge* new_edge);

 private:
  std::vector <float> param_values_;
  std::vector <const Edge*> adjacent_edges_;
};