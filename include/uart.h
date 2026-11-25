
#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

/* UART operation status */
typedef enum {
    UART_OK,
    UART_ERROR
} UART_Status;

/* Simulated UART registers */
typedef struct {
    uint8_t data;
    uint8_t status;
    uint8_t control;
} UART_Registers;

/* Status register flags */
#define UART_TX_READY  (1u << 0)
#define UART_RX_READY  (1u << 1)

/* Control register flags */
#define UART_ENABLED  (1u << 0)

/* UART driver functions */
UART_Status uart_init(UART_Registers *uart);

UART_Status uart_transmit(
    UART_Registers *uart,
    uint8_t data
);

UART_Status uart_receive(
    UART_Registers *uart,
    uint8_t *data
);

/* Simulation helper: emulate incoming serial data */
UART_Status uart_simulate_receive(
    UART_Registers *uart,
    uint8_t data
);

#endif
