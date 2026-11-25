
#include "gpio.h"

GPIO_Status gpio_init(GPIO_Registers *port) {
    if (port == NULL) {
        return GPIO_ERROR;
    }

    port->direction = 0x00;
    port->output = 0x00;
    port->input = 0x00;

    return GPIO_OK;
}

GPIO_Status gpio_configure_pin(
    GPIO_Registers *port,
    uint8_t pin,
    GPIO_Mode mode
) {
    if (port == NULL || pin >= 8) {
        return GPIO_ERROR;
    }

    if (mode == GPIO_OUTPUT) {
        port->direction |= (uint8_t)(1u << pin);
    }
    else if (mode == GPIO_INPUT) {
        port->direction &= (uint8_t)~(1u << pin);
    }
    else {
        return GPIO_ERROR;
    }

    return GPIO_OK;
}

GPIO_Status gpio_write_pin(
    GPIO_Registers *port,
    uint8_t pin,
    bool value
) {
    if (port == NULL || pin >= 8) {
        return GPIO_ERROR;
    }

    /* Writing is allowed only on output pins. */
    if ((port->direction & (uint8_t)(1u << pin)) == 0) {
        return GPIO_ERROR;
    }

    if (value) {
        port->output |= (uint8_t)(1u << pin);
    }
    else {
        port->output &= (uint8_t)~(1u << pin);
    }

    return GPIO_OK;
}

GPIO_Status gpio_read_pin(
    const GPIO_Registers *port,
    uint8_t pin,
    bool *value
) {
    if (port == NULL || value == NULL || pin >= 8) {
        return GPIO_ERROR;
    }

    uint8_t mask = (uint8_t)(1u << pin);

    if (port->direction & mask) {
        *value = (port->output & mask) != 0;
    }
    else {
        *value = (port->input & mask) != 0;
    }

    return GPIO_OK;
}

GPIO_Status gpio_simulate_input(
    GPIO_Registers *port,
    uint8_t pin,
    bool value
) {
    if (port == NULL || pin >= 8) {
        return GPIO_ERROR;
    }

    /* External signals can only affect input pins. */
    if (port->direction & (uint8_t)(1u << pin)) {
        return GPIO_ERROR;
    }

    if (value) {
        port->input |= (uint8_t)(1u << pin);
    }
    else {
        port->input &= (uint8_t)~(1u << pin);
    }

    return GPIO_OK;
}
