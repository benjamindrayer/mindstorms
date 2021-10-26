
void CLI_MOTOR_set(const char* pArguments);
#define CLI_MOTOR_SET_CMD_NAME "MOTOR_SET"
#define CLI_MOTOR_SET_CMD_HELP "\
MOTOR_SET [motor_id] [speed] sets the speed of the motor with motor_id\n \
          motor_id: 0,...,n\n \
          speed: -100,...,100\n"
#define CLI_MOTOR_SET_CMD_NARGS 2

void CLI_MOTOR_get(const char* pArguments);
#define CLI_MOTOR_GET_CMD_NAME "MOTOR_GET"
#define CLI_MOTOR_GET_CMD_HELP "\
MOTOR_GET [motor_id] gets the status of the motor with motor_id\n \
          motor_id: 0,...,n\n"
#define CLI_MOTOR_GET_CMD_NARGS 1
