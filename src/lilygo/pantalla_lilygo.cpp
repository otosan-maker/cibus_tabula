
#include "pantalla_lilygo.hpp"




extern producto vProductos[30];
extern int      vProductoSize;
extern int      iPrimerElemento;
extern char     szLocalizacion[25];
extern char     *szgLocalizaciones[];


pantalla_lilygo :: pantalla_lilygo(){
    epd_init(EPD_OPTIONS_DEFAULT);
    hl = epd_hl_init(WAVEFORM);
    epd_set_rotation(orientation);
    framebuffer = epd_hl_get_framebuffer(&hl);


    epd_poweron();
    epd_clear();
    
    epd_poweroff();
}

void pantalla_lilygo::dibuja_fondo(){
    //canvas.fillRect(0,50,540,7,15);
    drawRectangle(0, 50 , 540, 7, 255);
    //canvas.fillRect(0,850,540,7,15);
    drawRectangle(0, 850 , 540, 7, 255);
}

void pantalla_lilygo::dibuja_top_apagado(){
    //canvas.fillRect(315,10,24,24,0);
    drawRectangle(315,10,24,24, 0 );
    drawBMP("/img/sleep.png",315,10);
}

void pantalla_lilygo::dibuja_top(){
    char strTmp[100];
    //rtc_time_t RTCtime;
    //rtc_date_t RTCDate;
    struct tm myTm;

    //canvas.setTextSize(3);
    //int iVoltaje=M5.getBatteryVoltage();
    int iVoltaje=4001;
    sprintf(strTmp,"%d",iVoltaje);
    write(strTmp, 360, 14);
    if (iVoltaje>4250){
         drawBMP("/img/bateria_4.bmp",450,10);
    }else if (iVoltaje>4000){
         drawBMP("/img/bateria_3.bmp",450,10);
    }else if (iVoltaje>3750){
         drawBMP("/img/bateria_2.bmp",450,10);
    }else if (iVoltaje>3400){
         drawBMP("/img/bateria_1.bmp",450,10);
    }else{
         drawBMP("/img/bateria_4.bmp",450,10);
    }
    drawBMP("/img/despierto.png",315,10);

    //M5.RTC.getTime(&RTCtime);
    //M5.RTC.getDate(&RTCDate);
    getTimeLilygo(&myTm);
    sprintf(strTmp,"%02d/%02d/%d %d:%02d",myTm.tm_mday ,myTm.tm_mon,myTm.tm_year,myTm.tm_hour,myTm.tm_min );
    write(strTmp, 10, 14);  
}





void pantalla_lilygo::dibuja_cuerpo(){
    char szLocal[32];
    //canvas.fillRect(0,60,560,790,0);
    drawRectangle(0,60,560,790, 0);
    //canvas.setTextSize(4);
    strcpy(szLocal,vProductos[0].m_localizacion);
    szLocal[0]=toupper(szLocal[0]);
    write( szLocal, 150, 65);
    //canvas.fillRect(10,102,500,3,15);
    drawRectangle(10,102,500,3, 255);
    //canvas.setTextSize(3);
    for(int i =iPrimerElemento;(i<20+iPrimerElemento);i++){
        int iLocalizacion = i - iPrimerElemento;
        if(vProductos[i].m_seleccionado)
            drawBMP("/img/radio_button_checked.png", 20, 110+iLocalizacion*35);
        else
            drawBMP("/img/radio_button_unchecked.png", 20, 110+iLocalizacion*35);
        //canvas.drawPngFile(SD,"/img/despierto.png", 20, 110+i*35);
        
        int cursor_x = 50;
        int cursor_y = 110+iLocalizacion*35;
        //canvas.drawString( vProductos[i].m_nombreProducto, 50, 110+iLocalizacion*35);
        write( vProductos[i].m_nombreProducto, cursor_x, cursor_y);
        cursor_x = 340;
        //canvas.drawString( vProductos[i].m_f_alta, 340, 110+iLocalizacion*35);
        write(vProductos[i].m_f_alta, cursor_x, cursor_y);
        //canvas.fillRect(20,140+iLocalizacion*35,500,2,15);
        drawRectangle(20, 140+iLocalizacion*35 , 35, 500, 255);
    }
   
}



void pantalla_lilygo::dibuja_menu(){
    char szFile[128];
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[0]);
    drawBMP(szFile,20,861);
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[1]);
    drawBMP(szFile,120,861);
    sprintf(szFile,"/img/%s.bmp",szgLocalizaciones[2]);
    drawBMP(szFile,220,861);
    drawBMP("/img/descarga.bmp",320,861);
    drawBMP("/img/apagar.bmp",420,861);
}


void pantalla_lilygo::dibuja_flush(){
    epd_poweron();
    epd_hl_update_screen(&hl, MODE_GC16, temperature);
    
    epd_poweroff();
}



void pantalla_lilygo::boton1(){
    strcpy(szLocalizacion,szgLocalizaciones[0]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    dibuja_flush( );
}
void pantalla_lilygo::boton2(){
    strcpy(szLocalizacion,szgLocalizaciones[1]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    dibuja_flush( );
    
}

void pantalla_lilygo::boton3(){
    strcpy(szLocalizacion,szgLocalizaciones[2]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    dibuja_flush( );
}
void pantalla_lilygo::boton4(){
    InitWifi();
    Consumidos();
    Sincroniza_download(szLocalizacion);
    loadJson(szLocalizacion);
    CloseWifi();
    dibuja_cuerpo();
    dibuja_flush( );
}
void pantalla_lilygo::boton5(){
    //canvas.drawPngFile(SD,"/img/despierto.png",315,10);
    drawRectangle(315,10,24,24,0);
    drawBMP("/img/sleep.png",315,10);
    dibuja_flush( );
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

void pantalla_lilygo::drawRectangle(int x,int y,int width,int heigth,int color){

}


void pantalla_lilygo::drawBMP(char *szFile,int x, int y){

}

void pantalla_lilygo::write(char * szTexto,int x, int y){

}