#include "motor_control.h"
#include "tools.h"

void CLI_MOTOR_set(const char* pArguments)
{
    TOOL_print(pArguments);
    TOOL_print("\n");
    char aArgument0[10];
    char aArgument1[10];
    int len0 = TOOL_parseArgument(pArguments, aArgument0);
    int len1 = TOOL_parseArgument(&pArguments[len0+1], aArgument1);
    TOOL_print("PARDED\n");
    TOOL_print(aArgument0);
    TOOL_print("\n");
    TOOL_print(aArgument1);
    TOOL_print("\n");
}

void CLI_MOTOR_get(const char* pArguments)
{
    
}
