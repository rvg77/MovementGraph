#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

class Edge;

enum JOINT_TYPE {
  LEFT,
  MID,
  RIGHT
};

const float PI = 3.14159265;

const size_t PARAM_NUM_ = 24;

const std::vector <std::string> PARAM_NAMES = {
    "HeadYaw",
    "HeadPitch",

    "LShoulderPitch",
    "LShoulderRoll",
    "LElbowYaw",
    "LElbowRoll",
    "LWristYaw",

    "RShoulderPitch",
    "RShoulderRoll",
    "RElbowYaw",
    "RElbowRoll",
    "RWristYaw",

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
    "RAnkleRoll" };

const std::vector <int> PAIR_JOINT = {
    0,
    1,

    7,
    -8,
    -9,
    -10,
    11,

    2,
    -3,
    -4,
    -5,
    6,

    18,
    -19,
    20,
    21,
    22,
    -23,

    12,
    -13,
    14,
    15,
    16,
    -17 };

const std::vector <JOINT_TYPE> JOINT_TYPES = {
    MID,
    MID,

    LEFT,
    LEFT,
    LEFT,
    LEFT,
    LEFT,

    RIGHT,
    RIGHT,
    RIGHT,
    RIGHT,
    RIGHT,

    LEFT,
    LEFT,
    LEFT,
    LEFT,
    LEFT,
    LEFT,

    RIGHT,
    RIGHT,
    RIGHT,
    RIGHT,
    RIGHT,
    RIGHT };

class Vertex {
 public:
  Vertex() = delete;
  Vertex(bool flag);
  Vertex(std::vector <float> new_param_values_, bool is_radian = false);
  Vertex(const Vertex& vertex);

  Vertex& operator =(const Vertex& vertex);

  float Dist(const Vertex& vertex) const;

  void SetName(std::string name);

  std::string GetName() const;

  std::vector<float> GetRadianValues() const;

  std::vector<float> GetDegreesValues() const;


  void AddEdge(const Edge* new_edge);

  void PrintState(std::ostream &out);

  const Edge* GetEdge(int ind) const;

  void Reflect();

  void CopyFromSide(JOINT_TYPE side_name);
 private:
  std::string name_;
  std::vector <float> degree_values_;
  std::vector <float> radian_values_;
  std::vector <const Edge*> adjacent_edges_;
};