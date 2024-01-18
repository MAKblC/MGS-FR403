/*****************************************************
  Library for flame sensor MGS-FR403

  Maxim Kotov, Saint-Petersburg, Russia
  kotovm@mgbot.ru
  17-01-2024

  https://github.com/MAKblC/Codes/tree/master/MGS-FR403
******************************************************/

#include "Arduino.h"
#include "MGS_FR403.h"

//MGS_FR403::MGS_FR403() {}

void MGS_FR403::begin(void) {
  Wire.begin();
  Wire.beginTransmission(sensor_addr);
  Wire.write(ADC_integration_time);       // Регистр времени интегрирования АЦП
  Wire.write(0b00111111); // 180 мс, 65535 циклов
  Wire.endTransmission();
  Wire.beginTransmission(sensor_addr);
  Wire.write(Waiting_time);       // Регистр времени ожидания
  Wire.write(0b00111111); // 180 мс
  Wire.endTransmission();
  Wire.beginTransmission(sensor_addr);
  Wire.write(Gain);         // Регистр усиления
  Wire.write(0b00000000);   // Усиление 1x
  Wire.endTransmission();
  Wire.beginTransmission(sensor_addr);
  Wire.write(Power_control);       // Регистр управления питанием
  Wire.write(0b00001011); // Включение ожидания, генератора, АЦП и ALS сенсора
  Wire.endTransmission();

}


void MGS_FR403::get_ir_and_vis(void) {

  unsigned int sensor_data[4];
  Wire.beginTransmission(sensor_addr);
  Wire.write(Data_reg); // Начальный адрес регистров данных
  Wire.endTransmission();
  Wire.requestFrom(sensor_addr, 4);
  if (Wire.available() == 4) {
    sensor_data[0] = Wire.read();
    sensor_data[1] = Wire.read();
    sensor_data[2] = Wire.read();
    sensor_data[3] = Wire.read();
  }
  ir_data   = sensor_data[3] * 256.0 + sensor_data[2];
  vis_data = sensor_data[1] * 256.0 + sensor_data[0];
}