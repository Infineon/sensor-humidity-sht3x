/******************************************************************************
 * \file mtb_sht3x.h
 *
 * \brief
 *     This file is the public interface of the SHT3x humidity sensor.
 *
 ********************************************************************************
 * \copyright
 * Copyright 2024 Cypress Semiconductor Corporation
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#pragma once

#include "cyhal_i2c.h"
#include "sht3x_i2c.h"

#if defined(__cplusplus)
extern "C"
{
#endif


/* Enumeration used for selecting I2C address*/
typedef enum
{
    /** Use the default addresses for the SHT35 sensors (0x44) */
    MTB_SHT35_ADDRESS_DEFAULT  = SHT35_I2C_ADDR_44,
    MTB_SHT35_ADDRESS_SEC      = SHT35_I2C_ADDR_45
} mtb_sht35_address_t;

/* enum defining the different repeatability modes for the periodic measurement */
typedef enum
{
    REPEAT_LOW    = REPEATABILITY_LOW,
    REPEAT_MEDIUM = REPEATABILITY_MEDIUM,
    REPEAT_HIGH   = REPEATABILITY_HIGH
} mtb_sht3x_repeatability_t;

/* enum defining the different messages per second values for the periodic measurement */
typedef enum
{
    MPS_EVERY_TWO_SEC = MPS_EVERY_TWO_SECONDS,
    MPS_ONE_PER_SEC   = MPS_ONE_PER_SECOND,
    MPS_TWO_PER_SEC   = MPS_TWO_PER_SECOND,
    MPS_FOUR_PER_SEC  = MPS_FOUR_PER_SECOND,
    MPS_TEN_PER_SEC   = MPS_TEN_PER_SECOND
} mtb_sht3x_mps_t;

/* Structure to store SHT35 sensor humidity and temperature data */
struct sensor_data_t
{
    double temperature;
    double humidity;
};

/******************************************************************************
* Function Name: mtb_sht3x_init
******************************************************************************
* Summary:
* This function initializes the I2C instance and configures the SHT35.
*
* Parameters:
*  i2c_instance    Pointer to an initialized I2C object
*  i2c_address     I2C address to use when communicating with the sensor
*
* Return:
*  Status of execution
*
******************************************************************************/
cy_rslt_t mtb_sht3x_init(cyhal_i2c_t* i2c_instance, mtb_sht35_address_t i2c_address);

/******************************************************************************
* Function Name: mtb_sht3x_start_periodic_measurement
******************************************************************************
* Summary:
* Starts the periodic measurement mode.
*
* Parameters:
*  i2c_instance        Pointer to an initialized I2C object
*  repeatability_pm    The repeatability of the periodic measurement
*  mps_pm              The messages per second value of the periodic measurement
*
* Return:
*  Status of execution
*
******************************************************************************/
cy_rslt_t mtb_sht3x_start_periodic_measurement(cyhal_i2c_t* i2c_instance,
                                               mtb_sht3x_repeatability_t repeatability_pm,
                                               mtb_sht3x_mps_t mps_pm);

/******************************************************************************
* Function Name: mtb_sht3x_stop_measurement
******************************************************************************
* Summary:
* Stops the periodic measurement mode.
*
* Parameters:
*  i2c_instance        Pointer to an initialized I2C object
*
* Return:
*  Status of execution
*
******************************************************************************/
cy_rslt_t mtb_sht3x_stop_measurement(cyhal_i2c_t* i2c_instance);

/******************************************************************************
* Function Name: mtb_sht3x_soft_reset
******************************************************************************
* Summary:
* Performs a soft reset
*
* Parameters:
*  i2c_instance        Pointer to an initialized I2C object
*
* Return:
*  Status of execution
*
******************************************************************************/
cy_rslt_t mtb_sht3x_soft_reset(cyhal_i2c_t* i2c_instance);

/*****************************************************************************
* Function Name: mtb_sht3x_read_raw
*****************************************************************************
* Summary:
* Reads the SHT35 sensor and gives the raw readings (in milli degree celsius
* and milli percent RH).
*
* Parameters:
*  i2c_instance      Pointer to an initialized I2C object
*  temperature       Measured temperature in milli degree celsius
*  humidity          Measured humidity in milli percent RH
*
* Return:
*  Status of execution
*
*****************************************************************************/
cy_rslt_t mtb_sht3x_read_raw(cyhal_i2c_t* i2c_instance, int32_t* temperature,
                             int32_t* humidity);

/******************************************************************************
* Function Name: mtb_sht3x_read
******************************************************************************
* Summary:
* Reads the SHT35 sensor and returns the sensor readings converted to degree
* celsius and percent RH.
*
* Parameters:
*  i2c_instance        Pointer to an initialized I2C object
*
* Return:
* Updated sensor_data_t structure with the sensor readings converted degree
* celsius and percent RH
*
******************************************************************************/
struct sensor_data_t mtb_sht3x_read(cyhal_i2c_t* i2c_instance);

/******************************************************************************
* Function Name: mtb_sht3x_free
******************************************************************************
* Summary:
* Frees up any resources allocated by mtb_sht3x_init()
*
* Parameters:
*  i2c_instance        Pointer to an initialized I2C object
*
* Return: None
*
******************************************************************************/
void mtb_sht3x_free(cyhal_i2c_t* i2c_instance);

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
