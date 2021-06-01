
#include "time.h"
#include <SD.h>

#define FILE_LAST_STATE "/configuracion/estado.txt"

void tskTouchScreen(void * parameter );
void tskTouchScreen_ttgo(void * parameter );
void tskEventHandler(void * parameter );

void InitWifi();
void Sincroniza_download(const char *);
void CloseWifi();


void writeBatt2SD();
void msg2BatteryLog(const char* );

void guardaEstado();
void cargaEstado(File fEstado);
void apagamos();

void Consumidos();
void consumido2SD(const char* szURL);

void print_wakeup_reason();

 void  getTimeM5(struct tm *myTm);
 void inittime_m5(struct tm mGlobalTm );
 void apagarM5(int iDuracion);

 void  getTimeLilygo(struct tm *myTm);
 void apagarLiligo(int iDuracion);
 int getVolt();