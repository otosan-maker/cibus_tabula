
#include "pantalla_lilygo.hpp"




extern producto vProductos[30];
extern int      vProductoSize;
extern int      iPrimerElemento;
extern char     szLocalizacion[25];
extern char     *szgLocalizaciones[];


pantalla_lilygo :: pantalla_lilygo(){
    //Serial.println("pantalla_lilygo ::: Inicializamos \n");
    epd_init(EPD_OPTIONS_DEFAULT);
    hl = epd_hl_init(WAVEFORM);
    epd_set_rotation(orientation);
    framebuffer = epd_hl_get_framebuffer(&hl);


    epd_poweron();
    epd_clear();
    
    epd_poweroff();
}

void pantalla_lilygo::dibuja_fondo(){
    //Serial.println("pantalla_lilygo ::: Dibujamos fondo \n");
    //canvas.fillRect(0,50,540,7,15);
    fillRectangle(0, 50 , 540, 10, 0);
    //canvas.fillRect(0,850,540,7,15);
    fillRectangle(0, 850 , 540, 10, 0);
    //dibuja_flush();
}

void pantalla_lilygo::dibuja_top_apagado(){
    //canvas.fillRect(315,10,24,24,0);
    fillRectangle(315,10,24,24, 255 );
    drawBMP("/img/sleep.bmp",315,10);
}

void pantalla_lilygo::dibuja_top(){
    char strTmp[100];
    //rtc_time_t RTCtime;
    //rtc_date_t RTCDate;
    struct tm myTm;

    //canvas.setTextSize(3);
    //int iVoltaje=M5.getBatteryVoltage();
    int iVoltaje=getVolt();
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
    drawBMP("/img/despierto.bmp",315,10);

    //M5.RTC.getTime(&RTCtime);
    //M5.RTC.getDate(&RTCDate);
    getTimeLilygo(&myTm);
    sprintf(strTmp,"%02d/%02d/%d %d:%02d",myTm.tm_mday ,myTm.tm_mon,myTm.tm_year,myTm.tm_hour,myTm.tm_min );
    write(strTmp, 10, 14);  
}





void pantalla_lilygo::dibuja_cuerpo(){
    char szLocal[32];
    //canvas.fillRect(0,60,560,790,0);
    fillRectangle(0,60,560,790, 255);
    //canvas.setTextSize(4);
    strcpy(szLocal,vProductos[0].m_localizacion);
    szLocal[0]=toupper(szLocal[0]);
    write( szLocal, 150, 65);
    //canvas.fillRect(10,102,500,3,15);
    fillRectangle(10,102,500,3, 0);
    //canvas.setTextSize(3);
    for(int i =iPrimerElemento;(i<20+iPrimerElemento);i++){
        int iLocalizacion = i - iPrimerElemento;
        if(vProductos[i].m_seleccionado)
            drawBMP("/img/radio_button_checked.bmp", 20, 110+iLocalizacion*35);
        else
            drawBMP("/img/radio_button_unchecked.bmp", 20, 110+iLocalizacion*35);
        
        int cursor_x = 50;
        int cursor_y = 110+iLocalizacion*35;
        //canvas.drawString( vProductos[i].m_nombreProducto, 50, 110+iLocalizacion*35);
        write( vProductos[i].m_nombreProducto, cursor_x, cursor_y);
        cursor_x = 340;
        //canvas.drawString( vProductos[i].m_f_alta, 340, 110+iLocalizacion*35);
        write(vProductos[i].m_f_alta, cursor_x, cursor_y);
        //canvas.fillRect(20,140+iLocalizacion*35,500,2,15);
        fillRectangle(20, 140+iLocalizacion*35 , 500, 2, 0);
    }
   
}

