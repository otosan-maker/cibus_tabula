#include "cal_interfaces.h"
#include "pantalla.hpp"
#include "jsonCom.hpp"
#include "producto.hpp"



extern producto vProductos[30];
extern int      vProductoSize;
extern int      iPrimerElemento;
extern char     szLocalizacion[25];
extern char     *szgLocalizaciones[];

void pantalla::dibuja_fondo(){
    Serial.println("pantalla ::: Dibujamos fondo \n");
    drawRectangle(0, 50 , 540, 7, 255);
    drawRectangle(0, 850 , 540, 7, 255);
    dibuja_flush();
}

void pantalla::dibuja_top_apagado(){
   
}

void pantalla::dibuja_top(){
    
    
}





void pantalla::dibuja_cuerpo(){
  
}



void pantalla::dibuja_menu(){
 
}


void pantalla::dibuja_flush(){
    
}



void pantalla::boton1(){
    
}
void pantalla::boton2(){
    
    
}

void pantalla::boton3(){
    

}
void pantalla::boton4(){
    
}
void pantalla::boton5(){
  
}

void pantalla::pgUp(){
   
}

void pantalla::pgDown(){
    
}


void pantalla::botonListado(int iIndicePulsado){
    
}

void pantalla::write(char * szTexto,int x, int y){

}
void pantalla::drawBMP(char *szFile,int x, int y){

}
void pantalla::drawRectangle(int x,int y,int width,int heigth,int color){

}