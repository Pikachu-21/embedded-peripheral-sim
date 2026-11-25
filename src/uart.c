
#include "uart.h"
#include <stddef.h>

/* Initialize the UART peripheral */
UART_Status uart_init(UART_Registers *uart) {
    if (uart == NULL) {
        return UART_ERROR;
    }

    uart->data = 0x00;
    uart->status = UART_TX_READY;
    uart->control = UART_ENABLED;

    return UART_OK;
}

/* Simulate transmission of one byte */
UART_Status uart_transmit(
    UART_Registers *uart,
    uint8_t data
) {
    if (uart == NULL) {
        return UART_ERROR;
    }

    /* Check whether UART is enabled */
    if ((uart->control & UART_ENABLED) == 0) {
        return UART_ERROR;
    }

    /* Check whether transmitter is ready */
    if ((uart->status & UART_TX_READY) == 0) {
        return UART_ERROR;
    }

    /* Load data into the transmit register */
    uart->data = data;

    /* Simulate transmission completion */
    uart->status |= UART_TX_READY;

    return UART_OK;
}

/* Retrieve received data */
UART_Status uart_receive(
    UART_Registers *uart,
    uint8_t *data
) {
    if (uart == NULL || data == NULL) {
        return UART_ERROR;
    }

    if ((uart->control & UART_ENABLED) == 0) {
        return UART_ERROR;
    }

    /* Check whether received data is available */
    if ((uart->status & UART_RX_READY) == 0) {
        return UART_ERROR;
    }

    *data = uart->data;

    /* Clear receive-ready flag after reading */
    uart->status &= (uint8_t)~UART_RX_READY;

    return UART_OK;
}

/* Simulate incoming serial data */
UART_Status uart_simulate_receive(
    UART_Registers *uart,
    uint8_t data
) {
    if (uart == NULL) {
        return UART_ERROR;
    }

    if ((uart->control & UART_ENABLED) == 0) {
        return UART_ERROR;
    }

    /* Prevent overwriting unread received data */
    if (uart->status & UART_RX_READY) {
        return UART_ERROR;
    }

    uart->data = data;

    /* Indicate that received data is available */
    uart->status |= UART_RX_READY;

    return UART_OK;
}
