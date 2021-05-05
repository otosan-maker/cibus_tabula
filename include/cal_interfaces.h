



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