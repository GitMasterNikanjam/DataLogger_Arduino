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

bool DataLogger::_updateLogNum(void)
{
  if (SD.exists("LAST_LOG_NUMBER.txt"))
  {
    File lastLogNumFile = SD.open("LAST_LOG_NUMBER.txt", FILE_READ);

    if(!lastLogNumFile)
    {
      return false;
    }

    String data = lastLogNumFile.readString();
    _logNum = data.toInt();
    
    if(_logNum == 0)
    {
      errorMessage = "Error DataLogger: The data on LAST_LOG_NUMBER is not valid.";
      return false;
    }

    _logNum += 1;
    lastLogNumFile.close();
  }
  else
  {
    File lastLogNumFile = SD.open("LAST_LOG_NUMBER.txt", FILE_WRITE);

    if(!lastLogNumFile)
    {
      return false;
    }

    _logNum = 1;
    lastLogNumFile.println(_logNum);
    lastLogNumFile.close();
  }

  return true;
}

bool DataLogger::start(void)
{
  if(_loggingFlag == false)
  {
    if(!_updateLogNum())
    {
      return false;;
    }

    _file = SD.open("LOG_" + String(_logNum) + ".txt", FILE_WRITE);

    if(!_file)
    {
      return false;
    }
  }
  _loggingFlag = true;
}

bool DataLogger::stop(void)
{
  if(_loggingFlag == true)
  {
    _loggingFlag = false;
    SD.remove("LAST_LOG_NUMBER.txt");
    File lastLogNumFile = SD.open("LAST_LOG_NUMBER.txt", FILE_WRITE);

    if(!lastLogNumFile)
    {
      return false;
    }

    lastLogNumFile.println(_logNum);
    lastLogNumFile.close();
  }
  
  _file.close();

  return true;
}

bool DataLogger::write(String data)
{
  uint32_t t = millis();

  if(_loggingFlag == false)
  {
    errorMessage = "Error DataLogger: Can not write data log beacause logger is not started.";
    return false;
  }

  if(!_file)
  {
    errorMessage = "Error DataLogger: The log file is not opend.";
    return false;
  }

  if(parameters.LOG_FRQ > 0)
  {
    if((float)(t - _T) < 1000.0/parameters.LOG_FRQ)
    {
      return true;
    }
  }
  
  _file.println(data);
  _file.flush();
  _T = t;
  return true;
}

