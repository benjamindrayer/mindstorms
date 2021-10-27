#ifndef TOOLS_H
#define TOOLS_H

typedef void (*TOOLS_PrintFunction_t)(const char*);
void TOOL_setPrintCommand(TOOLS_PrintFunction_t);
void TOOL_print(const char* pData);

int TOOL_parseArgument(const char* pString,
                       char* pArgument);
#endif