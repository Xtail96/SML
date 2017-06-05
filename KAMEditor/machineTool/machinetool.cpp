#include "machinetool.h"

/*const int GET_TERMO = 0x01;

const int LUBRICATE_SYSTEM_1_ON = 0x02;
const int LUBRICATE_SYSTEM_2_ON = 0x03;
const int LUBRICATE_SYSTEM_3_ON = 0x04;
const int LUBRICATE_SYSTEM_4_ON = 0x05;
const int LUBRICATE_SYSTEM_1_OFF = 0x06;
const int LUBRICATE_SYSTEM_2_OFF = 0x07;
const int LUBRICATE_SYSTEM_3_OFF = 0x08;
const int LUBRICATE_SYSTEM_4_OFF = 0x09;

const int INVERT_LINK_LED = 0x0A;
const int INVERT_LASER_LINK_LED = 0x0B;

const int PNEUMATIC_ACTURATOR_1_ON = 0x0C;
const int PNEUMATIC_ACTURATOR_2_ON = 0x0D;
const int PNEUMATIC_ACTURATOR_3_ON = 0x0E;
const int PNEUMATIC_ACTURATOR_4_ON = 0x0F;
const int PNEUMATIC_ACTURATOR_5_ON = 0x10;
const int PNEUMATIC_ACTURATOR_6_ON = 0x11;

const int PNEUMATIC_ACTURATOR_1_OFF = 0x12;
const int PNEUMATIC_ACTURATOR_2_OFF = 0x13;
const int PNEUMATIC_ACTURATOR_3_OFF = 0x14;
const int PNEUMATIC_ACTURATOR_4_OFF = 0x15;
const int PNEUMATIC_ACTURATOR_5_OFF = 0x16;
const int PNEUMATIC_ACTURATOR_6_OFF = 0x17;

const int INVERT_SENSORS_LED = 0x18;

const int TOOL_RELEASE_ON = 0x19;
const int TOOL_RELEASE_OFF = 0x1A;

const int ELECTROMAGNETIC_COUPLING_1_ON = 0x1B;
const int ELECTROMAGNETIC_COUPLING_2_ON = 0x1C;
const int ELECTROMAGNETIC_COUPLING_3_ON = 0x1D;

const int ELECTROMAGNETIC_COUPLING_1_OFF = 0x1E;
const int ELECTROMAGNETIC_COUPLING_2_OFF = 0x1F;
const int ELECTROMAGNETIC_COUPLING_3_OFF = 0x20;

const int LASER_POWER_ON = 0x21;
const int LASER_POWER_OFF = 0x22;

const int SHIELD_OPEN = 0x33;
const int SHIELD_CLOSE = 0x34;

const int START_FORWARD_MOVE = 1;
const int START_BACKWARD_MOVE = 2;
const int START_LEFT_MOVE = 3;
const int START_RIGHT_MOVE = 4;
const int START_UP_MOVE = 5;
const int START_DOWN_MOVE = 6;
const int SET_MAX_SPEED = 7;
const int SET_VOLTAGE = 8;
const int GET_MCU_STATE = 9;

const int START_FORWARDLEFT = 10;
const int START_FORWARDRIGHT = 11;
const int START_BACKWARDRIGHT = 12;
const int START_BACKWARDLEFT = 13;
const int STOP_MOVE = 14;

const int SWITCH_OFF_STEPPERS = 15;
const int SET_DEVICES = 16;
const int SOFT_STOP = 17;
const int CLEAR_BUFFER = 18;
const int SET_MCU_POS = 19;
const int GET_STEPPER_INFO = 20;
const int SET_STEPPER_STATE = 21;
const int GLOBAL_STOP = 22;
const int SET_UP_DIR = 23;
const int MOVE_BY_PROGRAM = 24;
const int DRIVES_OFF = 25;
const int RESTORE_DRIVES = 26;
const int ZERO_SEARCH = 27;
const int BAZA_SEARCH = 30;//28;
const int ANALYZE_SENSORS = 35;
const int SEARCH_SENSOR = 36;
const int SENSORS_ANALYZE_MODE= 37;
const int REPROGRAM_SPEED_PREPARE = 38;
const int REPROGRAM_SPEED = 39;
const int CHANGE_TEMPERATURE = 42;
const int SEND_TO_S_BOARD = 50;
const int RE_PROGRAM = 117;
const int TOOL_LENGTH_SEARCH = 31;
const int SWITCH_PNEUMO = 60;

const int SEARCH_SOFT_ZERO_SENSOR = 0x0C;
const int SEARCH_SOFT_TOOL_SENSOR = 0x0B;
const int SEARCH_ATC_SENSOR = 0x0D;*/



MachineTool& MachineTool::Instance()
{
    static MachineTool m;
    return m;
}


MachineTool::MachineTool()
{
    baseStatus = false;
    edgesControlEnable = false;
    spindleEnable = false;
    spindleWarmUp = false;
//    dimensions.x = 0;
//    dimensions.y = 0;
//    dimensions.z = 0;
//    dimensions.a = 0;
//    dimensions.b = 0;
    axisCount = 0;
    machineToolAxis = {};
//    for(unsigned int i = 0; i < axisCount; i++)
//    {
//        AxisKFlopSettings tmp;
//        tmp.jerk = 0;
//        tmp.acceleration = 0;
//        tmp.velocity = 0;
//        tmp.channel = 0;
//        tmp.basingVelocity = 0;
//        axisKFlopSettings.push_back(tmp);
//    }
}

