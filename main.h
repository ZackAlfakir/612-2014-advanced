#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>

#include "SmoothJoystick.h"
#include "Shift.h"
#include "Pneumatics.h"
#include "DerekDrive.h"

#include "UpdateRegistry.h"


class robot_class : public IterativeRobot
{
public:
    robot_class();

    void RobotInit();

    void DisabledInit();
    void DisabledPeriodic();

    void AutonomousInit();
    void AutonomousPeriodic();

    void TeleopInit();
    void TeleopPeriodic();

    void TestInit();
    void TestPeriodic();
    
    //DerekDrive* test_drivetrain;
    SmoothJoystick* driverJoy;
    Shift* shifter;
    
    SmoothJoystick* driver;
    DerekDrive* drivetrain;
    
    UpdateRegistry updateRegistry;
    Pneumatics* pnum;
    
private:
};

#endif // MAIN_H
