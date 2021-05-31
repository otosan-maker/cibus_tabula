#include <Arduino.h>
#include "time.h"
#include "esp_adc_cal.h"


#define BATT_PIN            36

 void  getTimeLilygo(struct tm *myTm){
     myTm->tm_sec= 00;
    myTm->tm_min= 30;
    myTm->tm_hour= 20;

    myTm->tm_mday=20;
    myTm->tm_mon=3;
    myTm->tm_year=2021;

}

void apagarLilygo(){
      
    // esp_sleep_enable_ext1_wakeup(GPIO_SEL_13, ESP_EXT1_WAKEUP_ANY_HIGH);
    // Set to wake up by GPIO35
    esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
    esp_deep_sleep_start();
}

int getVolt(){
    int vref = 1100;

    // Correct the ADC reference voltage
    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        Serial.printf("eFuse Vref:%u mV\n", adc_chars.vref);
        vref = adc_chars.vref;
    }

    uint16_t v = analogRead(BATT_PIN);
    Serial.printf("AnalogRead  %u mV\n", v);
    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
    String voltage = "➸ Voltage :" + String(battery_voltage) + "V";
    Serial.printf("%s\n", voltage.c_str());
    return v+2000;
}