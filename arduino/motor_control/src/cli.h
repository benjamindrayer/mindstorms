//TODO include guards
//TODO blabla
#ifndef CLI_H
#define CLI_H
#include "motor_control.h"
#include "tools.h"

typedef void (*CLI_Function_t)(const char*);

typedef struct
{
  const char* pName;
  const char* pHelp;
  int nArguments;
  CLI_Function_t pFunction;
} CLI_Command_t;

void CLI_HELP(const char* pArguments);
#define CLI_HELP_CMD_NAME "help"
#define CLI_HELP_CMD_HELP "help shows this help page: \n"
#define CLI_HELP_CMD_NARGS 0

#define CMD_LIBRARY {{CLI_HELP_CMD_NAME, CLI_HELP_CMD_HELP, CLI_HELP_CMD_NARGS, CLI_HELP},\
                     {CLI_MOTOR_SET_CMD_NAME, CLI_MOTOR_SET_CMD_HELP, CLI_MOTOR_SET_CMD_NARGS, CLI_MOTOR_set},\
                     {CLI_MOTOR_GET_CMD_NAME, CLI_MOTOR_GET_CMD_HELP, CLI_MOTOR_GET_CMD_NARGS, CLI_MOTOR_get}}

#define CMD_LIBRARY_SIZE  3

void CLI_process(const char* pCommand);
#endif