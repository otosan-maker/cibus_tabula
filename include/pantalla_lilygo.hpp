#ifndef __PANTALLA_LILYGO__
#define __PANTALLA_LILYGO__

#include "epd_driver.h"
#include "epd_highlevel.h"
#include "Firasans/Firasans.h"
#include "readbmp.hpp"
#include "pantalla.hpp"
#include "jsonCom.hpp"
#include "producto.hpp"
#include "cal_interfaces.h"


#define BATT_PIN            36
#define SD_MISO             12
#define SD_MOSI             13
#define SD_SCLK             14
#define SD_CS               15

#define WAVEFORM EPD_BUILTIN_WAVEFORM

class pantalla_lilygo : public pantalla{

    public:
    EpdiyHighlevelState hl;
    EpdRotation orientation = EPD_ROT_PORTRAIT;
    uint8_t *framebuffer;
    int temperature = 20;

    pantalla_lilygo();
    
    void dibuja_fondo();
    void dibuja_top();
    void dibuja_top_apagado();
    void dibuja_cuerpo();
    void dibuja_menu();
    void dibuja_flush();
    void msg(const char *szText);
    void boton1();
    void boton2();
    void boton3();
    void boton4();
    void boton5();
    void pgUp();
    void pgDown();
    void botonListado(int iIndicePulsado);

    void write(char * szTexto,int x, int y);
    void drawBMP(const char *szFile,int x, int y);
    void drawRectangle(int x,int y,int width,int heigth,int color);
    void fillRectangle(int x,int y,int width,int heigth,int color);
};

#endif