#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

void (*ADC_HANDLER)(uint16_t) = 0;

void adc_init(void)
{
    // die Versorgungsspannung AVcc als Referenz wählen:
    //ADMUX = (1<<REFS0);
    // AREF als referenzspannung nehmen
    ADMUX = 0x00;

    // Bit ADFR ("free running") in ADCSRA steht beim Einschalten
    // schon auf 0, also single conversion
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Frequenzvorteiler
    ADCSRA |= (1 << ADEN);                               // ADC aktivieren
}

uint16_t adc_read(uint8_t channel)
{
    // Kanal waehlen, ohne andere Bits zu beeinflußen
    ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);

    ADCSRA |= (1 << ADSC); // eine ADC-Wandlung
    while (ADCSRA & (1 << ADSC))
        ;
    return ADCW;
}

void adc_start_read(uint8_t channel)
{
    ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
    ADCSRA |= (1 << ADSC) | (1<<ADIE);
}

ISR(ADC_vect)
{
    if (ADC_HANDLER != 0)
        ADC_HANDLER(ADCW);
}