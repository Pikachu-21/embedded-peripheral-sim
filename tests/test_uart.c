
#include "uart.h"

#include <assert.h>
#include <stdio.h>


/* Test transmission and reconstruction of a 16-bit value */
static void test_uart_round_trip(uint16_t original_value) {
    UART_Registers uart;

    uint8_t high_byte;
    uint8_t low_byte;

    uint8_t received_high = 0;
    uint8_t received_low = 0;

    uint16_t reconstructed_value;

    assert(uart_init(&uart) == UART_OK);

    /* Split the original value into two bytes */
    high_byte = (uint8_t)(original_value >> 8);
    low_byte = (uint8_t)(original_value & 0xFF);

    /* Transmit both bytes */
    assert(uart_transmit(&uart, high_byte) == UART_OK);
    assert(uart_transmit(&uart, low_byte) == UART_OK);

    /* Simulate receiving the high byte */
    assert(uart_simulate_receive(&uart, high_byte) == UART_OK);
    assert(uart_receive(&uart, &received_high) == UART_OK);

    /* Simulate receiving the low byte */
    assert(uart_simulate_receive(&uart, low_byte) == UART_OK);
    assert(uart_receive(&uart, &received_low) == UART_OK);

    /* Reconstruct the original value */
    reconstructed_value =
        ((uint16_t)received_high << 8) | received_low;

    assert(reconstructed_value == original_value);
}


int main(void) {
    UART_Registers uart;
    uint8_t received_data = 0;

    /* Test 1: Initialize UART */
    assert(uart_init(&uart) == UART_OK);

    assert(uart.data == 0x00);
    assert(uart.status == UART_TX_READY);
    assert(uart.control == UART_ENABLED);

    /* Test 2: Transmit a byte */
    assert(uart_transmit(&uart, 0x41) == UART_OK);

    assert(uart.data == 0x41);
    assert((uart.status & UART_TX_READY) != 0);

    /* Test 3: Simulate incoming data */
    assert(uart_simulate_receive(&uart, 0x42) == UART_OK);

    assert(uart.data == 0x42);
    assert((uart.status & UART_RX_READY) != 0);

    /* Test 4: Receive the incoming byte */
    assert(uart_receive(&uart, &received_data) == UART_OK);

    assert(received_data == 0x42);
    assert((uart.status & UART_RX_READY) == 0);

    /* Test 5: Cannot receive the same byte twice */
    assert(uart_receive(&uart, &received_data) == UART_ERROR);

    /* Test 6: Cannot overwrite unread received data */
    assert(uart_simulate_receive(&uart, 0x43) == UART_OK);
    assert(uart_simulate_receive(&uart, 0x44) == UART_ERROR);

    /* Test 7: Reject transmission when UART is disabled */
    uart.control &= (uint8_t)~UART_ENABLED;

    assert(uart_transmit(&uart, 0x45) == UART_ERROR);
    assert(uart_simulate_receive(&uart, 0x46) == UART_ERROR);
    assert(uart_receive(&uart, &received_data) == UART_ERROR);

    /* Test 8: Null pointer handling */
    assert(uart_init(NULL) == UART_ERROR);
    assert(uart_transmit(NULL, 0x41) == UART_ERROR);
    assert(uart_receive(NULL, &received_data) == UART_ERROR);
    assert(uart_receive(&uart, NULL) == UART_ERROR);
    assert(uart_simulate_receive(NULL, 0x41) == UART_ERROR);


    /* Test 9: Multi-byte transmission and reconstruction */

    /* Minimum 10-bit value */
    test_uart_round_trip(0);

    /* Maximum value representable in one byte */
    test_uart_round_trip(255);

    /* First value requiring two bytes */
    test_uart_round_trip(256);

    /* Maximum 10-bit ADC value */
    test_uart_round_trip(1023);


    printf("All UART tests passed!\n");

    return 0;
}
