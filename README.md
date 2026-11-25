# Embedded Peripheral Driver & Register Simulation

[![C Build and Test](https://github.com/Pikachu-21/embedded-peripheral-sim/actions/workflows/ci.yml/badge.svg)](https://github.com/Pikachu-21/embedded-peripheral-sim/actions/workflows/ci.yml)

A lightweight **C11-based embedded systems simulation** demonstrating the implementation and testing of GPIO, UART, and ADC peripheral drivers using mock hardware registers.

The project explores low-level programming concepts commonly found in embedded software development, including bitwise register manipulation, peripheral configuration, status flags, input validation, and modular driver design.

> **Note:** This is a software simulation. It models peripheral register behaviour without interacting with physical microcontrollers or hardware devices.

## Features

### 1. GPIO (General Purpose Input/Output)

- Simulates an 8-pin GPIO peripheral.
- Configures individual pins as input or output.
- Uses bitwise operations to manipulate direction and output registers.
- Supports simulated external input signals.
- Prevents writing to pins configured as inputs.

### 2. UART (Universal Asynchronous Receiver/Transmitter)

- Simulates UART data, status, and control registers.
- Implements basic transmit and receive operations.
- Uses status flags to represent transmission readiness and received data availability.
- Handles disabled peripherals and unread-data conditions.
- Demonstrates splitting and reconstructing a 16-bit value using two 8-bit bytes.

### 3. ADC (Analog-to-Digital Converter)

- Simulates a 10-bit ADC with a 3.3 V reference voltage.
- Converts analog voltage inputs into digital values.
- Supports an input range of 0–3.3 V.
- Implements conversion-ready status handling.
- Uses rounding when calculating digital output values.

## Project Architecture

```text
embedded-peripheral-sim/
│
├── .github/
│   └── workflows/
│       └── ci.yml
│
├── include/
│   ├── gpio.h
│   ├── uart.h
│   └── adc.h
│
├── src/
│   ├── main.c
│   ├── gpio.c
│   ├── uart.c
│   └── adc.c
│
├── tests/
│   ├── test_gpio.c
│   ├── test_uart.c
│   └── test_adc.c
│
├── CMakeLists.txt
├── .gitignore
└── README.md
```

The project follows a modular driver architecture:

- **Header files:** Define register structures, status codes, constants, and driver interfaces.
- **Source files:** Implement peripheral initialization and operations.
- **Test files:** Validate individual driver behaviour and error conditions.
- **Main application:** Integrates the simulated peripherals into a sensor-monitoring workflow.

## Technologies Used

| Technology | Purpose |
|---|---|
| C11 | Driver implementation |
| GCC | Compilation |
| CMake | Build configuration |
| CTest | Automated test execution |
| Git & GitHub | Version control |
| GitHub Actions | Continuous integration |

## Getting Started

### Prerequisites

- GCC or another compatible C compiler
- CMake 3.16 or later
- Git

### Clone the repository

```bash
git clone https://github.com/Pikachu-21/embedded-peripheral-sim.git

cd embedded-peripheral-sim
```

### Configure the project

```bash
cmake -S . -B build
```

### Build the project

```bash
cmake --build build
```

### Run the application

```bash
./build/peripheral_demo
```

### Run unit tests

```bash
ctest --test-dir build --output-on-failure
```

## Integrated Demonstration

The application demonstrates a complete simulated sensor-monitoring cycle:

1. Initializes the GPIO, UART, and ADC peripherals.
2. Supplies a simulated sensor voltage of 2.1 V to the ADC.
3. Converts the voltage into a 10-bit digital value.
4. Activates a GPIO indicator when the voltage reaches the configured threshold of 1.65 V.
5. Splits the ADC reading into two bytes.
6. Demonstrates UART byte handling and reconstructs the original value.
7. Verifies the reconstructed value against the original ADC reading.

Example output:

```text
====================================
  EMBEDDED PERIPHERAL MONITORING
====================================

All peripherals initialized successfully.

Sensor voltage: 2.10 V
Digital sensor reading: 651
Indicator state: ON

UART Transmission:
High byte: 2
Low byte: 139

UART Reception:
Reconstructed ADC value: 651
Data integrity check: PASSED

Monitoring cycle completed successfully!
====================================
```

## Testing

The project includes three independent test suites:

| Test suite | Coverage |
|---|---|
| GPIO Tests | Initialization, pin configuration, read/write operations, invalid pins and input simulation |
| UART Tests | Initialization, transmission, reception, status flags, disabled operations and invalid pointers |
| ADC Tests | Initialization, voltage conversion, boundary values, invalid inputs and conversion status |

Tests are executed using CTest.

## Continuous Integration

GitHub Actions automatically builds and tests the project whenever changes are pushed to the `main` branch or a pull request targets it.

The CI workflow performs the following steps:

1. Checks out the repository.
2. Installs the required compiler and build tools.
3. Configures the project using CMake.
4. Compiles the drivers, test executables, and integrated demo.
5. Runs all registered unit tests.

The workflow helps ensure that changes do not break the existing build or test suites.

## Engineering Concepts Demonstrated

- Modular embedded driver architecture
- Mock peripheral register modelling
- Bitwise operations and bit masking
- Register and status-flag manipulation
- Input validation and error handling
- Integer conversion and byte manipulation
- Unit testing and build automation
- Continuous integration using GitHub Actions

## Scope and Limitations

This project is intended as an educational software simulation of embedded peripheral drivers.

It does not implement physical GPIO signalling, real UART communication, ADC hardware sampling, baud-rate configuration, interrupt handling, or hardware-specific register access.

The simulated UART uses simplified status flags and a single data register rather than a hardware FIFO or transmission queue.

The project provides a foundation for understanding peripheral-driver concepts before progressing to actual microcontroller development.

## Future Improvements

- Introduce configurable UART baud rates and framing parameters.
- Implement simulated UART buffers and interrupt-driven operations.
- Add ADC sampling and conversion timing models.
- Extend GPIO functionality with pull-up and pull-down configuration.
- Integrate hardware-specific drivers on a microcontroller development board.

---

**Author:** [Pikachu-21](https://github.com/Pikachu-21)  
**Repository:** [embedded-peripheral-sim](https://github.com/Pikachu-21/embedded-peripheral-sim)