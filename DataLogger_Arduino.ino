#include "DataLogger.h"

DataLogger logger;

void setup() {
  // put your setup code here, to run once:
logger.parameters.SDCARD_CS_PIN = 10;
logger.init();

logger.createHelpFile("data1, data2, data3");
logger.start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
