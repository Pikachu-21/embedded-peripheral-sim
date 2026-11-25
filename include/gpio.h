
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Simulated GPIO operating modes */
typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT
} GPIO_Mode;

/* Function return status */
typedef enum {
    GPIO_OK,
    GPIO_ERROR
} GPIO_Status;

/* Simulated hardware registers */
typedef struct {
    uint8_t direction;
    uint8_t output;
    uint8_t input;
} GPIO_Registers;

/* GPIO driver functions */
GPIO_Status gpio_init(GPIO_Registers *port);

GPIO_Status gpio_configure_pin(
    GPIO_Registers *port,
    uint8_t pin,
    GPIO_Mode mode
);

GPIO_Status gpio_write_pin(
    GPIO_Registers *port,
    uint8_t pin,
    bool value
);

GPIO_Status gpio_read_pin(
    const GPIO_Registers *port,
    uint8_t pin,
    bool *value
);

/* Simulation helper: emulate an external input signal */
GPIO_Status gpio_simulate_input(
    GPIO_Registers *port,
    uint8_t pin,
    bool value
);

#endif
