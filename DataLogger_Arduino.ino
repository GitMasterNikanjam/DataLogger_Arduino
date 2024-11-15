#include "DataLogger.h"

DataLogger logger;

void setup() {

  Serial.begin(115200);

  logger.parameters.SDCARD_CS_PIN = 10;
  logger.parameters.LOG_FRQ = 100;

  if(!logger.init())
  {
    Serial.println(logger.errorMessage);
  }

  logger.createHelpFile("data1, data2, data3");
  logger.start();
}

void loop() {

  uint32_t T = millis();

  if(T >= 5000)
  {
    logger.stop();
  }

  String data = String(T) + String(sin(T/1000.0), 2) + String(cos(T/1000.0), 2); 
  logger.write(data);

  delay(2);
}
