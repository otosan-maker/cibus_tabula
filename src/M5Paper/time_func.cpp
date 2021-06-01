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


void inittime_m5(struct tm mGlobalTm ){
    rtc_time_t RTCtime;
    rtc_date_t RTCDate;
    RTCtime.hour = mGlobalTm.tm_hour;
    RTCtime.min = mGlobalTm.tm_min;
    RTCtime.sec = mGlobalTm.tm_sec;
    M5.RTC.setTime(&RTCtime);
    RTCDate.year = mGlobalTm.tm_year;
    RTCDate.mon = mGlobalTm.tm_mon;
    RTCDate.day = mGlobalTm.tm_mday;
    M5.RTC.setDate(&RTCDate);
}