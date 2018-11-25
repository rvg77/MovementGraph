#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

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
  Vertex(std::vector <float> new_param_values_, bool is_radian = false);
  Vertex(const Vertex& vertex);

  float Dist(const Vertex& vertex) const;

  std::vector<float> GetRadianValues() const;

  std::vector<float> GetDegreesValues() const;

  void AddEdge(const Edge* new_edge);

  void PrintState(std::ostream &out);

  const Edge* GetEdge(int ind) const ;
 private:
  std::vector <float> degree_values_;
  std::vector <float> radian_values_;
  std::vector <const Edge*> adjacent_edges_;
};