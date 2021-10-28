#include "motor_control.h"
#include "tools.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_MOTORS 3
MOTOR_Motor_t motors[MAX_MOTORS];

void MOTOR_config(int motor_id,
                  int rotEncoder0,
                  int rotEncoder1,
                  int pin1,
                  int pin2,
                  int pinEnable)
{
    motors[motor_id].config.pinEnable = pinEnable;
    motors[motor_id].config.pinInput0 = pin1;
    motors[motor_id].config.pinInput1 = pin2;
    motors[motor_id].config.pinEncoder0 = rotEncoder0;
    motors[motor_id].config.pinEncoder1 = rotEncoder1;
    motors[motor_id].freeRunMode = 1;
}

int deltaC(int oldVal, int newVal)
{
    int factor = -1;
    int oldBit1 = oldVal>>1;
    int newBit1 = newVal>>1;
    int oldBit0 = oldVal & 1;
    int newBit0 = newVal & 1;
    if(oldBit0 == newBit0)
    {
        int d = newBit1 - oldBit1;
        if(oldBit0 == 1)
        {
            d *= -1;
        }
        return d;
    }
    if(oldBit1 == newBit1)
    {
        int d = newBit0 - oldBit0;
        if(oldBit1 == 0)
        {
            d *= -1;
        }
        return d;
    }
}

void Motor_update(int motor_id)
{
    int val0 = TOOL_readDigital(motors[motor_id].config.pinEncoder0);
    int val1 = TOOL_readDigital(motors[motor_id].config.pinEncoder1);
    int valueNew = val0<<1 | val1;
    int d = deltaC(valueNew, motors[motor_id].encoderValue);
    motors[motor_id].encoderValue = valueNew;
    motors[motor_id].currentPosition+=d;
    if(motors[motor_id].freeRunMode==0)
    {
        if(motors[motor_id].speed>0 && motors[motor_id].targetPosition <= motors[motor_id].currentPosition)
        {
            motors[motor_id].freeRunMode = 1;
            MOTOR_set_speed(motor_id, 0);
        }
        if(motors[motor_id].speed<0 && motors[motor_id].targetPosition >= motors[motor_id].currentPosition)
        {
            motors[motor_id].freeRunMode = 1;
            MOTOR_set_speed(motor_id, 0);
        }
    }

}

void MOTOR_updateMotor0(void)
{
    Motor_update(0);
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

void MOTOR_rotate(int motor_id, int degrees)
{
    if(degrees == 0)
    {
        return;
    }
    //Target Position
    motors[motor_id].targetPosition = motors[motor_id].currentPosition + degrees;
    //Deactivate freerun mode
    motors[motor_id].freeRunMode = 0;
    //Let the engine run
    if(motors[motor_id].targetPosition > motors[motor_id].currentPosition)
    {
        MOTOR_set_speed(motor_id, 100);
    }
    if(motors[motor_id].targetPosition < motors[motor_id].currentPosition)
    {
        MOTOR_set_speed(motor_id, -100);
    }
}

void CLI_MOTOR_rotate(const char* pArguments)
{
    char aArgument0[10];
    char aArgument1[10];
    int len0 = TOOL_parseArgument(pArguments, aArgument0);
    int len1 = TOOL_parseArgument(&pArguments[len0], aArgument1);
    MOTOR_rotate(atoi(aArgument0), atoi(aArgument1));
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
    sprintf(aBuffer, " -target position: %i\n", motors[motor_id].targetPosition);
    TOOL_print(aBuffer);
    sprintf(aBuffer, " -free run: %i\n", motors[motor_id].freeRunMode);
    TOOL_print(aBuffer);
    sprintf(aBuffer, " -encoder value: %i %i\n", motors[motor_id].encoderValue & 1, motors[motor_id].encoderValue>>1 & 1);
    TOOL_print(aBuffer);
}

void CLI_MOTOR_get(const char* pArguments)
{
    char aArgument0[10];
    int len0 = TOOL_parseArgument(pArguments, aArgument0);    
    MOTOR_print(atoi(aArgument0));
}
