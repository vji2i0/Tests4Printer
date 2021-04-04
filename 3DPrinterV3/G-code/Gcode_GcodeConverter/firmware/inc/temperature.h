#include <stdint.h>
#ifndef __TEMPERATURE_CONTROL
#define __TEMPERATURE_CONTROL

/*void regNewADCValue_Extruder1_Temperature(uint16_t raw_value);
void regNewADCValue_Bed_Temperature(uint16_t adc_value);*/

void regNewTemperature_Extruder1_Temperature(float temperature);
void regNewTemperature_Bed_Temperature(float temperature);

float ADC2Temperature_Extruder1_Temperature(uint16_t adc_value);
float ADC2Temperature_Bed_Temperature(uint16_t adc_value);

float getExtruder1_Temperature(void);
float getBed_Temperature(void);

float getTargetExtruder1_Temperature(void);
float getTargetBed_Temperature(void);

void setExtruder1_Temperature(float temp);
void setBed_Temperature(float temp);

void turnOffExtruder1_Temperature(void);
void turnOffBed_Temperature(void);

void init_Temperature(void);                // Should be called once
void pidTimerCallBack_Temperature(void);    // Should be called every 100 ms

/*
    Neet to be defined by user somewere
*/
void setExtruder1_PWM(uint16_t);
void setBed_PWM(uint16_t);
#endif
