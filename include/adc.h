
#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ADC_OK,
    ADC_ERROR
} ADC_Status;

#define ADC_RESOLUTION 10
#define ADC_MAX_VALUE ((1u << ADC_RESOLUTION) - 1u)
#define ADC_REFERENCE_VOLTAGE 3.3f

typedef struct {
    uint16_t data;
    uint8_t status;
    uint8_t control;
} ADC_Registers;

#define ADC_CONVERSION_READY (1u << 0)
#define ADC_ENABLED (1u << 0)

ADC_Status adc_init(ADC_Registers *adc);

ADC_Status adc_convert(
    ADC_Registers *adc,
    float input_voltage
);

ADC_Status adc_read(
    ADC_Registers *adc,
    uint16_t *digital_value
);

#endif
