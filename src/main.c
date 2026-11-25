
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"
#include "uart.h"
#include "adc.h"

#define SENSOR_THRESHOLD 1.65f
#define INDICATOR_PIN 3

int main(void) {

    /* Create simulated peripheral registers */
    GPIO_Registers gpio;
    UART_Registers uart;
    ADC_Registers adc;

    uint16_t sensor_reading = 0;
    uint8_t received_high = 0;
    uint8_t received_low = 0;
    uint16_t reconstructed_value = 0;
    bool indicator_state = false;

    float sensor_voltage = 2.1f;

    printf("\n====================================\n");
    printf("  EMBEDDED PERIPHERAL MONITORING\n");
    printf("====================================\n");

    /* Step 1: Initialize peripherals */
    if (gpio_init(&gpio) != GPIO_OK ||
        uart_init(&uart) != UART_OK ||
        adc_init(&adc) != ADC_OK) {

        printf("Peripheral initialization failed!\n");
        return 1;
    }

    printf("\nAll peripherals initialized successfully.\n");

    /* Step 2: Configure GPIO indicator pin */
    if (gpio_configure_pin(
            &gpio,
            INDICATOR_PIN,
            GPIO_OUTPUT
        ) != GPIO_OK) {

        printf("GPIO configuration failed!\n");
        return 1;
    }

    /* Step 3: Simulate analog sensor input */
    printf("\nSensor voltage: %.2f V\n", sensor_voltage);

    if (adc_convert(&adc, sensor_voltage) != ADC_OK) {
        printf("ADC conversion failed!\n");
        return 1;
    }

    /* Step 4: Read ADC conversion result */
    if (adc_read(&adc, &sensor_reading) != ADC_OK) {
        printf("ADC reading failed!\n");
        return 1;
    }

    printf("Digital sensor reading: %u\n",
           (unsigned int)sensor_reading);

    /* Step 5: Determine indicator state */
    indicator_state = sensor_voltage >= SENSOR_THRESHOLD;

    if (gpio_write_pin(
            &gpio,
            INDICATOR_PIN,
            indicator_state
        ) != GPIO_OK) {

        printf("GPIO output operation failed!\n");
        return 1;
    }

    printf("Indicator state: %s\n",
           indicator_state ? "ON" : "OFF");

    
    /* Step 6: Split the 10-bit ADC reading into two bytes */
    uint8_t high_byte = (uint8_t)(sensor_reading >> 8);
    uint8_t low_byte = (uint8_t)(sensor_reading & 0xFF);

    /* Transmit the high byte */
    if (uart_transmit(&uart, high_byte) != UART_OK) {
        printf("UART high-byte transmission failed!\n");
        return 1;
    }

    /* Transmit the low byte */
    if (uart_transmit(&uart, low_byte) != UART_OK) {
        printf("UART low-byte transmission failed!\n");
       return 1;
    }

    printf("\nUART Transmission:\n");
    printf("High byte: %u\n", (unsigned int)high_byte);
    printf("Low byte: %u\n", (unsigned int)low_byte);


    /* Step 7: Simulate receiving the two transmitted bytes */
    if (uart_simulate_receive(&uart, high_byte) != UART_OK) {
        printf("UART high-byte reception failed!\n");
        return 1;
    }

    if (uart_receive(&uart, &received_high) != UART_OK) {
        printf("UART high-byte read failed!\n");
        return 1;
    }

    if (uart_simulate_receive(&uart, low_byte) != UART_OK) {
        printf("UART low-byte reception failed!\n");
        return 1;
    }

    if (uart_receive(&uart, &received_low) != UART_OK) {
        printf("UART low-byte read failed!\n");
        return 1;
    }

    /* Reconstruct the original ADC reading */
    reconstructed_value =
        ((uint16_t)received_high << 8) | received_low;

    printf("\nUART Reception:\n");
    printf("Reconstructed ADC value: %u\n",
          (unsigned int)reconstructed_value);

    /* Verify data integrity */
    if (reconstructed_value != sensor_reading) {
       printf("Data integrity check failed!\n");
        return 1;
    }

    printf("Data integrity check: PASSED\n");



    printf("\nMonitoring cycle completed successfully!\n");
    printf("====================================\n");

    return 0;
}
