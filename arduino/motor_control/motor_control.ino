#define MAX_CMD_LENGTH   128

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Native USB only
  }
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

int processCommand(char* pData, 
                   const int maxLength)
{
  String cmdStr = pData;
  if(cmdStr == "Test")
  {
    Serial.println("CMD: Test");
  }
  else
  {
    Serial.println("CMD: unknown");
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
