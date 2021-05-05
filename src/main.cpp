#include <Arduino.h>
#include <M5EPD.h>
#include <SPI.h>
#include <SD.h>
#include "pantalla.hpp"
#include "jsonCom.hpp"


#include "cal_interfaces.h"

extern char     szLocalizacion[25];
extern int wifi_status ;
long unsigned int iLastUpdate=0;

M5EPD_Canvas canvas(&M5.EPD);
pantalla scrPrincipal;



TaskHandle_t thEventHandler;
TaskHandle_t thTouchScreenHandler;
QueueHandle_t qTouchScreenQueue;


void setup() {
  M5.begin(true,true,true,true,true);
  M5.EPD.SetRotation(90);
  M5.TP.SetRotation(90);
  M5.EPD.Clear(true);
  M5.RTC.begin();
  canvas.createCanvas(540, 960);
  

  SPI.begin(14, 13, 12, 4);
  SD.begin(4, SPI, 20000000);
  cargaEstado();
  print_wakeup_reason();

  InitWifi();
  Sincroniza_download(szLocalizacion);
  loadJson(szLocalizacion);
  CloseWifi();

  //Creamos las colas de trabajo
  qTouchScreenQueue = xQueueCreate( 10, sizeof( tp_finger_t ) );
  // arrancamos las tareas
  xTaskCreatePinnedToCore(tskEventHandler, "EventHandler",5000,NULL,1,&thEventHandler,tskNO_AFFINITY );
  xTaskCreatePinnedToCore(tskTouchScreen, "EventHandler",5000,NULL,1,&thTouchScreenHandler,tskNO_AFFINITY );

  
  scrPrincipal.set_canvas(&canvas);
  scrPrincipal.dibuja_fondo();
  scrPrincipal.dibuja_top();
  scrPrincipal.dibuja_cuerpo();
  
  scrPrincipal.dibuja_menu();
  scrPrincipal.dibuja_flush();

  writeBatt2SD();
  iLastUpdate=millis();
}






void loop() {
  
/* 
  Sincroniza_download(szLocalizacion);
  loadJson(szLocalizacion);
  scrPrincipal.dibuja_cuerpo();
 */
  scrPrincipal.dibuja_top();
  scrPrincipal.dibuja_flush();

  UBaseType_t memoria_usada=uxTaskGetStackHighWaterMark(thEventHandler);
  Serial.printf("memoria usada por thEventHandler %d\n",memoria_usada );
  memoria_usada=uxTaskGetStackHighWaterMark(thTouchScreenHandler);
  Serial.printf("memoria usada por thTouchScreenHandler %d\n",memoria_usada );
  
  
  Serial.printf("last update %d\n",int(millis()-iLastUpdate));

   delay(10000);
  if (millis()-iLastUpdate>20000){
    canvas.fillRect(315,10,24,24,0);
    canvas.drawPngFile(SD,"/img/sleep.png",315,10);
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16 );
    apagamos();
  } 
      

}