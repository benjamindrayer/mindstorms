#include "cli.h"
#include <string.h>

CLI_Command_t allCmds[] = CMD_LIBRARY;

void CLI_help()
{
    TOOL_print("============================================\n");
    for(int i = 0; i < CMD_LIBRARY_SIZE; i++)
    {
        TOOL_print(allCmds[i].pName);
        TOOL_print("\n");
        TOOL_print(allCmds[i].pHelp);
        TOOL_print("\n");
    }
}

void CLI_HELP(const char* pArguments)
{
    CLI_help();
}

void CLI_process(const char* pCommand)
{
    const char* pTemp = pCommand;
    int index = 0;
    while(*pTemp)
    {
        if(*pTemp == ' ' || pTemp == NULL || *pTemp == '\n' || *pTemp == '\r')
        {
            break;
        }
        index++;
        pTemp++;
    }
    //Find the command
    int cmdIndex = -1;
    for(int i = 0;i<CMD_LIBRARY_SIZE;i++)
    {
        if(index == strlen(allCmds[i].pName))
        {
            int same = 1;
            for(int j = 0;j<index;j++)
            {
                if(pCommand[j] != allCmds[i].pName[j])
                {
                    same = 0;
                    break;
                }
            }
            if(same)
            {
                cmdIndex = i;
            }
        }
    }
    if(cmdIndex>=0)
    {
        allCmds[cmdIndex].pFunction(pTemp);
    }
}