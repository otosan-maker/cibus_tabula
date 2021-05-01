#include <M5EPD.h>
#include "producto.hpp"
#include "cal_interfaces.h"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  600        /* Time ESP32 will go to sleep (in seconds) */

extern producto vProductos[30];
extern int      vProductoSize;
extern int      iPrimerElemento;
extern char     szLocalizacion[25];
extern char     *szgLocalizaciones[];


void cargaEstado(){
  
  File fEstado = SD.open("/configuracion/estado.txt","r");
  String strTmp;
  
  Serial.println("cargamos el estado");
  strTmp=fEstado.readStringUntil('\n');
  Serial.printf("leemos el primer elemento %s\n",strTmp.c_str());
  if(strTmp!="")
    iPrimerElemento=atoi(strTmp.c_str());
  else  
    iPrimerElemento=0;

  strTmp=fEstado.readStringUntil('\n');
  Serial.printf("leemos la localizacion %s\n",strTmp.c_str());
  if(strTmp!="")
    strcpy(szLocalizacion,strTmp.c_str()); 
  else  
    strcpy(szLocalizacion,szgLocalizaciones[0]); 
  
  fEstado.close();
}
void guardaEstado(){
  Serial.println("Guardamos el estado");
  File fEstado = SD.open("/configuracion/estado.txt","w");
  fEstado.printf("%d\n",iPrimerElemento);
  fEstado.printf("%s\n",szLocalizacion);
  fEstado.close();
}


void apagamos(){
  rtc_time_t RTCtime;
  M5.RTC.getTime(&RTCtime);
  
  guardaEstado();
  writeBatt2SD();
  if ((RTCtime.hour>22) || (RTCtime.hour<6) ){
    Serial.printf("shutdown gordo!");
    msg2BatteryLog("apagado largo"+RTCtime.hour);
    delay(500);
    M5.shutdown(18000);

  }else{
    Serial.printf("shutdown pequeño");
    msg2BatteryLog("apagado pequeño"+RTCtime.hour);
    delay(500);
    M5.shutdown(3600); 
  }
    
  Serial.printf("DeepSleep ");
  msg2BatteryLog("deep sleep");
  delay(500);
  // esp_sleep_enable_ext0_wakeup((gpio_num_t )BUTTON_1, LOW);
  esp_sleep_enable_ext1_wakeup(((uint64_t)(((uint64_t)1) << 37)), ESP_EXT1_WAKEUP_ALL_LOW);
  //esp_deep_sleep_start(uS_TO_S_FACTOR*TIME_TO_SLEEP);

  ESP.deepSleep(uS_TO_S_FACTOR*TIME_TO_SLEEP); 
  Serial.printf("DeepSleep NO");
  msg2BatteryLog("NO hemos entrado en deep sleep");
}

void print_wakeup_reason(){
	esp_sleep_wakeup_cause_t wakeup_reason;
	wakeup_reason = esp_sleep_get_wakeup_cause();
	switch(wakeup_reason)
	{
		case 1  : msg2BatteryLog("Wakeup caused by external signal using RTC_IO"); break;
		case 2  : msg2BatteryLog("Wakeup caused by external signal using RTC_CNTL"); break;
		case 3  : msg2BatteryLog("Wakeup caused by timer"); break;
		case 4  : msg2BatteryLog("Wakeup caused by touchpad"); break;
		case 5  : msg2BatteryLog("Wakeup caused by ULP program"); break;
		default : msg2BatteryLog("Wakeup was not caused by deep sleep"); break;
	}
}