/*MachineTool::MachineTool(unsigned int axisCount)
{
    baseStatus = false;
    edgesControlEnable = false;
    spindleEnable = false;
    spindleWarmUp = false;
    machineToolAxis = {};
    addMachineToolAxis(axisCount);
}*/

MachineTool::~MachineTool()
{

}


VectorDouble MachineTool::getBaseCoordinates()
{
    return base;
}


VectorDouble MachineTool::getCurrentCoordinates()
{
    return current;
}


VectorDouble MachineTool::getParkCoordinates()
{
    return park;
}

std::string MachineTool::getSettingsPath()
{
    return settingsPath;
}

void MachineTool::setSettingsPath(std::string s)
{
    settingsPath = s;
}

bool MachineTool::getBaseStatus()
{
    return baseStatus;
}

void MachineTool::setBaseStatus(bool value)
{
    baseStatus = value;
}

bool MachineTool::getEdgesControlEnable()
{
    return edgesControlEnable;
}

void MachineTool::setEdgesControlEnable(bool value)
{
    edgesControlEnable = value;
}

bool MachineTool::getSpindleEnable()
{
    return spindleEnable;
}

void MachineTool::setSpindleEnable(bool value)
{
    spindleEnable = value;
}

bool MachineTool::getSpindleWarmUp()
{
    return spindleWarmUp;
}

void MachineTool::setSpindleWarmUp(bool value)
{
    spindleWarmUp = value;
}

void MachineTool::stepMove(VectorDouble f)
{
    double current_step = (step > 0) ? step : 0.01;

    current.x += f.x * current_step;
    current.y += f.y * current_step;
    current.z += f.z * current_step;
    current.a += f.a * current_step;
    current.b += f.b * current_step;


    base.x += f.x * current_step;
    base.y += f.y * current_step;
    base.z += f.z * current_step;
    base.a += f.a * current_step;
    base.b += f.b * current_step;
}

//VectorDouble MachineTool::getDimensions()
//{
//    return dimensions;
//}

//void MachineTool::setDimensions(VectorDouble v)
//{
//    dimensions = v;
//}

//std::vector<bool> MachineTool::getDirections()
//{
//    return directions;
//}

//void MachineTool::setDirections(std::vector<bool> v)
//{
//    directions = v;
//}


void MachineTool::setParkCoordinates(VectorDouble f)
{
    park.x = f.x;
    park.y = f.y;
    park.z = f.z;
    park.a = f.a;
    park.b = f.b;
}
void MachineTool::setNewZeroCoordinates(VectorDouble f)
{
    zero.x = base.x;
    zero.y = base.y;
    zero.z = base.z;
    zero.a = base.a;
    zero.b = base.b;

    current.x = 0;
    current.y = 0;
    current.z = 0;
    current.a = 0;
    current.b = 0;
}

//void MachineTool::setDistanceByOneStep(VectorDouble v)
//{
//    distanceByOneStep = v;
//}
//VectorDouble MachineTool::getDistanceByOneStep()
//{
//    return distanceByOneStep;
//}

//void MachineTool::setStepQuantityByOneMm(VectorDouble v)
//{
//    stepQuantityByOneMm = v;
//}
//VectorDouble MachineTool::getStepQuantityByOneMm()
//{
//    return stepQuantityByOneMm;
//}

void MachineTool::setExternalDevices(std::map<std::string, bool> m)
{
    externalDevices = m;
}
std::map<std::string, bool> MachineTool::getExternalDevices()
{
    return externalDevices;
}

//void MachineTool::setAxisKFlopSettings(std::vector<AxisKFlopSettings> s)
//{
//   for(unsigned int i = 0; i< axisKFlopSettings.size(); i++)
//   {
//       axisKFlopSettings[i] = s[i];
//   }
//}

//std::vector<AxisKFlopSettings> MachineTool::getAxisKFlopSettings()
//{
//    return axisKFlopSettings;
//}

unsigned int MachineTool::getAxisCount()
{
    return axisCount;
}

void MachineTool::setAxisCount(const unsigned int &value)
{
    axisCount = value;
}

void MachineTool::addMachineToolAxis(const unsigned int &count)
{
    if(count <= 11)
    {
        setAxisCount(count);
    }
    else
    {
        setAxisCount(11);
    }
    for(unsigned int i = 0; i < axisCount; i++)
    {
        std::string axisName = axisNames.getNameByKey(i);
        Axis newAxis(axisName);
        machineToolAxis.push_back(newAxis);
    }

   /* for(auto it : machineToolAxis)
    {
        it.setupAxisSettings();
    }*/
    setupMachineToolAxises();
}

void MachineTool::setupMachineToolAxises()
{
    SettingsManager settings;
    std::map<std::string, std::string> settingsMap = settings.getSettings();
    if(settingsMap.size() != 0)
    {
        /*for(auto axis : machineToolAxis)
        {
            axis.setup(settingsMap);
        }*/
        for(unsigned int i = 0; i < machineToolAxis.size(); i++)
        {
           machineToolAxis[i].setup(settingsMap);
        }
    }
}

std::vector<Axis> &MachineTool::getMachineToolAxis()
{
    return machineToolAxis;
}

void MachineTool::setMachineToolAxis(const std::vector<Axis> &value)
{
    machineToolAxis = value;
}

std::vector<Sensor> MachineTool::getMachineToolSensors() const
{
    return machineToolSensors;
}

void MachineTool::addMachineToolSensor(Sensor s)
{
    machineToolSensors.push_back(s);
}
