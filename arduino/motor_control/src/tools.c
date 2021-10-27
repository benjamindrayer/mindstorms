#include "tools.h"
#include <string.h>

TOOLS_PrintFunction_t printFunction = NULL;
TOOLS_AnalogWriteFunction_t analogWriteFunction = NULL;
TOOLS_DigitalWriteFunction_t digitalWriteFunction = NULL;
TOOLS_DigitalReadFunction_t digitalReadFunction = NULL;

/////////////////////////////////////////////////////////////////////////////////
// I/O
/////////////////////////////////////////////////////////////////////////////////
void TOOL_setAnalogWriteFunction(TOOLS_AnalogWriteFunction_t pAnalogWrite)
{
    analogWriteFunction = pAnalogWrite;
}

void TOOL_setDigitalWriteFunction(TOOLS_DigitalWriteFunction_t pDigitalWrite)
{
    digitalWriteFunction = pDigitalWrite;
}

void TOOL_setDigitalReadFunction(TOOLS_DigitalReadFunction_t pDigitalRead)
{
    digitalReadFunction = pDigitalRead;
}

void TOOL_writeAnalog(int pin, int value)
{
    analogWriteFunction(pin, value);
}

void TOOL_writeDigital(int pin, int value)
{
    digitalWriteFunction(pin, value);
}

int TOOL_readDigital(int pin)
{
    return digitalReadFunction(pin);
}

/////////////////////////////////////////////////////////////////////////////////
// Printing 
/////////////////////////////////////////////////////////////////////////////////

void TOOL_setPrintCommand(TOOLS_PrintFunction_t pPrintFunction)
{
    printFunction = pPrintFunction;
}

void TOOL_print(const char* pData)
{
    if(printFunction)
    {
        printFunction(pData);
    }
}

int TOOL_parseArgument(const char* pString,
                       char* pArgument)
{
    int index = 0;
    int offset = 0;
    while(*pString == ' ')
    {
        pString++;
        offset++;
    }
    while(pString)
    {
        if(*pString == ' ' || *pString == '\n')
        {
            break;
        }
        pArgument[index] = *pString;
        pString++;
        index++;
    }
    pArgument[index] = 0;
    return index + offset;
}