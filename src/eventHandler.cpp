
#include <Arduino.h>
#include "pantalla.hpp"
#include "pantalla_M5.hpp"
#include "pantalla_lilygo.hpp"



extern QueueHandle_t qTouchScreenQueue;


#ifdef CONFIG__M5_PAPER__
extern pantalla_M5 *pScrPrincipal;
#else
extern pantalla_lilygo *pScrPrincipal;
#endif

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
                    pScrPrincipal->botonListado(iIndice+iPrimerElemento);
                    continue;
                }

                // botones de abajo
                if ((pulsacion.x<120) && (pulsacion.y>860)){
                    pScrPrincipal->boton1();
                    continue;
                }
                if ((pulsacion.x>120) && (pulsacion.x<220) && (pulsacion.y>860)){
                    pScrPrincipal->boton2();
                    continue;
                }
                if ((pulsacion.x>220) && (pulsacion.x<320) && (pulsacion.y>860)){
                    pScrPrincipal->boton3();
                    continue;
                }
                if ((pulsacion.x>320) && (pulsacion.x<420) && (pulsacion.y>860)){
                    pScrPrincipal->boton4();
                    continue;
                }
                if ((pulsacion.x>420) && (pulsacion.y>860)){
                    pScrPrincipal->boton5();
                }
            }
            if (pulsacion.id==10){
                if(pulsacion.x==1){
                    pScrPrincipal->pgUp();
                }
                if(pulsacion.x==2){
                    pScrPrincipal->pgDown();
                }
            }
        }
 //       Serial.println(xQueueReceive( qTouchScreenQueue , &pulsacion ,  pdMS_TO_TICKS( 100000 ) ));
    }
}