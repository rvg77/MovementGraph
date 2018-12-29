
enum JOINT_TYPE {
  LEFT,
  MID,
  RIGHT
};

const std::string VERTEXES_FILE = "test/vertex.txt";

const float PI     = 3.14159265;
const float TO_RAD = PI / 180;
const float TO_DEG = 180 / PI;
const float EPS    = 1e-5;
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
    RIGHT
};


const std::vector <std::string> MOVE_PARAM_NAMES  = {
    "MaxStepX",
    "MaxStepY",
    "MaxStepTheta",
    "MaxStepFrequency",
    "StepHeight",
    "TorsoWx",
    "TorsoWy"
};

const std::vector <float> MOVE_PARAM_DEFAULT = {
    0.040,  // MaxStepX
    0.140,  // MaxStepY
    0.349,  // MaxStepTheta
    1.0  ,  // MaxStepFrequency
    0.020,  // StepHeight
    0.000,  // TorsoWx
    0.000,  // TorsoWy
};

const float x_velocity     = 0.08;
const float y_velocity     = 0.02;
const float theta_velocity = 15 * TO_RAD;