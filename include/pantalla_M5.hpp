#ifndef __PANTALLA_M5__
#define __PANTALLA_M5__
#include <M5EPD.h>
#include "pantalla.hpp"
#include "jsonCom.hpp"
#include "producto.hpp"
#include "cal_interfaces.h"


class pantalla_M5 : public pantalla{

    public:
    M5EPD_Canvas canvas;
    pantalla_M5();
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