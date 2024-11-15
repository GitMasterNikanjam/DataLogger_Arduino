
// ###########################################################################
// Include libraries:

#include "DataLogger.h"

// ###########################################################################
// DataLogger class:

DataLogger::DataLogger()
{
  parameters.SDCARD_CS_PIN = -1;

  _logNum = 1;
}

DataLogger::~DataLogger()
{
  
}

bool DataLogger::init(void)
{
  if (!SD.begin(parameters.SDCARD_CS_PIN))
  {
    errorMessage = "Error DataLogger: SDCard failed, or not present";
    return false;
  }

  return true;
}

bool DataLogger::createHelpFile(String data)
{
  SD.remove("LOG_HELP.txt");
  _file = SD.open("LOG_HELP.txt",FILE_WRITE); 
  if(_file)
  {
    errorMessage = "Error DataLogger: SDCard failed, or not present";
    return false;
  }
  _file.println(data);
  _file.close();
}

bool DataLogger::_createNewLog(void)
{
  if (SD.exists("LAST_LOG_NUMBER.txt"))
  {
    File lastLogNumFile = SD.open("LAST_LOG_NUMBER.txt", FILE_READ);
    String data = lastLogNumFile.readString();
    _logNum = (data.toInt()+1);
    lastLogNumFile.close();
    SD.remove("LAST_LOG_NUMBER.txt");
    lastLogNumFile = SD.open("LAST_LOG_NUMBER.txt", FILE_WRITE);
    lastLogNumFile.println(_logNum);
    lastLogNumFile.close();
  }
  else
  {
    File lastLogNumFile = SD.open("LAST_LOG_NUMBER.txt", FILE_WRITE);
    _logNum = 1;
    lastLogNumFile.println(_logNum);
    lastLogNumFile.close();
  }
}

bool DataLogger::start(void)
{
  _file = SD.open("log_" + String(_logNum) + ".txt", FILE_WRITE);
  _file.close();
}

bool DataLogger::stop(void)
{

}

bool DataLogger::write(String data)
{
  _file = SD.open("LOG_" + String(_logNum) + ".txt", FILE_WRITE);
  _file.println(data);
  _file.close();
}

