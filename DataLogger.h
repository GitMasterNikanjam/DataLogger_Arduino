#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

// #################################################################################
// Include libraries:

#include <Arduino.h>
#include <SD.h>                       // Arduino Library for FAT12/FAT16/FAT32. https://github.com/adafruit/SdFat

// #################################################################################

/**
  @class DataLogger
  @brief The class for manage data logging.
*/
class DataLogger
{
  public:

    /// @brief Last error accured for object.
    String errorMessage;

    /**
      @struct ParametersStructure
      @brief Parameters structure
    */
    struct ParametersStructure
    {
      /// @brief The GPIO pin number for spi chip select of SD card.
      int8_t SDCARD_CS_PIN;

      /**
        @brief The data log frequency. [Hz]
      */
      uint16_t LOG_FRQ;

    }parameters;

    /// @brief Default constructor. Init some variables or parameters.
    DataLogger();

    /// @brief Destructor.
    ~DataLogger();

    /**
      @brief Init object. Check parameters. 
    */
    bool init(void);

    /**
      @brief
    */
    bool start(void);

    /**
      @brief
    */
    bool stop(void);

    /**
      @brief
    */
    bool write(String data);

    /**
      @brief Create a help file and write data in it.
    */
    bool createHelpFile(String data);

  private:

    /**
      @brief The Time at update Log file data on sd card. [ms]
    */
    uint32_t _T;

    /**
      @brief Current file that recording data on SDcard.
    */
    File _file;                                  

    /// @brief Current log number that recording data on SDcard.
    uint32_t _logNum;

    /**
      @brief The flag for state of recording mode of data logging.
    */
    bool _loggingFlag;

    /**
      @brief Check parameters validation.
      @return true if succeeded.
    */
    bool _checkParameters(void);

    /**
      @brief Create a new log file with new log number. change _logNum value.
    */
    bool _updateLogNum(void);
};


#endif