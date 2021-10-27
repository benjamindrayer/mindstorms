#ifndef TOOLS_H
#define TOOLS_H
#include <stdint.h>

typedef void (*TOOLS_PrintFunction_t)(const char*);
typedef void (*TOOLS_AnalogWriteFunction_t)(uint8_t, int);
typedef void (*TOOLS_DigitalWriteFunction_t)(uint8_t, uint8_t);
typedef int (*TOOLS_DigitalReadFunction_t)(uint8_t);

void TOOL_setAnalogWriteFunction(TOOLS_AnalogWriteFunction_t);
void TOOL_setDigitalWriteFunction(TOOLS_DigitalWriteFunction_t);
void TOOL_setDigitalReadFunction(TOOLS_DigitalReadFunction_t);

void TOOL_writeAnalog(int pin, int value); 
void TOOL_writeDigital(int pin, int value); 
int TOOL_readDigital(int pin); 

void TOOL_setPrintCommand(TOOLS_PrintFunction_t);
void TOOL_print(const char* pData);

int TOOL_parseArgument(const char* pString,
                       char* pArgument);
#endif