#include <Arduino.h>
#include <M5EPD.h>
#include <SD.h>
#include "cal_interfaces.h"

void writeBatt2SD(){
  char strTmp[100];
  rtc_time_t RTCtime;
  rtc_date_t RTCDate;
  
  M5.RTC.getTime(&RTCtime);
  M5.RTC.getDate(&RTCDate);
  sprintf(strTmp,"%d/%02d/%d %d:%02d",RTCDate.day,RTCDate.mon,RTCDate.year,RTCtime.hour,RTCtime.min );
  
  File myFile;
  myFile = SD.open("/bateria.txt", "a");

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to bateria.txt...");
    myFile.printf("%s.- Nivel de bateria %d.\n", strTmp ,M5.getBatteryVoltage());
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
  myFile = SD.open("/consumidos.txt", "a");
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
  myFile = SD.open("/mensajes.txt", "a");
  if (myFile) {
    myFile.printf("%s.- %s.\n", strTmp ,szMsg);
    myFile.close();
  }
  Serial.printf("msg2BatteryLog ::: %s.- %s.\n", strTmp ,szMsg);
}