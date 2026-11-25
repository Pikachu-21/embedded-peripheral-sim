
#include "adc.h"
#include <stddef.h>

/* Initialize the ADC peripheral */
ADC_Status adc_init(ADC_Registers *adc) {
    if (adc == NULL) {
        return ADC_ERROR;
    }

    adc->data = 0;
    adc->status = 0x00;
    adc->control = ADC_ENABLED;

    return ADC_OK;
}

/* Convert analog voltage into a digital value */
ADC_Status adc_convert(
    ADC_Registers *adc,
    float input_voltage
) {
    if (adc == NULL) {
        return ADC_ERROR;
    }

    /* Check whether ADC is enabled */
    if ((adc->control & ADC_ENABLED) == 0) {
        return ADC_ERROR;
    }

    /* Validate the input voltage */
    if (input_voltage < 0.0f ||
        input_voltage > ADC_REFERENCE_VOLTAGE) {
        return ADC_ERROR;
    }

    /* Calculate the digital conversion result */
    float scaled_value =
        (input_voltage / ADC_REFERENCE_VOLTAGE) * ADC_MAX_VALUE;

    /* Store the converted value */
    adc->data = (uint16_t)(scaled_value + 0.5f);

    /* Indicate that conversion is complete */
    adc->status |= ADC_CONVERSION_READY;

    return ADC_OK;
}

/* Read the completed ADC conversion */
ADC_Status adc_read(
    ADC_Registers *adc,
    uint16_t *digital_value
) {
    if (adc == NULL || digital_value == NULL) {
        return ADC_ERROR;
    }

    /* Check whether ADC is enabled */
    if ((adc->control & ADC_ENABLED) == 0) {
        return ADC_ERROR;
    }

    /* Check whether conversion is complete */
    if ((adc->status & ADC_CONVERSION_READY) == 0) {
        return ADC_ERROR;
    }

    *digital_value = adc->data;

    /* Clear conversion-ready flag after reading */
    adc->status &= (uint8_t)~ADC_CONVERSION_READY;

    return ADC_OK;
}
