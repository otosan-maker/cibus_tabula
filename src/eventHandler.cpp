#include <M5EPD.h>
#include "pantalla.hpp"



extern QueueHandle_t qTouchScreenQueue;
extern M5EPD_Canvas canvas;
extern pantalla scrPrincipal;
extern int iLastUpdate;
extern int iPrimerElemento;

String strFileName="";

void tskEventHandler(void * parameter ){
     tp_finger_t pulsacion;
    while(1){ 
        
        if (xQueueReceive( qTouchScreenQueue , &pulsacion ,  pdMS_TO_TICKS( 1000 ) ) == pdPASS ){
            vTaskDelay(10);
            iLastUpdate=millis();
            Serial.printf("Evento %d %d %d\n",pulsacion.x,pulsacion.y,pulsacion.id);
            // Si esta en el centro ... calculo el indice
            if(pulsacion.id==0){
                if((pulsacion.y>120) && (pulsacion.y<860)){
                    float fIndice = (pulsacion.y -110) / 35;
                    int iIndice= abs(fIndice);
                    Serial.printf("fIndice %f , iIndice %d\n",fIndice,iIndice);
                    scrPrincipal.botonListado(iIndice+iPrimerElemento);
                    continue;
                }

                // botones de abajo
                if ((pulsacion.x<120) && (pulsacion.y>860)){
                    scrPrincipal.boton1();
                    continue;
                }
                if ((pulsacion.x>120) && (pulsacion.x<220) && (pulsacion.y>860)){
                    scrPrincipal.boton2();
                    continue;
                }
                if ((pulsacion.x>220) && (pulsacion.x<320) && (pulsacion.y>860)){
                    scrPrincipal.boton3();
                    continue;
                }
                if ((pulsacion.x>320) && (pulsacion.x<420) && (pulsacion.y>860)){
                    scrPrincipal.boton4();
                    continue;
                }
                if ((pulsacion.x>420) && (pulsacion.y>860)){
                    scrPrincipal.boton5();
                }
            }
            if (pulsacion.id==10){
                if(pulsacion.x==1){
                    scrPrincipal.pgUp();
                }
                if(pulsacion.x==2){
                    scrPrincipal.pgDown();
                }
            }
        }
 //       Serial.println(xQueueReceive( qTouchScreenQueue , &pulsacion ,  pdMS_TO_TICKS( 100000 ) ));
    }
}