#if(SDCARD_ENA == true)

  int init_SD(void)
  {
    if (!SD.begin(SDCARD_CS_PIN))
    {
      return 1;
    }
    else
    {
      SD.remove("log_help.txt");
      LOG_FILE=SD.open("log_help.txt",FILE_WRITE); 
      LOG_FILE.println("Time[ms],Throttle[us],Thrust[kg],Torque[N.m],RPM,Voltage_battery[Volt],Amper_battery[A]");
      LOG_FILE.close();
      return 0;
    }
  }

  // +++++++++++++++++++++++++++++++++++++++++++
  void init_SD_Record(void)
  {
    if (SD.exists("last_log.txt"))
    {
      LOG_FILE=SD.open("last_log.txt",FILE_READ);
      last_log_file_num=LOG_FILE.readString();
      last_log_file_num=(String)(last_log_file_num.toInt()+1);
      LOG_FILE.close();
      SD.remove("last_log.txt");
      LOG_FILE=SD.open("last_log.txt",FILE_WRITE);
      LOG_FILE.print(last_log_file_num);
      LOG_FILE.close();
    }
    else
    {
      last_log_file_num="0";
      LOG_FILE=SD.open("last_log.txt",FILE_WRITE);
      LOG_FILE.print("0");
      LOG_FILE.close();
    }

    LOG_FILE=SD.open("log_"+last_log_file_num+".txt",FILE_WRITE);
    LOG_FILE.print("Temperature: ");LOG_FILE.print(air.temperature);LOG_FILE.print(" Celsius, ");
    LOG_FILE.print("Pressure: ");LOG_FILE.print(air.pressure);LOG_FILE.print(" Pa, ");
    LOG_FILE.print("Density: ");LOG_FILE.print(air.density);LOG_FILE.print(" kg/m^3, ");
    LOG_FILE.print("Altitude[MSL]: ");LOG_FILE.print(air.altitude);LOG_FILE.println(" m");
    LOG_FILE.close();
  }
  // +++++++++++++++++++++++++++++++++++++++++++
  void write_SD(void)
  {
    LOG_FILE=SD.open("log_"+last_log_file_num+".txt",FILE_WRITE);
    LOG_FILE.print(T);LOG_FILE.print(",");
    LOG_FILE.print(RCIN_value);LOG_FILE.print(",");
    LOG_FILE.print((float)thrust/1000.0);LOG_FILE.print(",");
    LOG_FILE.print((float)torque/100.0);LOG_FILE.print(",");
    LOG_FILE.print(rpm);LOG_FILE.print(",");
    LOG_FILE.print((float)voltage_battery/1000.0);LOG_FILE.print(",");
    LOG_FILE.println((float)amper_battery/1000.0);
    LOG_FILE.close();
  }

#endif  // SDCARD_ENA
