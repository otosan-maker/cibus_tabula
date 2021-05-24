#include "time.h"




 void  getTimeLilygo(struct tm *myTm){
     myTm->tm_sec= 00;
    myTm->tm_min= 30;
    myTm->tm_hour= 20;

    myTm->tm_mday=20;
    myTm->tm_mon=3;
    myTm->tm_year=2021;

}

void apagarLilygo(int iDuracion){
    
}

int getVolt(){
    return 4000;
}