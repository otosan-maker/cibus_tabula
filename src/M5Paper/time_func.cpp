#include "time.h"
#include <M5EPD.h>



 void  getTimeM5(struct tm *myTm){
    rtc_time_t RTCtime;
    M5.RTC.getTime(&RTCtime);
    myTm->tm_sec= RTCtime.sec;
    myTm->tm_min= RTCtime.min;
    myTm->tm_hour= RTCtime.hour;

}

void apagarM5(int iDuracion){
    M5.shutdown(iDuracion);
}