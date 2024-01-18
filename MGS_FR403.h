/*****************************************************
  Library for flame sensor MGS-FR403

  Maxim Kotov, Saint-Petersburg, Russia
  kotovm@mgbot.ru
  17-01-2024

  https://github.com/MAKblC/Codes/tree/master/MGS-FR403
******************************************************/

#ifndef MGS_FR403_h
#define MGS_FR403_h

#include "Arduino.h"
#include "Wire.h"

#define sensor_addr 0x39

// Instruction set architecture modes

#define ADC_integration_time 0x81

#define Waiting_time 0x83

#define Gain 0x90

#define Power_control 0x80

#define Data_reg 0x94

class MGS_FR403 {

  public:
    float ir_data;
    float vis_data;
    // MGS_FR403();
    void begin(void);
    void get_ir_and_vis(void);

};

#endif