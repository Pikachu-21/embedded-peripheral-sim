
#include "gpio.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    GPIO_Registers port;
    bool value = false;

    /* Initialize registers */
    assert(gpio_init(&port) == GPIO_OK);
    assert(port.direction == 0x00);
    assert(port.output == 0x00);
    assert(port.input == 0x00);

    /* Configure pin 3 as output */
    assert(gpio_configure_pin(&port, 3, GPIO_OUTPUT) == GPIO_OK);
    assert(port.direction == 0x08);

    /* Set pin 3 HIGH */
    assert(gpio_write_pin(&port, 3, true) == GPIO_OK);
    assert(gpio_read_pin(&port, 3, &value) == GPIO_OK);
    assert(value == true);

    /* Set pin 3 LOW */
    assert(gpio_write_pin(&port, 3, false) == GPIO_OK);
    assert(gpio_read_pin(&port, 3, &value) == GPIO_OK);
    assert(value == false);

    /* Configure pin 2 as input */
    assert(gpio_configure_pin(&port, 2, GPIO_INPUT) == GPIO_OK);

    /* Simulate an external HIGH signal */
    assert(gpio_simulate_input(&port, 2, true) == GPIO_OK);
    assert(gpio_read_pin(&port, 2, &value) == GPIO_OK);
    assert(value == true);

    /* Writing to an input pin should fail */
    assert(gpio_write_pin(&port, 2, true) == GPIO_ERROR);

    /* Invalid pin should fail */
    assert(gpio_configure_pin(&port, 8, GPIO_OUTPUT) == GPIO_ERROR);

    /* Null register pointer should fail */
    assert(gpio_init(NULL) == GPIO_ERROR);

    /* Verify independent pin manipulation */
    assert(gpio_configure_pin(&port, 1, GPIO_OUTPUT) == GPIO_OK);

    assert(gpio_write_pin(&port, 1, true) == GPIO_OK);

    assert(port.output == 0x02);

    assert(gpio_write_pin(&port, 3, true) == GPIO_OK);

    assert(port.output == 0x0A);

    printf("All GPIO tests passed!\n");

    return 0;
}
