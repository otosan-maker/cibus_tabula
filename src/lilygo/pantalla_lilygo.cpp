
#include "pantalla_lilygo.hpp"




extern producto vProductos[30];
extern int      vProductoSize;
extern int      iPrimerElemento;
extern char     szLocalizacion[25];
extern char     *szgLocalizaciones[];


pantalla_lilygo :: pantalla_lilygo(){
    epd_init();
    framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer) {
        Serial.println("alloc memory failed !!!");
        while (1);
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

    epd_poweron();
    epd_clear();
    
    epd_poweroff();



    M5.begin(true,true,true,true,true);
    M5.EPD.SetRotation(90);
    M5.TP.SetRotation(90);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    canvas.createCanvas(540, 960);
}

void pantalla_lilygo::dibuja_fondo(){
    canvas.fillRect(0,50,540,7,15);
    canvas.fillRect(0,850,540,7,15);
}

void pantalla_lilygo::dibuja_top_apagado(){
    canvas.fillRect(315,10,24,24,0);
    canvas.drawPngFile(SD,"/img/sleep.png",315,10);
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16 );
}

void pantalla_lilygo::dibuja_top(){
    char strTmp[100];
    rtc_time_t RTCtime;
    rtc_date_t RTCDate;

    canvas.setTextSize(3);
    sprintf(strTmp,"%d",M5.getBatteryVoltage());
    canvas.drawString(strTmp, 360, 14);
    if (M5.getBatteryVoltage()>4250){
         canvas.drawBmpFile(SD,"/img/bateria_4.bmp",450,10);
    }else if (M5.getBatteryVoltage()>4000){
         canvas.drawBmpFile(SD,"/img/bateria_3.bmp",450,10);
    }else if (M5.getBatteryVoltage()>3750){
         canvas.drawBmpFile(SD,"/img/bateria_2.bmp",450,10);
    }else if (M5.getBatteryVoltage()>3400){
         canvas.drawBmpFile(SD,"/img/bateria_1.bmp",450,10);
    }else{
         canvas.drawBmpFile(SD,"/img/bateria_4.bmp",450,10);
    }
    canvas.drawPngFile(SD,"/img/despierto.png",315,10);

    M5.RTC.getTime(&RTCtime);
    M5.RTC.getDate(&RTCDate);
    
    sprintf(strTmp,"%02d/%02d/%d %d:%02d",RTCDate.day,RTCDate.mon,RTCDate.year,RTCtime.hour,RTCtime.min );
    canvas.drawString(strTmp, 10, 14);
    
}

void pantalla_lilygo::set_canvas(M5EPD_Canvas *ppCanvas){
    //pCanvas=ppCanvas;
}



void pantalla_lilygo::dibuja_cuerpo(){
    char szLocal[32];
    canvas.fillRect(0,60,560,790,0);
    canvas.setTextSize(4);
    strcpy(szLocal,vProductos[0].m_localizacion);
    szLocal[0]=toupper(szLocal[0]);
    canvas.drawString( szLocal, 150, 65);
    canvas.fillRect(10,102,500,3,15);
    canvas.setTextSize(3);
    for(int i =iPrimerElemento;(i<20+iPrimerElemento);i++){
        int iLocalizacion = i - iPrimerElemento;
        if(vProductos[i].m_seleccionado)
            canvas.drawPngFile(SD,"/img/radio_button_checked.png", 20, 110+iLocalizacion*35);
        else
            canvas.drawPngFile(SD,"/img/radio_button_unchecked.png", 20, 110+iLocalizacion*35);
        //canvas.drawPngFile(SD,"/img/despierto.png", 20, 110+i*35);
        canvas.drawString( vProductos[i].m_nombreProducto, 50, 110+iLocalizacion*35);
        canvas.drawString( vProductos[i].m_f_alta, 340, 110+iLocalizacion*35);
        canvas.fillRect(20,140+iLocalizacion*35,500,2,15);
    }
   
}



void pantalla_lilygo::dibuja_menu(){
    char szFile[128];
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[0]);
    canvas.drawBmpFile(SD,szFile,20,861);
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[1]);
    canvas.drawBmpFile(SD,szFile,120,861);
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[2]);
    canvas.drawBmpFile(SD,szFile,220,861);
    canvas.drawBmpFile(SD,"/img/descarga.bmp",320,861);
    canvas.drawBmpFile(SD,"/img/apagar.bmp",420,861);
}


void pantalla_lilygo::dibuja_flush(){
    canvas.pushCanvas(0,0,UPDATE_MODE_DU4);
}



void pantalla_lilygo::boton1(){
    strcpy(szLocalizacion,szgLocalizaciones[0]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16    );
}
void pantalla_lilygo::boton2(){
    strcpy(szLocalizacion,szgLocalizaciones[1]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16    );
    
}

void pantalla_lilygo::boton3(){
    strcpy(szLocalizacion,szgLocalizaciones[2]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16    );

}
void pantalla_lilygo::boton4(){
    InitWifi();
    Consumidos();
    Sincroniza_download(szLocalizacion);
    loadJson(szLocalizacion);
    CloseWifi();
    dibuja_cuerpo();
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16    );
}
void pantalla_lilygo::boton5(){
    //canvas.drawPngFile(SD,"/img/despierto.png",315,10);
    canvas.fillRect(315,10,24,24,0);
    canvas.drawPngFile(SD,"/img/sleep.png",315,10);
    canvas.pushCanvas(0,0,UPDATE_MODE_GC16 );
    apagamos();
}

void pantalla_lilygo::pgUp(){
    iPrimerElemento+=3;
    if(iPrimerElemento>vProductoSize-19)
        iPrimerElemento=vProductoSize-19;
    Serial.printf("pgUp::cambiamos el primer elemento a  %d\n",iPrimerElemento);
    dibuja_cuerpo();
    dibuja_flush();
    Serial.printf("pgUp::cambiamos el primer elemento a  %d\n",iPrimerElemento);
}

void pantalla_lilygo::pgDown(){
    iPrimerElemento-=3;
    if(iPrimerElemento<0)
        iPrimerElemento=0;
    Serial.printf("pgDown::cambiamos el primer elemento a  %d\n",iPrimerElemento);
    dibuja_cuerpo();
    dibuja_flush();
    Serial.printf("pgDown::cambiamos el primer elemento a  %d\n",iPrimerElemento);
}


void pantalla_lilygo::botonListado(int iIndicePulsado){
    if(vProductos[iIndicePulsado].m_seleccionado)
        vProductos[iIndicePulsado].m_seleccionado=false;
    else  
        vProductos[iIndicePulsado].m_seleccionado=true;

    dibuja_cuerpo();
    dibuja_flush();

}