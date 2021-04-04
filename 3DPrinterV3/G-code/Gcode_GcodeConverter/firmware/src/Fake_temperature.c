#include "temperature.h"
#include "CppUTestExt/MockSupport_c.h"

static float current_extruder1_temperature, target_extruder1_temperature;

static float current_bed_temperature, target_bed_temperature;

void init_Temperature(void)
{
    turnOffExtruder1_Temperature();
    turnOffBed_Temperature();
}

void regNewTemperature_Extruder1_Temperature(float temperature)
{
    current_extruder1_temperature = temperature;
}


float ADC2Temperature_Extruder1_Temperature(uint16_t adc_value)
{
    return 0;
}



float getExtruder1_Temperature(void)
{
    return current_extruder1_temperature;
}

void setExtruder1_Temperature(float temp)
{
    target_extruder1_temperature = temp;
}

float getTargetExtruder1_Temperature(void)
{
    return target_extruder1_temperature;
}

void turnOffExtruder1_Temperature(void)
{
    target_extruder1_temperature = 0;
    mock_c()->actualCall("turnOffExtruder1_Temperature");
}

void pidTimerCallBack_Temperature(void)
{
}


float ADC2Temperature_Bed_Temperature(uint16_t adc_value)
{
    return 0;
}

void regNewTemperature_Bed_Temperature(float temperature)
{
    current_bed_temperature = temperature;
}

float getBed_Temperature(void)
{
    return current_bed_temperature;
}

void setBed_Temperature(float temp)
{
    target_bed_temperature = temp;
}

float getTargetBed_Temperature(void)
{
    return target_bed_temperature;
}

void turnOffBed_Temperature(void)
{
    target_bed_temperature = 0;
    mock_c()->actualCall("turnOffBed_Temperature");
}
