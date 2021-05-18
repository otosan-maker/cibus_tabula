#ifndef __PANTALLA_LILYGO__
#define __PANTALLA_LILYGO__


#include "pantalla.hpp"
#include "jsonCom.hpp"
#include "producto.hpp"
#include "cal_interfaces.h"


#define BATT_PIN            36
#define SD_MISO             12
#define SD_MOSI             13
#define SD_SCLK             14
#define SD_CS               15

#define CONFIG_EPD_DISPLAY_TYPE_ED047TC1

#define WAVEFORM EPD_BUILTIN_WAVEFORM

class pantalla_lilygo : public pantalla{

    public:
   

    pantalla_lilygo();
    
    void dibuja_fondo();
    void dibuja_top();
    void dibuja_top_apagado();
    void dibuja_cuerpo();
    void dibuja_menu();
    void dibuja_flush();
    void boton1();
    void boton2();
    void boton3();
    void boton4();
    void boton5();
    void pgUp();
    void pgDown();
    void botonListado(int iIndicePulsado);

    void write(char * szTexto,int x, int y);
    void drawBMP(char *szFile,int x, int y);
    void drawRectangle(int x,int y,int width,int heigth,int color);
};

#endif