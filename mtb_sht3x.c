/******************************************************************************
 * \file mtb_sht3x.c
 *
 * \brief
 *     This file contains the functions for interacting with the
 *     SHT3x humidity sensor.
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


#include "mtb_sht3x.h"
#include "sensirion_i2c_hal.h"
#include "sensirion_common.h"
#include "cyhal.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/******************************************************************************
* Macros
******************************************************************************/
#define SHT3X_DELAY (1000)

/******************************************************************************
* Global variables
******************************************************************************/
cyhal_i2c_t* sht3x_i2c = NULL;

/******************************************************************************
* mtb_sht3x_init
******************************************************************************/
cy_rslt_t mtb_sht3x_init(cyhal_i2c_t* i2c_instance, mtb_sht35_address_t i2c_address)
{
    cy_rslt_t result;

    CY_ASSERT(i2c_instance != NULL);
    sht3x_init(i2c_address);

    sht3x_i2c = i2c_instance;

    result = mtb_sht3x_stop_measurement(sht3x_i2c);
    sensirion_i2c_hal_sleep_usec(SHT3X_DELAY);
    result = mtb_sht3x_soft_reset(sht3x_i2c);
    sensirion_i2c_hal_sleep_usec(SHT3X_DELAY);

    return result;
}


/******************************************************************************
* mtb_sht3x_start_periodic_measurement
******************************************************************************/
cy_rslt_t mtb_sht3x_start_periodic_measurement(cyhal_i2c_t* i2c_instance,
                                               mtb_sht3x_repeatability_t repeatability_pm,
                                               mtb_sht3x_mps_t mps_pm)
{
    CY_ASSERT(i2c_instance != NULL);
    sht3x_i2c = i2c_instance;

    return sht3x_start_periodic_measurement((repeatability)repeatability_pm, (mps)mps_pm);
}


/******************************************************************************
* mtb_sht3x_stop_measurement
******************************************************************************/
cy_rslt_t mtb_sht3x_stop_measurement(cyhal_i2c_t* i2c_instance)
{
    CY_ASSERT(i2c_instance != NULL);
    sht3x_i2c = i2c_instance;
    return sht3x_stop_measurement();
}


/******************************************************************************
* mtb_sht3x_soft_reset
******************************************************************************/
cy_rslt_t mtb_sht3x_soft_reset(cyhal_i2c_t* i2c_instance)
{
    CY_ASSERT(i2c_instance != NULL);
    sht3x_i2c = i2c_instance;
    return sht3x_soft_reset();
}


/******************************************************************************
* mtb_sht3x_read_raw
******************************************************************************/
cy_rslt_t mtb_sht3x_read_raw(cyhal_i2c_t* i2c_instance, int32_t* temperature,
                             int32_t* humidity)
{
    CY_ASSERT(i2c_instance != NULL);
    sht3x_i2c = i2c_instance;
    return sht3x_blocking_read_measurement(temperature, humidity);
}


/******************************************************************************
* mtb_sht3x_read
******************************************************************************/
struct sensor_data_t mtb_sht3x_read(cyhal_i2c_t* i2c_instance)
{
    CY_ASSERT(i2c_instance != NULL);
    sht3x_i2c = i2c_instance;

    struct sensor_data_t sht3x;
    int32_t temperature;
    int32_t humidity;
    sht3x_blocking_read_measurement(&temperature, &humidity);
    /* conversion from milli degrees to degree */
    sht3x.temperature = (double)(temperature)/1000.0;
    /* conversion from milli percent RH to percent RH */
    sht3x.humidity = (double)(humidity)/1000.0;

    return sht3x;
}


/******************************************************************************
* mtb_sht3x_free
******************************************************************************/
void mtb_sht3x_free(cyhal_i2c_t* i2c_instance)
{
    CY_ASSERT(i2c_instance != NULL);
    sht3x_i2c = i2c_instance;
    sensirion_i2c_hal_free();
}


#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
