#include <M5EPD.h>


class pantalla{
    M5EPD_Canvas *pCanvas=NULL;

    public:
    
    void set_canvas(M5EPD_Canvas *ppCanvas);
    void dibuja_fondo();
    void dibuja_top();
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