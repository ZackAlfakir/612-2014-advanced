#include "DerekDrive.h"
#include "main.h"
#include "612.h"
#include "UpdateRegistry.h"
#include "Controls.h"
#include "ports.h"

DerekDrive::DerekDrive(uint8_t shiftMod, uint32_t shift1, uint32_t shift2,
                       //talons
                       uint8_t modFL,uint32_t chanFL,
                       uint8_t modRL,uint32_t chanRL,
                       uint8_t modFR,uint32_t chanFR,
                       uint8_t modRR,uint32_t chanRR)
                    :RobotDrive(new Victor(modFL,chanFL),
                                new Victor(modRL,chanRL),
                                new Victor(modFR,chanFR),
                                new Victor(modRR,chanRR))
{
    shifter = new Shift(shiftMod,shift1,shift2);
    isAsync = false;
    //robot_class* robot = (robot_class*)o;
    drivePower = 1.0;
    //shift LOW (or high, but we need to have a default as seen from last year)
    driver = robot->driverJoy;
    robot->updateRegistry.add(this, &update);
    ultrasonic = new AnalogChannel(1,1); //TODO placeholder
}

DerekDrive::~DerekDrive()
{
    delete shifter;
}
void DerekDrive::autoDrive(float dist) 
{

}
void DerekDrive::autoRotate()
{
}
void DerekDrive::doTeleOp()
{
    static int count = 0;
    ultrasonicPower = (ultrasonic->GetVoltage()/0.0098); //TODO get conversion to distance
    if(!(driver -> IsAxisZero(DRIVER_LEFT_DRIVE_AXIS)) || !(driver -> IsAxisZero(DRIVER_RIGHT_DRIVE_AXIS)))
    {
        float left = driver -> GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
        float right = driver -> GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);
        TankDrive(left * DRIVE_POWER, right * DRIVE_POWER);
        static int output = 0;
        if (output % 25 == 0) 
        {
            printf("left: %f, right: %f", left, right);
        }
        output++;
    }
    else
    {
        TankDrive(0.0f, 0.0f);
    }
    if (count % 25 == 0)
    {
        std::printf("Ultrasonic Distance: %f \n", ultrasonicPower);
    }
    count++;
}
void DerekDrive::shiftGear()
{
    //TODO
    shifter -> shiftGear();
}
void DerekDrive::stop()
{
    TankDrive(0.0f, 0.0f);
}
void DerekDrive::setSafety()
{
    //TODO
}

void DerekDrive::update(void* o)
{
    DerekDrive* thisObj = (DerekDrive*)o;
    thisObj->doTeleOp();
}
