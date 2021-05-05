#include <Arduino.h>
#include <M5EPD.h>
#include <SPI.h>
#include <SD.h>
#include "pantalla.hpp"



#include "cal_interfaces.h"



M5EPD_Canvas canvas(&M5.EPD);
extern pantalla scrPrincipal;


void setup_M5() {
  M5.begin(true,true,true,true,true);
  M5.EPD.SetRotation(90);
  M5.TP.SetRotation(90);
  M5.EPD.Clear(true);
  M5.RTC.begin();
  canvas.createCanvas(540, 960);
  
  scrPrincipal.set_canvas(&canvas);
}




