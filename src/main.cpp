#include <Arduino.h>
#include <SPI.h>

#include "pantalla.hpp"
#include "pantalla_M5.hpp"
#include "pantalla_lilygo.hpp"
#include "jsonCom.hpp"
#include "cal_interfaces.h"



pantalla *pScrPrincipal= NULL;



extern char     szLocalizacion[25];
extern int wifi_status ;
long unsigned int iLastUpdate=0;





TaskHandle_t thEventHandler;
TaskHandle_t thTouchScreenHandler;
QueueHandle_t qTouchScreenQueue;


void setup() {
  File fEstado;

  Serial.begin(115200);
  Serial.println("Inicializamos  1");
  delay(60);
#ifdef CONFIG__M5_PAPER__
  pScrPrincipal = new  pantalla_M5();
  SPI.begin(14, 13, 12, 4);
  SD.begin(4, SPI, 20000000);
  fEstado = SD.open(FILE_LAST_STATE,"r");
  cargaEstado(fEstado);
  fEstado.close();
#else
  Serial.printf("Inicializamos 2 %d\n",millis());
   if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        delay(20);
  }
  pScrPrincipal = new  pantalla_lilygo();
  Serial.printf("Inicializamos  3 %d\n",millis());
  fEstado = SPIFFS.open(FILE_LAST_STATE,"r");
  cargaEstado(fEstado);
  Serial.printf("Inicializamos  4 %d\n",millis());
  fEstado.close();
#endif

  

  print_wakeup_reason();
  Serial.printf("Inicializamos  %d\n",millis());
  InitWifi();
  Sincroniza_download(szLocalizacion);
  loadJson(szLocalizacion);
  CloseWifi();
  Serial.printf("Inicializamos  %d\n",millis());
  //Creamos las colas de trabajo
  qTouchScreenQueue = xQueueCreate( 10, sizeof( tp_finger_t ) );
  // arrancamos las tareas
  xTaskCreatePinnedToCore(tskEventHandler, "EventHandler",5000,NULL,1,&thEventHandler,tskNO_AFFINITY );
  xTaskCreatePinnedToCore(tskTouchScreen, "EventHandler",5000,NULL,1,&thTouchScreenHandler,tskNO_AFFINITY );

  
 
  pScrPrincipal->dibuja_fondo();
  pScrPrincipal->dibuja_top();
  pScrPrincipal->dibuja_cuerpo();
  
  pScrPrincipal->dibuja_menu();
  pScrPrincipal->dibuja_flush();

  writeBatt2SD();
  iLastUpdate=millis();
}






void loop() {
  
/* 
  Sincroniza_download(szLocalizacion);
  loadJson(szLocalizacion);
  scrPrincipal.dibuja_cuerpo();
 */
  pScrPrincipal->dibuja_top();
  pScrPrincipal->dibuja_flush();

  UBaseType_t memoria_usada=uxTaskGetStackHighWaterMark(thEventHandler);
  Serial.printf("memoria usada por thEventHandler %d\n",memoria_usada );
  memoria_usada=uxTaskGetStackHighWaterMark(thTouchScreenHandler);
  Serial.printf("memoria usada por thTouchScreenHandler %d\n",memoria_usada );
  
  
  Serial.printf("last update %d\n",int(millis()-iLastUpdate));

   delay(10000);
  if (millis()-iLastUpdate>20000){
    pScrPrincipal->dibuja_top_apagado();
    apagamos();
  } 
      

}