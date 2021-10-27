typedef struct
{
    //Outputs
    int pinEnable;  ///< Pin to control the power of the motor (PWM)
    int pinInput0;  ///< Pin0 and Pin1 of the H-Bridge, 01 -> FWD 
    int pinInput1;  ///<                                10 -> BACK
                    ///<                                00 -> STOP
                    ///<                                11 -> STOP
    //Inputs
    int pinEncoder0;    ///< Pin0 and Pin1 of the rotationary encoder
    int pinEncoder1;
}
MOTOR_MotorConfig_t;

typedef struct
{
    int id;
    int speed;
    int currentPosition;    //
    int targetPosition;     //
    int encoderValue;
    int direction;          //direction
    MOTOR_MotorConfig_t config;     //PinConfiguration
}
 MOTOR_Motor_t;

void MOTOR_config(int motor_id,
                  int rotEncoder0,
                  int rotEncoder1,
                  int pin1,
                  int pin2,
                  int pinEnable);


void CLI_MOTOR_set(const char* pArguments);
#define CLI_MOTOR_SET_CMD_NAME "motor_set"
#define CLI_MOTOR_SET_CMD_HELP "\
motor_set [motor_id] [speed] sets the speed of the motor with motor_id\n \
          motor_id: 0,...,n\n \
          speed: -100,...,100\n"
#define CLI_MOTOR_SET_CMD_NARGS 2

void CLI_MOTOR_get(const char* pArguments);
#define CLI_MOTOR_GET_CMD_NAME "motor_get"
#define CLI_MOTOR_GET_CMD_HELP "\
motor_get [motor_id] gets the status of the motor with motor_id\n \
          motor_id: 0,...,n\n"
#define CLI_MOTOR_GET_CMD_NARGS 1

void MOTOR_updatePosition();