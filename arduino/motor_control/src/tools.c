#include "tools.h"
#include <string.h>

TOOLS_PrintFunction_t printFunction = NULL;

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
    while(*pString == ' ')
    {
        pString++;
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
    return index;
}