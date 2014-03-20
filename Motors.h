#ifndef MOTORS_H
#define MOTORS_H

#include <vector>

#include <SpeedController.h>
#include <Talon.h>
#include <CANJaguar.h>
#include <Relay.h>

#include "ports.h"
#include "SmoothJoystick.h"
#include "Controls.h"
#include "FileProcessor.h"

enum motor_type
{
    TALON,
    CANJAG,
    RELAY
};

struct motor_info
{
    const char* name;
    motor_type type;
    uint8_t module;
    uint32_t channel;
    void* relay;
};

class Motors
{
public:
    Motors::Motors();
    Motors::~Motors();
    void runMotor(int motor);
    void disable();
    void setTalon(Talon* t, bool print, int motor);
    void setTalon(int motor, bool print);
    void launcher(bool print, float power);
    motor_info mot;
    std::vector<motor_info> motors;
    Relay* compressor; //Spike 1,1
    Talon* drivetrain[4];

    char* curInfo;
    char* filename;
    FileProcessor* fp;
    
    Talon* FR; //Talon 7
    Talon* FL; //Talon 1
    Talon* RR; //Talon 6
    Talon* RL; //T2
    int previousMotor;
private:
    //SmoothJoystick* joy;
    float joy;
    float power;
    float left;
    float right;
    void drive();
    void drive2(bool print);
    bool over_thresh;
    //const float THRESHHOLD = 0.1;
    
    Talon* grabber; //Talon 3
    CANJaguar* wormDrive;
    
    CANJaguar* tilt;
    
    void runJag(CANJaguar* jag, float power, bool print, float previousPower);
    void runCompressor(Relay* relay, float power, bool print);
    void controlPiston();
};
#endif
