#include <ArduinoJson.h>
#include <SD.h>
#include <SPIFFS.h>
#include  "jsonCom.hpp"
#include "producto.hpp"


producto vProductos[MAX_NUM_PRODUCTOS];
int      vProductoSize=0;
int      iPrimerElemento=0;
char     szLocalizacion[25];


void clearvProductos(){
  for(int i=0;i<vProductoSize;i++){
    vProductos[i].set(1,"","","",""); 
  }
  vProductoSize=0;
  iPrimerElemento=0;
}



void loadJson(const char*szMiLocalizacion){
    DynamicJsonDocument doc(8048);
    char szFile[40];
    clearvProductos();
    sprintf(szFile,"/despensa/%s.json",szMiLocalizacion);
    // Deserialize the JSON document
#ifdef CONFIG__M5_PAPER__
  File fLeemos = SD.open(szFile,"r");
#else
  File fLeemos = SPIFFS.open(szFile,"r");
#endif
    DeserializationError error = deserializeJson(doc, fLeemos);
 
    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    Serial.printf("tamaño del vector %d\n",sizeof(vProductos));
    JsonObject repo0 = doc[0];
    vProductoSize=0;
    for(int i=1;repo0;i++){
      const char* identificador = repo0["prod_id"] | "1";
      const char* fecha_a = repo0["f_alta"] | " ";
      const char* fecha_b = repo0["f_baja"] | " ";
      const char* prod = repo0["producto"] | " ";
      const char* localizacion = repo0["localizacion"] | " ";
      
      vProductos[vProductoSize++].set(atoi(identificador),fecha_a,fecha_b,prod,localizacion); 

      Serial.printf("leimos %s :: %s :: %s :: %s :: %s \n",identificador,fecha_a,fecha_b,prod,localizacion);
      repo0 = doc[i];
    }
    
    fLeemos.close();
}