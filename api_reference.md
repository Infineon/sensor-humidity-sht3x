# SHT3X API Reference Guide

## General Description

Basic set of API for Interacting with the Sensirion SHT35 humidity and temperature sensor.

This provides basic initialization and access to the humidity and temperature data. It also provides access to the base SHT3X driver for full control. For more information about the SHT35 humidity and temperature sensor, see: [Sensirion SHT3X Sensor](https://github.com/Sensirion/embedded-i2c-sht3x)


**Note:** All the functions in this library use the I2C address that is specified in the `mtb_sht3x_init()` for all operations. Currently only one I2C address is supported for a given I2C instance.

## Code Snippets

### Snippet 1: Simple initialization with I2C
The following snippet initializes an I2C instance and the SHT35, then does configuration of SHT35.

```
/* Initialize the I2C */
result =  cyhal_i2c_init(&i2c_instance, CYBSP_I2C_SDA,CYBSP_I2C_SCL, NULL);
/* Initialize and configure SHT35 sensor */
 result = mtb_sht3x_init(&i2c_instance, MTB_SHT35_ADDRESS_DEFAULT);
```

### Snippet 2: Start the periodic measurement mode
The following snippet starts the periodic measurement mode based on the specified repeatability and messages per second.

```
/* Starts the periodic measurement mode */
result = mtb_sht3x_start_periodic_measurement(cyhal_i2c_t* i2c_instance, mtb_sht3x_repeatability_t repeatability_pm, mtb_sht3x_mps_t mps_pm);
```

### Snippet 3: Read humidity and temperature data
The data from the sensor can be read in two ways, either raw data or converted data.

1. Reading the raw sensor data - get the values in milli degree celsius and milli percent RH.

    ```
    /* Reads the raw data from SHT35 */
    result = mtb_sht3x_read_raw(&i2c_instance, &temperature, &humidity);
    ```

2. Reading the converted sensor data - get the values in degree celsius and percent RH.

    ```
    /* Reads the data from SHT35 */
    sensor_data = mtb_sht3x_read(&i2c_instance);
    ```

## Data Structure
```
struct sensor_data_t    Structure holding the SHT35 sensor humidity and temperature converted data
```

## Enumerations
- Enumeration used for selecting I2C address.

 ```
typedef enum
{
    MTB_SHT35_ADDRESS_DEFAULT  = SHT35_I2C_ADDR_44,
    MTB_SHT35_ADDRESS_SEC      = SHT35_I2C_ADDR_45
} mtb_sht35_address_t;
```

- Enumeration specifying different repeatability modes for the periodic measurement.

```
typedef enum
{
    REPEAT_LOW    = REPEATABILITY_LOW,
    REPEAT_MEDIUM = REPEATABILITY_MEDIUM,
    REPEAT_HIGH   = REPEATABILITY_HIGH
} mtb_sht3x_repeatability_t;
```

- Enumeration specifying different messages per second values for the periodic measurement.

```
typedef enum
{
    MPS_EVERY_TWO_SEC = MPS_EVERY_TWO_SECONDS,
    MPS_ONE_PER_SEC   = MPS_ONE_PER_SECOND,
    MPS_TWO_PER_SEC   = MPS_TWO_PER_SECOND,
    MPS_FOUR_PER_SEC  = MPS_FOUR_PER_SECOND,
    MPS_TEN_PER_SEC   = MPS_TEN_PER_SECOND
} mtb_sht3x_mps_t;

```

## Functions
cy_rslt_t `mtb_sht3x_init(cyhal_i2c_t* i2c_instance, mtb_sht35_address_t i2c_address)`
>Initializes the I2C instance and configures the SHT35.

cy_rslt_t `mtb_sht3x_start_periodic_measurement(cyhal_i2c_t* i2c_instance, mtb_sht3x_repeatability_t repeatability_pm, mtb_sht3x_mps_t mps_pm)`
>Starts the periodic measurement mode based on the specified repeatability and messages per second.

cy_rslt_t `mtb_sht3x_stop_measurement(cyhal_i2c_t* i2c_instance)`
>Stops the periodic measurement mode.

cy_rslt_t `mtb_sht3x_soft_reset(cyhal_i2c_t* i2c_instance)`
>Performs a soft reset of the sensor.

cy_rslt_t `mtb_sht3x_read_raw(cyhal_i2c_t* i2c_instance, int32_t* temperature, int32_t* humidity)`
>Reads the SHT35 sensor data and gives the raw values (in milli degree celsius and milli percent RH).

sensor_data_t `mtb_sht3x_read(cyhal_i2c_t* i2c_instance)`
>Reads the SHT35 sensor data and returns sensor readings converted to degree celsius and percent RH.

void `mtb_sht3x_free(cyhal_i2c_t* i2c_instance)`
>Frees up any resources allocated by mtb_sht3x_init().

## Data Structure Documentation
- sensor_data_t

 Member             |  Description
 :-------           |  :------------
 temperature        | Converted temperature data (in degree C)
 humidity           | Converted humidity data (in percent RH)

## Function Documentation
#### mtb_sht3x_init
- cy_rslt_t `mtb_sht3x_init(cyhal_i2c_t* i2c_instance, mtb_sht35_address_t i2c_address)`

> **Summary:** This function initializes the I2C instance and configures the SHT35.
>
> **Parameter:**
>  Parameters            |  Description
>  :-------              |  :------------
>  i2c_instance          |  Pointer to an initialized I2C object.
>  i2c_address           |  I2C address to use when communicating with the sensor.
>
> Return:
>  - cy_rslt_t           :  Status of execution

#### mtb_sht3x_start_periodic_measurement
- cy_rslt_t `mtb_sht3x_start_periodic_measurement(cyhal_i2c_t* i2c_instance, mtb_sht3x_repeatability_t repeatability_pm, mtb_sht3x_mps_t mps_pm)`

> **Summary:** Starts the periodic measurement mode.
>
> **Parameter:**
>  Parameters            |  Description
>  :-------              |  :------------
>  i2c_instance          |  Pointer to an initialized I2C object.
> repeatability_pm       |  The repeatability of the periodic measurement.
> mps_pm                 |  The messages per second value of the periodic measurement.
>
> Return:
>  - cy_rslt_t           :  Status of execution.

#### mtb_sht3x_stop_measurement
- cy_rslt_t `mtb_sht3x_stop_measurement(cyhal_i2c_t* i2c_instance)`

> **Summary:** Stops the periodic measurement mode.
>
> **Parameter:**
>  Parameters            |  Description
>  :-------              |  :------------
>  i2c_instance          |  Pointer to an initialized I2C object.
> 
> Return:
>  - cy_rslt_t           :  Status of execution.

#### mtb_sht3x_soft_reset
- cy_rslt_t `mtb_sht3x_soft_reset(cyhal_i2c_t* i2c_instance)`

> **Summary:** Performs a soft reset of the sensor.
>
> **Parameter:**
>  Parameters            |  Description
>  :-------              |  :------------
>  i2c_instance          |  Pointer to an initialized I2C object.
> 
> Return:
>  - cy_rslt_t           :  Status of execution.

#### mtb_sht3x_read_raw
- cy_rslt_t `mtb_sht3x_read_raw(cyhal_i2c_t* i2c_instance, int32_t* temperature, int32_t* humidity)`

>**Summary:** Reads the SHT35 sensor and gives the raw values (in milli degree celsius and milli percent RH).
>
> **Parameter:**
>  Parameters           |  Description
>  :-------             |  :------------
>  i2c_instance         |  Pointer to an initialized I2C object.
>  temperature          |  Measured temperature in milli degree celsius.
>  humidity             |  Measured humidity in milli percent RH.
>
> Return:
>  - cy_rslt_t          :  Status of execution.

#### mtb_sht3x_read
- sensor_data_t `mtb_sht3x_read(cyhal_i2c_t* i2c_instance)`

>**Summary:** Reads the SHT35 sensor and returns the sensor readings converted to degree celsius and percent RH.
>
> **Parameter:**
>  Parameters            |  Description
>  :-------              |  :------------
>  i2c_instance          |  Pointer to an initialized I2C object.
> 
> Return:
>  - sht3x              :  Updated sensor_data_t structure with the sensor readings converted to degree celsius and percent RH.

#### mtb_sht3x_free
- void `mtb_sht3x_free(cyhal_i2c_t* i2c_instance)`

>**Summary:** Frees up any resources allocated by `mtb_sht3x_init()`
>
> **Parameter:**
>  Parameters            |  Description
>  :-------              |  :------------
>  i2c_instance          |  Pointer to an initialized I2C object.

---
© 2024, Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation.
