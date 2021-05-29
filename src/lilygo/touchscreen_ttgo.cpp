#include "touch.h"
#include "Button2.h"
#include "epd_driver.h"

#define BUTTON_1            34
#define BUTTON_2            35
#define BUTTON_3            39

#define TOUCH_INT   13
TouchClass touch;

extern QueueHandle_t qTouchScreenQueue;

Button2  btn1(BUTTON_1);
Button2  btn2(BUTTON_2);
Button2  btn3(BUTTON_3);

void b1Pressed(Button2 &b){
    tp_finger_t FingerItem;
    FingerItem.id=10;
    FingerItem.x=1;
    Serial.printf("B1 wasPressed!\n");
    xQueueSend( qTouchScreenQueue,( void * ) &FingerItem, ( TickType_t ) 0 );
    
}
void b2Pressed(Button2 &b){
    tp_finger_t FingerItem;
    FingerItem.id=10;
    FingerItem.x=2;
    Serial.printf("B2 wasPressed!\n");
    xQueueSend( qTouchScreenQueue,( void * ) &FingerItem, ( TickType_t ) 0 );
    
    
}
void b3Pressed(Button2 &b){
    
    
}


void tskTouchScreen_ttgo(void * parameter ){
    int point[2]={0,0};
    tp_finger_t FingerItem;
    Serial.println("Starting tskTouchScreen_ttgo ...");
    //Inicializamos los botones
    btn1.setPressedHandler(b1Pressed);
    btn2.setPressedHandler(b2Pressed);
    btn3.setPressedHandler(b3Pressed);
    Wire.begin(15, 14);

    if (!touch.begin()) {
        Serial.println("start touchscreen failed");
        while (1) delay(2000);
    }
    Serial.println("Started Touchscreen poll...");
    while(1){ 
        if(digitalRead(TOUCH_INT)){
            if(touch.scanPoint()){
                uint16_t  x, y;
                touch.getPoint(x, y, 0);
                FingerItem.x=EPD_HEIGHT - y;
                FingerItem.y=EPD_WIDTH - x;
                FingerItem.id=0;
                if( (point[0]!=FingerItem.x)&& (point[1]!=FingerItem.y)){
                    //Serial.printf("Finger ID:%d-->X: %d  Y: %d  Size: %d\n", 
                    //                FingerItem.id, FingerItem.x, FingerItem.y , FingerItem.size);
                     xQueueSend( qTouchScreenQueue,( void * ) &FingerItem, ( TickType_t ) 0 );
                }
                point[0]=FingerItem.x;
                point[1]=FingerItem.y;
            }
        }
       
        delay(50);

    }
}