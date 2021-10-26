#include "cli.h"
CLI_Command_t allCmds[] = CMD_LIBRARY;

void CLI_help(CLI_Function_t pPrintFunction)
{
    pPrintFunction("============================================\n");
    pPrintFunction("* Overview of the available cli commands: *!\n");
    for(int i = 0; i < CMD_LIBRARY_SIZE; i++)
    {
        pPrintFunction(allCmds[i].pName);
        pPrintFunction("\n");
        pPrintFunction(allCmds[i].pHelp);
        pPrintFunction("\n");
    }
}