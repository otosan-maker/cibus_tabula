#ifndef __PANTALLA_LILYGO__
#define __PANTALLA_LILYGO__
#include "epd_driver.h"
#include "pantalla.hpp"
#include "jsonCom.hpp"
#include "producto.hpp"
#include "cal_interfaces.h"


#define BATT_PIN            36
#define SD_MISO             12
#define SD_MOSI             13
#define SD_SCLK             14
#define SD_CS               15


class pantalla_lilygo : public pantalla{

    public:
    M5EPD_Canvas canvas;
    uint8_t *framebuffer;

    pantalla_lilygo();
    void set_canvas(M5EPD_Canvas *ppCanvas);
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
};

#endif