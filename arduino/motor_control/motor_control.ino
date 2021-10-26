#define MAX_CMD_LENGTH   128

void stearMotor1(const char* prt)
               {
               }
void motorStatus1(const char* prt)
               {
               }

#define CMD_LIBRARY {{"MOTOR_SET", 2, stearMotor1},\
                     {"MOTOR_GET", 1, motorStatus1}}

#define CMD_LIBRARY_SIZE  2

typedef void (*myfun)(const char*);

typedef struct
{
  const char* pName;
  int nArguments;
  myfun pFunction;
} cliCommand;

cliCommand allCmds[] = CMD_LIBRARY;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Native USB only
  }
}


void motorStatus(const int motorId)
{
  Serial.println("Engine status is unknown");  
}

int readCommand(char* pData, 
                const int maxLength)
{
  int readBytes = 0;
  while((Serial.available() > 0) && readBytes < maxLength) 
  {
    pData[readBytes] = Serial.read();
    readBytes++;
  }
  return readBytes;
}

int stearMotor(const int motorId,
               const int speed)
{
  return 0;
}

int processCommand(char* pData, 
                   const int maxLength)
{
  int i = 0;
  int cmdIndex = -1;
  while(i<maxLength)
  {
    if(pData[i] == ' ')
    {
      for(int j=0;j<CMD_LIBRARY_SIZE;j++)
      {
        Serial.println(allCmds[j].pName);
        if(strlen(allCmds[j].pName) == i)
        {
          Serial.println("CMD: Found");
          cmdIndex = j;
          break;
        }
      }
      break;
    }
    i++;
  }
  if(cmdIndex==-1)
  {
    Serial.println("CMD: Not Found");    
  }
  return 0;
}

void loop() 
{
  char aCmd[MAX_CMD_LENGTH];
  // put your main code here, to run repeatedly:
  while(1)
  {
    int length = readCommand(aCmd, MAX_CMD_LENGTH);
    if(length > 0)
    {
      processCommand(aCmd, length);
    }
  delay(1000);
  }
}
