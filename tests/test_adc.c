
#include "adc.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    ADC_Registers adc;
    uint16_t digital_value = 0;

    /* Test 1: Initialize ADC */
    assert(adc_init(&adc) == ADC_OK);

    assert(adc.data == 0);
    assert(adc.status == 0x00);
    assert(adc.control == ADC_ENABLED);

    /* Test 2: Convert 0 volts */
    assert(adc_convert(&adc, 0.0f) == ADC_OK);
    assert(adc.data == 0);

    assert((adc.status & ADC_CONVERSION_READY) != 0);

    assert(adc_read(&adc, &digital_value) == ADC_OK);
    assert(digital_value == 0);

    /* Test 3: Convert half the reference voltage */
    assert(adc_convert(&adc, 1.65f) == ADC_OK);
    assert(adc.data == 512);

    assert(adc_read(&adc, &digital_value) == ADC_OK);
    assert(digital_value == 512);

    /* Test 4: Convert maximum reference voltage */
    assert(adc_convert(&adc, 3.3f) == ADC_OK);
    assert(adc.data == ADC_MAX_VALUE);

    assert(adc_read(&adc, &digital_value) == ADC_OK);
    assert(digital_value == 1023);

    /* Test 5: Reject invalid voltages */
    assert(adc_convert(&adc, -0.5f) == ADC_ERROR);
    assert(adc_convert(&adc, 3.5f) == ADC_ERROR);

    /* Test 6: Cannot read without a completed conversion */
    assert(adc_read(&adc, &digital_value) == ADC_ERROR);

    /* Test 7: Verify conversion-ready flag is cleared */
    assert((adc.status & ADC_CONVERSION_READY) == 0);

    /* Test 8: Reject operations when ADC is disabled */
    adc.control &= (uint8_t)~ADC_ENABLED;

    assert(adc_convert(&adc, 1.0f) == ADC_ERROR);
    assert(adc_read(&adc, &digital_value) == ADC_ERROR);

    /* Test 9: Null pointer handling */
    assert(adc_init(NULL) == ADC_ERROR);
    assert(adc_convert(NULL, 1.0f) == ADC_ERROR);
    assert(adc_read(NULL, &digital_value) == ADC_ERROR);
    assert(adc_read(&adc, NULL) == ADC_ERROR);

    printf("All ADC tests passed!\n");

    return 0;
}
