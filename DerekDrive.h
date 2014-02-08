#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#include <RobotDrive.h>
#include <SpeedController.h>
#include <Victor.h>
#include "Shift.h"
#include "SmoothJoystick.h"

enum side
{
    RIGHT,
    LEFT
};

class DerekDrive : public RobotDrive 
{
    public:
        DerekDrive::DerekDrive(uint8_t shiftMod, uint32_t shift1, uint32_t shift2,
                               //Victors
                               uint8_t modFL,uint32_t chanFL,
                               uint8_t modRL,uint32_t chanRL,
                               uint8_t modFR,uint32_t chanFR,
                               uint8_t modRR,uint32_t chanRR);
        ~DerekDrive();
        void autoDrive(float);
        void autoRotate();
        void doTeleOp();
        void stop();
        void setSafety();
        static void update(void*);
        void shiftGear();
    private:
        float drivePower; // 1.0 Normal and 0.6 Climbing
        bool isAsync;
        Shift* shifter;
        float ultrasonicPower;
        
        SmoothJoystick* driver;
};
#endif
