#pragma once

extern void (*ADC_HANDLER)(uint16_t);

extern void adc_init(void);
extern uint16_t adc_read( uint8_t channel );
extern void adc_start_read(uint8_t channel);
