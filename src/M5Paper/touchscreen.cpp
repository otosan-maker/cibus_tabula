#include <M5EPD.h>

extern QueueHandle_t qTouchScreenQueue;

void tskTouchScreen(void * parameter ){
    int point[2]={0,0};
    tp_finger_t FingerItem;
    while(1){ 
        if(M5.TP.avaliable()){
            M5.update();

            if(!M5.TP.isFingerUp()){
                M5.TP.update();    
                FingerItem = M5.TP.readFinger(0);
                if( (point[0]!=FingerItem.x)&& (point[1]!=FingerItem.y)){
                    //Serial.printf("Finger ID:%d-->X: %d  Y: %d  Size: %d\n", 
                    //                FingerItem.id, FingerItem.x, FingerItem.y , FingerItem.size);
                     xQueueSend( qTouchScreenQueue,( void * ) &FingerItem, ( TickType_t ) 0 );
                }
                point[0]=FingerItem.x;
                point[1]=FingerItem.y;
            }

            
        }

        M5.update();
        if( M5.BtnL.wasPressed()) {
           FingerItem.id=10;
           FingerItem.x=1;
           //Serial.printf("BtnL wasPressed!\n");
           xQueueSend( qTouchScreenQueue,( void * ) &FingerItem, ( TickType_t ) 0 );
        } 
        if( M5.BtnR.wasPressed()) {
            FingerItem.id=10;
            FingerItem.x=2;
            //Serial.printf("Btnr wasPressed!\n");
            xQueueSend( qTouchScreenQueue,( void * ) &FingerItem, ( TickType_t ) 0 );
        }
       
        delay(50);

    }
}