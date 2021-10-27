extern "C" 
{ 
#include "src/cli.h"
#include "src/tools.h"
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
  TOOL_setPrintCommand(serialPrint);
  TOOL_setAnalogWriteFunction(analogWrite);
  TOOL_setDigitalWriteFunction(digitalWrite);
  TOOL_setDigitalReadFunction(digitalRead);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  MOTOR_config(0, 2, 3, 4, 5, 11);
  attachInterrupt(digitalPinToInterrupt(2), MOTOR_updatePosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), MOTOR_updatePosition, CHANGE);
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
  char aCmd[MAX_CMD_LENGTH];
  // put your main code here, to run repeatedly:
  while(1)
  {
    int length = readCommand(aCmd, MAX_CMD_LENGTH);
    if(length > 0)
    {
      CLI_process(aCmd);
    }
    delay(10);
  }
}
