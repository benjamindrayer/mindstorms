#include "motor_control.h"
#include "tools.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_MOTORS 3
MOTOR_Motor_t motors[MAX_MOTORS];

void MOTOR_config(int motor_id,
                  int pinEnable,
                  int pin1,
                  int pin2)
{
    motors[motor_id].config.pinEnable = pinEnable;
    motors[motor_id].config.pinInput0 = pin1;
    motors[motor_id].config.pinInput1 = pin2;
}

void MOTOR_set_speed(int motor_id, 
                     int speed)
{
    if(0<= motor_id && motor_id<MAX_MOTORS )
    {
        motors[motor_id].speed = speed;
        if(speed<0)
        {
            TOOL_writeDigital(motors[motor_id].config.pinInput0, 1);
            TOOL_writeDigital(motors[motor_id].config.pinInput1, 0);
            TOOL_writeAnalog(motors[motor_id].config.pinEnable, -speed);
        }
        if(speed>0)
        {
            TOOL_writeDigital(motors[motor_id].config.pinInput0, 0);
            TOOL_writeDigital(motors[motor_id].config.pinInput1, 1);
            TOOL_writeAnalog(motors[motor_id].config.pinEnable, speed);
        }
        if(speed==0)
        {
            TOOL_writeDigital(motors[motor_id].config.pinInput0, 0);
            TOOL_writeDigital(motors[motor_id].config.pinInput1, 0);
            TOOL_writeAnalog(motors[motor_id].config.pinEnable, 0);
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

void MOTOR_print(int motor_id)
{
    char aBuffer[40];
    sprintf(aBuffer, "Motor :%i\n", motor_id);
    TOOL_print(aBuffer);
    sprintf(aBuffer, " -speed: %i\n", motors[motor_id].speed);
    TOOL_print(aBuffer);
    sprintf(aBuffer, " -position: %i\n", motors[motor_id].currentPosition);
    TOOL_print(aBuffer);
}

void CLI_MOTOR_get(const char* pArguments)
{
    char aArgument0[10];
    int len0 = TOOL_parseArgument(pArguments, aArgument0);    
    MOTOR_print(atoi(aArgument0));
}
