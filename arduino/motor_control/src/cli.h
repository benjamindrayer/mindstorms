//TODO include guards
//TODO blabla
#ifndef CLI_H
#define CLI_H
#include "motor_control.h"

typedef void (*CLI_Function_t)(const char*);

typedef struct
{
  const char* pName;
  const char* pHelp;
  int nArguments;
  CLI_Function_t pFunction;
} CLI_Command_t;

#define CMD_LIBRARY {{CLI_MOTOR_SET_CMD_NAME, CLI_MOTOR_SET_CMD_HELP, CLI_MOTOR_SET_CMD_NARGS, CLI_MOTOR_set},\
                     {CLI_MOTOR_GET_CMD_NAME, CLI_MOTOR_GET_CMD_HELP, CLI_MOTOR_GET_CMD_NARGS, CLI_MOTOR_get}}

#define CMD_LIBRARY_SIZE  2

void CLI_help(CLI_Function_t pFun);
#endif