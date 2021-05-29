#include <wifi.h>
#include <HTTPClient.h>
#include <SD.h>
#include <SPIFFS.h>
#include "cal_interfaces.h"
#include "producto.hpp"
#include "private.hpp"




int wifi_status = 0;

extern producto vProductos[30];
extern int      vProductoSize;


void InitWifi(){
  WiFi.mode(WIFI_STA);
  Serial.printf(" Conectamos a la Wifi %s %s \n",ssid,password);
  WiFi.begin(ssid, password);

 for(int i=0;i<20;i++) {
   if(WiFi.status() == WL_CONNECTED) {
     break;
   }
    delay(500);
    Serial.printf("%d",i);
  }

  //Serial.println("");
  //Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  wifi_status=1;
}




//
//  guardamos en la SD la ultima descarga del fichero
void setUltimaDescarga(String strValue){
  String strLastDownload="";
  
#ifdef CONFIG__M5_PAPER__
  File tmpFile = SD.open("/despensa/last.txt","w");
#else
  File tmpFile = SPIFFS.open("/despensa/last.txt","w");
#endif
  tmpFile.printf("%s",strValue.c_str());
  tmpFile.close();
}


//
//  hemos guardado en la SD la ultima descarga del fichero
String ultimaDescarga(){
  String strLastDownload="";
#ifdef CONFIG__M5_PAPER__
  File tmpFile = SD.open("/despensa/last.txt","r");
#else
  File tmpFile = SPIFFS.open("/despensa/last.txt","r");
#endif
  strLastDownload=tmpFile.readString();
  //Serial.printf("ultimaDescarga %s\n",strLastDownload.c_str());
  tmpFile.close();
  return strLastDownload;
}

//
//  preguntamos a NodeRed cuando fue la ultima modificacion de datos
String ultimaModificacion(){
  String payload="";
  HTTPClient http;
  String serverPath = (String)serverURL + "ultimaModificacion";
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
      
  if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
        Serial.println(payload);
  }else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
  }
  // Free resources
    http.end();
    return (payload);
}


//
//  descargamos el listado de una localizacion
void descargaLocalizacion(String strLocalizacion){
  HTTPClient http;
  String serverPath = (String)serverURL + "listado?localizacion="+strLocalizacion;
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
      
  if (httpResponseCode>0) {
        //Serial.print("HTTP Response code: ");
        //Serial.println(httpResponseCode);
        String payload = http.getString();
#ifdef CONFIG__M5_PAPER__
        File tmpFile=SD.open("/despensa/"+strLocalizacion+".json","w");
#else
        File tmpFile=SPIFFS.open("/despensa/"+strLocalizacion+".json","w");
#endif
        tmpFile.printf("%s",payload.c_str());
        tmpFile.close();
        Serial.println(payload);
  }else {
        //Serial.print("Error code: ");
        //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
    
}


//
//
//  Marcamos los productos consumidos
//
void Consumidos(){
  HTTPClient http;
  char szTmp[128];
  Serial.println("Consumidos");
  for(int i =0;i<vProductoSize;i++){
        if(vProductos[i].m_seleccionado){
          sprintf(szTmp,"%sconsumeID?id=%d",serverURL ,vProductos[i].m_idproducto);
          Serial.printf("Consumidos %d\n",vProductos[i].m_idproducto);
          Serial.println(szTmp);
          http.begin(szTmp);
          int httpResponseCode = http.GET();
          if (httpResponseCode!=0)
            Serial.printf("Obtenemos el codigo HTTP %d\n", httpResponseCode);
          http.end();
          consumido2SD( szTmp);
        }
    }
  Serial.println("Consumidos fin");
}



//
//
//  Sincronizamos los ficheros con Node-Red
//
void Sincroniza_download(const char *szMiLocalizacion){
  String strUltimaDescarga=ultimaDescarga();
  String strUltimaModificacion=ultimaModificacion();
  Serial.printf("ultimaDescarga     :%s:\n",strUltimaDescarga.c_str());
  Serial.printf("ultimaModificacion :%s:\n",strUltimaModificacion.c_str());

  if(strUltimaModificacion>strUltimaDescarga){
    for(int i=0;szgLocalizaciones[i]!=NULL;i++){
      descargaLocalizacion(szgLocalizaciones[i]);
    }
    setUltimaDescarga(strUltimaModificacion);
  }
}

void CloseWifi(){
  WiFi.disconnect();
  wifi_status=0;
}