void pantalla_lilygo::msg(const char *szText){
    fillRectangle(20, 700 , 500, 80, 255);
    drawRectangle(20, 700 , 500, 80, 255);
    int cursor_x = 25;
    int cursor_y = 720;
    write(szText, cursor_x, cursor_y);
    dibuja_flush( );
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
    Serial.println("Boton 1");
    strcpy(szLocalizacion,szgLocalizaciones[0]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    dibuja_flush( );
}

void pantalla_lilygo::boton2(){
    Serial.println("Boton 2");
    strcpy(szLocalizacion,szgLocalizaciones[1]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    dibuja_flush( );
    
}

void pantalla_lilygo::boton3(){
    Serial.println("Boton 3");
    strcpy(szLocalizacion,szgLocalizaciones[2]);
    loadJson(szLocalizacion);
    dibuja_cuerpo();
    dibuja_flush( );
}
void pantalla_lilygo::boton4(){
    Serial.println("Boton 4");
    InitWifi();
    Consumidos();
    Sincroniza_download(szLocalizacion);
    loadJson(szLocalizacion);
    CloseWifi();
    dibuja_cuerpo();
    dibuja_flush( );
}
//Esta definida en time_func_lilygo.cpp
void apagarLilygo();

void pantalla_lilygo::boton5(){
    Serial.println("Boton 5");
    fillRectangle(315,10,24,24,255);
    drawBMP("/img/sleep.bmp",315,10);
    dibuja_flush( );
    //apagamos();
    apagarLilygo();
}

void pantalla_lilygo::pgUp(){
    Serial.println("pgUp");
    iPrimerElemento+=3;
    if(iPrimerElemento>vProductoSize-19)
        iPrimerElemento=vProductoSize-19;
    Serial.printf("pgUp::cambiamos el primer elemento a  %d\n",iPrimerElemento);
    dibuja_cuerpo();
    dibuja_flush();
    Serial.printf("pgUp::cambiamos el primer elemento a  %d\n",iPrimerElemento);
}

void pantalla_lilygo::pgDown(){
    Serial.println("pgDown");
    iPrimerElemento-=3;
    if(iPrimerElemento<0)
        iPrimerElemento=0;
    Serial.printf("pgDown::cambiamos el primer elemento a  %d\n",iPrimerElemento);
    dibuja_cuerpo();
    dibuja_flush();
    Serial.printf("pgDown::cambiamos el primer elemento a  %d\n",iPrimerElemento);
}


void pantalla_lilygo::botonListado(int iIndicePulsado){
    Serial.println("botonListado");
    if(vProductos[iIndicePulsado].m_seleccionado)
        vProductos[iIndicePulsado].m_seleccionado=false;
    else  
        vProductos[iIndicePulsado].m_seleccionado=true;

    dibuja_cuerpo();
    dibuja_flush();

}

void pantalla_lilygo::drawRectangle(int xRect,int yRect,int wRect,int hRect,int color){
        EpdRect rect = {
        .x = xRect,
        .y = yRect,
        .width = wRect,
        .height = hRect,
    };
    epd_draw_rect(rect, color, framebuffer);
}

void pantalla_lilygo::fillRectangle(int xRect,int yRect,int wRect,int hRect,int color){
        EpdRect rect = {
        .x = xRect,
        .y = yRect,
        .width = wRect,
        .height = hRect,
    };
    epd_fill_rect(rect, color, framebuffer);
}


void pantalla_lilygo::drawBMP(const char *szFile,int x, int y){
    drawBitmap_SD(szFile,  x,  y,framebuffer);
}

#define FONT_Y_SIZE 20

void pantalla_lilygo::write(char * szTexto,int cursor_x, int cursor_y){
    int cX=cursor_x;
    int cY=cursor_y+FONT_Y_SIZE;
    //Serial.printf("Cadena  %d, %d ---  %s\n",cursor_x,cursor_y,szTexto);
    EpdFontProperties font_props = epd_font_properties_default();
    epd_write_string(&FiraSans_12, szTexto , &cX, &cY, framebuffer, &font_props);
}