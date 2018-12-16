enum JOINT_TYPE {
  LEFT,
  MID,
  RIGHT
};

const std::string VERTEXES_FILE = "test/vertex.txt";

const float PI = 3.14159265;

const float DEFAULT_TIME = 1.3;
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
    -11,

    2,
    -3,
    -4,
    -5,
    -6,

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