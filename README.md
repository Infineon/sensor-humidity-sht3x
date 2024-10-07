# SHT35 Digital Humidity and Temperature Sensor

## Overview

This library provides functions for interfacing with the SHT35 digital humidity and temperature sensor used on the SHIELD_XENSIV_A.

Datasheet: https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf

GitHub: https://github.com/Sensirion/embedded-i2c-sht3x

## Quick Start

Follow the steps below to create a simple application which outputs the humidity and temperature data from the sensor to the UART.

1. Create an empty ModusToolbox™ application.
2. Add this (sensor-humidity-sht3x) library to the application.
3. Add retarget-io library using the Library Manager.
4. Place following code in the main.c file.

```
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "mtb_sht3x.h"

cyhal_i2c_t i2c;
cyhal_i2c_cfg_t i2c_cfg =
{
    .is_slave        = false,
    .address         = 0,
    .frequencyhal_hz = 400000
};

#define SHT_I2C_SDA (CYBSP_I2C_SDA)
#define SHT_I2C_SCL (CYBSP_I2C_SCL)

int main(void)
{
    cy_rslt_t result;
    int32_t humidity;
    int32_t temperature;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Initialize I2C for interfacing with sensor */
    result = cyhal_i2c_init(&i2c, SHT_I2C_SDA, SHT_I2C_SCL, NULL);
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }
    result = cyhal_i2c_configure(&i2c, &i2c_cfg);
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Initialize and configure the sensor */
    result = mtb_sht3x_init(&i2c, MTB_SHT35_ADDRESS_DEFAULT);
    if (CY_RSLT_SUCCESS != result)
    {
        CY_ASSERT(0);
    }

    /* Starts the periodic measurement mode */
    result = mtb_sht3x_start_periodic_measurement(&i2c, REPEAT_MEDIUM, MPS_ONE_PER_SEC);

    for (;;)
    {
        /* Get the humidity and temperature, and print the results to the UART */
        mtb_sht3x_read_raw(&i2c, &temperature, &humidity);
        printf("\nHumidity    : %ld milli RH\r\n", (long)humidity);
        printf("Temperature : %ld milli degC\r\n\r\n", (long)temperature);
        cyhal_system_delay_ms(1000);
    }
}
```

5. Build the application and program the kit.

## More information

For more information, refer to the following documents:

* [API Reference Guide](./api_reference.md)
* [ModusToolbox Software Environment, Quick Start Guide, Documentation, and Videos](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software)
* [Infineon Technologies AG](https://www.infineon.com)

-----
© 2024, Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation.
