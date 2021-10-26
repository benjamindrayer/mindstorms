extern "C" 
{ 
#include "src/cli.h"
}
#define WWW 1
#define MAX_CMD_LENGTH   128


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

void serialPrint(const char* pData)
{
  while(*pData)
  {
    Serial.print(*pData);
    pData++;
  }
}

void loop() 
{
  CLI_setPrintFunction(serialPrint);
  char aCmd[MAX_CMD_LENGTH];
  // put your main code here, to run repeatedly:
  while(1)
  {
    int length = readCommand(aCmd, MAX_CMD_LENGTH);
    if(length > 0)
    {
      CLI_process(aCmd);
    }
    delay(1000);
  }
}
