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
    pCanvas->fillRect(0,50,540,7,15);
    pCanvas->fillRect(0,850,540,7,15);
}

void pantalla::dibuja_top_apagado(){
    pCanvas->fillRect(315,10,24,24,0);
    pCanvas->drawPngFile(SD,"/img/sleep.png",315,10);
    pCanvas->pushCanvas(0,0,UPDATE_MODE_GC16 );
}

void pantalla::dibuja_top(){
    char strTmp[100];
    rtc_time_t RTCtime;
    rtc_date_t RTCDate;

    pCanvas->setTextSize(3);
    sprintf(strTmp,"%d",M5.getBatteryVoltage());
    pCanvas->drawString(strTmp, 360, 14);
    if (M5.getBatteryVoltage()>4250){
         pCanvas->drawBmpFile(SD,"/img/bateria_4.bmp",450,10);
    }else if (M5.getBatteryVoltage()>4000){
         pCanvas->drawBmpFile(SD,"/img/bateria_3.bmp",450,10);
    }else if (M5.getBatteryVoltage()>3750){
         pCanvas->drawBmpFile(SD,"/img/bateria_2.bmp",450,10);
    }else if (M5.getBatteryVoltage()>3400){
         pCanvas->drawBmpFile(SD,"/img/bateria_1.bmp",450,10);
    }else{
         pCanvas->drawBmpFile(SD,"/img/bateria_4.bmp",450,10);
    }
    pCanvas->drawPngFile(SD,"/img/despierto.png",315,10);

    M5.RTC.getTime(&RTCtime);
    M5.RTC.getDate(&RTCDate);
    
    sprintf(strTmp,"%02d/%02d/%d %d:%02d",RTCDate.day,RTCDate.mon,RTCDate.year,RTCtime.hour,RTCtime.min );
    pCanvas->drawString(strTmp, 10, 14);
    
}

void pantalla::set_canvas(M5EPD_Canvas *ppCanvas){
    pCanvas=ppCanvas;
}



void pantalla::dibuja_cuerpo(){
    char szLocal[32];
    pCanvas->fillRect(0,60,560,790,0);
    pCanvas->setTextSize(4);
    strcpy(szLocal,vProductos[0].m_localizacion);
    szLocal[0]=toupper(szLocal[0]);
    pCanvas->drawString( szLocal, 150, 65);
    pCanvas->fillRect(10,102,500,3,15);
    pCanvas->setTextSize(3);
    for(int i =iPrimerElemento;(i<20+iPrimerElemento);i++){
        int iLocalizacion = i - iPrimerElemento;
        if(vProductos[i].m_seleccionado)
            pCanvas->drawPngFile(SD,"/img/radio_button_checked.png", 20, 110+iLocalizacion*35);
        else
            pCanvas->drawPngFile(SD,"/img/radio_button_unchecked.png", 20, 110+iLocalizacion*35);
        //pCanvas->drawPngFile(SD,"/img/despierto.png", 20, 110+i*35);
        pCanvas->drawString( vProductos[i].m_nombreProducto, 50, 110+iLocalizacion*35);
        pCanvas->drawString( vProductos[i].m_f_alta, 340, 110+iLocalizacion*35);
        pCanvas->fillRect(20,140+iLocalizacion*35,500,2,15);
    }
   
}



void pantalla::dibuja_menu(){
    char szFile[128];
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[0]);
    pCanvas->drawBmpFile(SD,szFile,20,861);
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[1]);
    pCanvas->drawBmpFile(SD,szFile,120,861);
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[2]);
    pCanvas->drawBmpFile(SD,szFile,220,861);
    pCanvas->drawBmpFile(SD,"/img/descarga.bmp",320,861);
    pCanvas->drawBmpFile(SD,"/img/apagar.bmp",420,861);
}


void pantalla::dibuja_flush(){
    pCanvas->pushCanvas(0,0,UPDATE_MODE_DU4);
}



void pantalla::boton1(){
    strcpy(szLocalizacion,szgLocalizaciones[0]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    pCanvas->pushCanvas(0,0,UPDATE_MODE_GC16    );
}
void pantalla::boton2(){
    strcpy(szLocalizacion,szgLocalizaciones[1]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    pCanvas->pushCanvas(0,0,UPDATE_MODE_GC16    );
    
}

void pantalla::boton3(){
    strcpy(szLocalizacion,szgLocalizaciones[2]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    pCanvas->pushCanvas(0,0,UPDATE_MODE_GC16    );

}
void pantalla::boton4(){
    InitWifi();
    Consumidos();
    Sincroniza_download(szLocalizacion);
    loadJson(szLocalizacion);
    CloseWifi();
    dibuja_cuerpo();
    pCanvas->pushCanvas(0,0,UPDATE_MODE_GC16    );
}
void pantalla::boton5(){
    //pCanvas->drawPngFile(SD,"/img/despierto.png",315,10);
    pCanvas->fillRect(315,10,24,24,0);
    pCanvas->drawPngFile(SD,"/img/sleep.png",315,10);
    pCanvas->pushCanvas(0,0,UPDATE_MODE_GC16 );
    apagamos();
}

void pantalla::pgUp(){
    iPrimerElemento+=3;
    if(iPrimerElemento>vProductoSize-19)
        iPrimerElemento=vProductoSize-19;
    Serial.printf("pgUp::cambiamos el primer elemento a  %d\n",iPrimerElemento);
    dibuja_cuerpo();
    dibuja_flush();
    Serial.printf("pgUp::cambiamos el primer elemento a  %d\n",iPrimerElemento);
}

void pantalla::pgDown(){
    iPrimerElemento-=3;
    if(iPrimerElemento<0)
        iPrimerElemento=0;
    Serial.printf("pgDown::cambiamos el primer elemento a  %d\n",iPrimerElemento);
    dibuja_cuerpo();
    dibuja_flush();
    Serial.printf("pgDown::cambiamos el primer elemento a  %d\n",iPrimerElemento);
}


void pantalla::botonListado(int iIndicePulsado){
    if(vProductos[iIndicePulsado].m_seleccionado)
        vProductos[iIndicePulsado].m_seleccionado=false;
    else  
        vProductos[iIndicePulsado].m_seleccionado=true;

    dibuja_cuerpo();
    dibuja_flush();

}