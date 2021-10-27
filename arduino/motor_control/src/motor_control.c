#include "motor_control.h"
#include "tools.h"
#include <stdlib.h>

#define MAX_MOTORS 3
MOTOR_Motor_t motors[MAX_MOTORS];

void MOTOR_init(void)
{
    for(int i = 0 ; i<MAX_MOTORS; i++)
    {
        motors[i].id = i;
        motors[i].speed = 0;
        motors[i].position = 0;
    }
}

void MOTOR_config(int motor_id,
                  int pinEnable,
                  int pin1,
                  int pin2)
{
    motors[motor_id].enablePin = pinEnable;
    motors[motor_id].input1Pin = pin1;
    motors[motor_id].input2Pin = pin2;
}

void MOTOR_set_speed(int motor_id, 
                     int speed)
{
    if(0<= motor_id && motor_id<MAX_MOTORS )
    {
        motors[motor_id].speed = speed;
        if(speed<0)
        {
            TOOL_writeDigital(motors[motor_id].input1Pin, 1);
            TOOL_writeDigital(motors[motor_id].input2Pin, 0);
            TOOL_writeAnalog(motors[motor_id].enablePin, -speed);
        }
        if(speed>0)
        {
            TOOL_writeDigital(motors[motor_id].input1Pin, 0);
            TOOL_writeDigital(motors[motor_id].input2Pin, 1);
            TOOL_writeAnalog(motors[motor_id].enablePin, speed);
        }
        if(speed==0)
        {
            TOOL_writeDigital(motors[motor_id].input1Pin, 0);
            TOOL_writeDigital(motors[motor_id].input2Pin, 0);
            TOOL_writeAnalog(motors[motor_id].enablePin, 0);
        }
    }
}

void CLI_MOTOR_set(const char* pArguments)
{
    char aArgument0[10];
    char aArgument1[10];
    int len0 = TOOL_parseArgument(pArguments, aArgument0);
    int len1 = TOOL_parseArgument(&pArguments[len0], aArgument1);
    MOTOR_set_speed(atoi(aArgument0), atoi(aArgument1));
}

void CLI_MOTOR_get(const char* pArguments)
{
    
}
