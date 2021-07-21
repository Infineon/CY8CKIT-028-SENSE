/***********************************************************************************************//**
 * \file cy8ckit_028_sense.c
 *
 * \brief
 *    Implementation file of the shield support library.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2021 Cypress Semiconductor Corporation
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
 **************************************************************************************************/

#include "cy8ckit_028_sense.h"
#ifdef EMWIN_ENABLED
#include "GUI.h"
#include "LCDConf.h"
#endif

typedef enum
{
    _CY8CKIT_028_SENSE_INITIALIZED_NONE = 0x00,
    _CY8CKIT_028_SENSE_INITIALIZED_ORIENTATION = 0x01,
    _CY8CKIT_028_SENSE_INITIALIZED_PRESSURE = 0x02,
    _CY8CKIT_028_SENSE_INITIALIZED_DISPLAY = 0x04,
    _CY8CKIT_028_SENSE_INITIALIZED_PDM = 0x08
} cy8ckit_028_sense_initialized_t;

static cyhal_i2c_t                      i2c;
static cyhal_adc_t                      adc;

static mtb_bmx160_t                     orientation_sensor;
static xensiv_dps3xx_t                  pressure_sensor;
static cyhal_pdm_pcm_t                  pdm_pcm;

static cyhal_i2c_t*                     i2c_ptr;
static cyhal_adc_t*                     adc_ptr;
static cy8ckit_028_sense_initialized_t  initialized = _CY8CKIT_028_SENSE_INITIALIZED_NONE;

//--------------------------------------------------------------------------------------------------
// cy8ckit_028_sense_init
//--------------------------------------------------------------------------------------------------
cy_rslt_t cy8ckit_028_sense_init(cyhal_i2c_t* i2c_inst, cyhal_spi_t* spi_inst,
                                 cyhal_adc_t* adc_inst, const cyhal_pdm_pcm_cfg_t* pdm_pcm_cfg,
                                 cyhal_clock_t* audio_clock_inst)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if (NULL == i2c_inst)
    {
        static const cyhal_i2c_cfg_t I2C_CFG =
        {
            .is_slave        = false,
            .address         = 0,
            .frequencyhal_hz = 400000
        };
        result = cyhal_i2c_init(&i2c, CY8CKIT_028_SENSE_PIN_I2C_SDA,
                                CY8CKIT_028_SENSE_PIN_I2C_SCL, NULL);
        if (CY_RSLT_SUCCESS == result)
        {
            i2c_ptr = &i2c;
            result  = cyhal_i2c_configure(&i2c, &I2C_CFG);
        }
    }
    else
    {
        i2c_ptr = i2c_inst;
    }

    if ((CY_RSLT_SUCCESS == result) && (NULL == adc_inst))
    {
        result = cyhal_adc_init(&adc, CY8CKIT_028_SENSE_PIN_VM_AOUT, NULL);
        if (CY_RSLT_SUCCESS == result)
        {
            adc_ptr = &adc;
        }
    }
    else
    {
        adc_ptr = adc_inst;
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = (NULL == spi_inst)
            ? mtb_bmx160_init_i2c(&orientation_sensor, i2c_ptr, MTB_BMX160_ADDRESS_DEFAULT)
            : mtb_bmx160_init_spi(&orientation_sensor, spi_inst, CY8CKIT_028_SENSE_PIN_SPI_CS);
    }
    if (CY_RSLT_SUCCESS == result)
    {
        initialized |= _CY8CKIT_028_SENSE_INITIALIZED_ORIENTATION;
        result = xensiv_dps3xx_mtb_init_i2c(&pressure_sensor, i2c_ptr,
                                            XENSIV_DPS3XX_I2C_ADDR_DEFAULT);
    }
    if (CY_RSLT_SUCCESS == result)
    {
        initialized |= _CY8CKIT_028_SENSE_INITIALIZED_PRESSURE;
        result = mtb_ssd1306_init_i2c(i2c_ptr);
    }

    // Initialize the PDM/PCM block
    if (CY_RSLT_SUCCESS == result)
    {
        initialized |= _CY8CKIT_028_SENSE_INITIALIZED_DISPLAY;
        if ((NULL != audio_clock_inst) && (NULL != pdm_pcm_cfg))
        {
            result = cyhal_pdm_pcm_init(&pdm_pcm, CY8CKIT_028_SENSE_PIN_PDM_DATA,
                                        CY8CKIT_028_SENSE_PIN_PDM_CLK, audio_clock_inst,
                                        pdm_pcm_cfg);

            if (CY_RSLT_SUCCESS == result)
            {
                initialized |= _CY8CKIT_028_SENSE_INITIALIZED_PDM;
            }
        }
    }

    if (CY_RSLT_SUCCESS != result)
    {
        cy8ckit_028_sense_free();
    }

    return result;
}


//--------------------------------------------------------------------------------------------------
// cy8ckit_028_sense_get_orientation_sensor
//--------------------------------------------------------------------------------------------------
mtb_bmx160_t* cy8ckit_028_sense_get_orientation_sensor(void)
{
    return &orientation_sensor;
}


//--------------------------------------------------------------------------------------------------
// cy8ckit_028_sense_get_pressure_sensor
//--------------------------------------------------------------------------------------------------
xensiv_dps3xx_t* cy8ckit_028_sense_get_pressure_sensor(void)
{
    return &pressure_sensor;
}


//--------------------------------------------------------------------------------------------------
// cy8ckit_028_sense_get_pdm
//--------------------------------------------------------------------------------------------------
cyhal_pdm_pcm_t* cy8ckit_028_sense_get_pdm(void)
{
    return ((initialized & _CY8CKIT_028_SENSE_INITIALIZED_PDM) > 0)
        ? &pdm_pcm
        : NULL;
}


//--------------------------------------------------------------------------------------------------
// cy8ckit_028_sense_free
//--------------------------------------------------------------------------------------------------
void cy8ckit_028_sense_free(void)
{
    if ((initialized & _CY8CKIT_028_SENSE_INITIALIZED_DISPLAY) > 0)
    {
        mtb_ssd1306_free();
    }
    if ((initialized & _CY8CKIT_028_SENSE_INITIALIZED_PRESSURE) > 0)
    {
        xensiv_dps3xx_free(&pressure_sensor);
    }
    if ((initialized & _CY8CKIT_028_SENSE_INITIALIZED_ORIENTATION) > 0)
    {
        mtb_bmx160_free(&orientation_sensor);
    }
    if ((initialized & _CY8CKIT_028_SENSE_INITIALIZED_PDM) > 0)
    {
        cyhal_pdm_pcm_free(&pdm_pcm);
    }
    initialized = _CY8CKIT_028_SENSE_INITIALIZED_NONE;

    if (i2c_ptr == &i2c)
    {
        cyhal_i2c_free(i2c_ptr);
    }
    i2c_ptr = NULL;

    // This must be done last, in case other code prior to this frees an ADC channel
    if (adc_ptr == &adc)
    {
        cyhal_adc_free(adc_ptr);
    }
    adc_ptr = NULL;
}
