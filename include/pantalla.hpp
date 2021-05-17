#ifndef __PANTALLA__
#define __PANTALLA__


class pantalla{
    
    public:
    
    
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