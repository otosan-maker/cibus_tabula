
#include "time.h"


void tskTouchScreen(void * parameter );
void tskEventHandler(void * parameter );

void InitWifi();
void Sincroniza_download(const char *);
void CloseWifi();


void writeBatt2SD();
void msg2BatteryLog(const char* );

void guardaEstado();
void cargaEstado();
void apagamos();

void Consumidos();
void consumido2SD(const char* szURL);

void print_wakeup_reason();

 void  getTimeM5(struct tm *myTm);
 void apagarM5(int iDuracion);

 void  getTimeLilygo(struct tm *myTm);
 void apagarLiligo(int iDuracion);