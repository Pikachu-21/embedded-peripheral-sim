
cmake_minimum_required(VERSION 3.16)

project(EmbeddedPeripheralSim LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

# GPIO driver library
add_library(gpio_driver
    src/gpio.c
    src/uart.c
    src/adc.c
)

target_include_directories(gpio_driver PUBLIC include)

# GPIO test executable
add_executable(gpio_test
    tests/test_gpio.c
)



target_link_libraries(gpio_test PRIVATE gpio_driver)

# UART test executable
add_executable(uart_test
    tests/test_uart.c
)

target_link_libraries(uart_test PRIVATE gpio_driver)

# Register UART test
add_test(NAME UARTTest COMMAND uart_test)

# ADC test executable
add_executable(adc_test
    tests/test_adc.c
)

target_link_libraries(adc_test PRIVATE gpio_driver)

# Register ADC test
add_test(NAME ADCTest COMMAND adc_test)

# Main application
add_executable(peripheral_demo
    src/main.c
)

target_link_libraries(peripheral_demo PRIVATE gpio_driver)

# Register tests
enable_testing()

add_test(NAME GPIOTest COMMAND gpio_test)
