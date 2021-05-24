#include <Arduino.h>
#include <M5EPD.h>
#include <SD.h>
#include <SPIFFS.h>
#include "cal_interfaces.h"

void writeBatt2SD(){
  char strTmp[100];
  int iVoltaje=0;
  
  File myFile;
#ifdef CONFIG__M5_PAPER__
  rtc_time_t RTCtime;
  rtc_date_t RTCDate;
  
  M5.RTC.getTime(&RTCtime);
  M5.RTC.getDate(&RTCDate);
  sprintf(strTmp,"%d/%02d/%d %d:%02d",RTCDate.day,RTCDate.mon,RTCDate.year,RTCtime.hour,RTCtime.min );
  iVoltaje=M5.getBatteryVoltage();
  myFile = SD.open("/bateria.txt", "a");
#else
  struct tm myTm;
  getTimeLilygo(&myTm);
  sprintf(strTmp,"%d/%02d/%d %d:%02d",myTm.tm_yday ,myTm.tm_mon,myTm.tm_year,myTm.tm_hour,myTm.tm_min );
  iVoltaje=getVolt();
  myFile = SPIFFS.open("/bateria.txt", "a");
#endif
 

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to bateria.txt...");
    myFile.printf("%s.- Nivel de bateria %d.\n", strTmp ,iVoltaje);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening bateria.txt");
  }
}


void consumido2SD(const char* szURL){
  char strTmp[100];
  rtc_time_t RTCtime;
  rtc_date_t RTCDate;
  M5.RTC.getTime(&RTCtime);
  M5.RTC.getDate(&RTCDate);
  sprintf(strTmp,"%d/%02d/%d %d:%02d",RTCDate.day,RTCDate.mon,RTCDate.year,RTCtime.hour,RTCtime.min );
  
  File myFile;
#ifdef CONFIG__M5_PAPER__
  myFile = SD.open("/consumidos.txt", "a");
#else
  myFile = SPIFFS.open("/consumidos.txt", "a");
#endif
  if (myFile) {
    myFile.printf("%s.- Consumo %s.\n", strTmp ,szURL);
    myFile.close();
  }

}


void msg2BatteryLog(const char* szMsg){
  char strTmp[100];
  rtc_time_t RTCtime;
  rtc_date_t RTCDate;
  M5.RTC.getTime(&RTCtime);
  M5.RTC.getDate(&RTCDate);
  sprintf(strTmp,"%d/%02d/%d %d:%02d",RTCDate.day,RTCDate.mon,RTCDate.year,RTCtime.hour,RTCtime.min );
  
  File myFile;
#ifdef CONFIG__M5_PAPER__
  myFile = SD.open("/mensajes.txt", "a");
#else
  myFile = SPIFFS.open("/mensajes.txt", "a");
#endif


  if (myFile) {
    myFile.printf("%s.- %s.\n", strTmp ,szMsg);
    myFile.close();
  }
  Serial.printf("msg2BatteryLog ::: %s.- %s.\n", strTmp ,szMsg);
}