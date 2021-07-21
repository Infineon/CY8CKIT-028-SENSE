/***********************************************************************************************//**
 * \file cy8ckit_028_sense.h
 *
 * Description: This file is the top level interface for the CY8CKIT-028-SENSE
 *              shield board.
 *
 * For the details of E-INK display hardware and driver interface, see the
 * documents available at the following website:
 * https://www.pervasivedisplays.com/product/2-71-e-ink-display/
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

#pragma once

#include "cy8ckit_028_sense_pins.h"
#include "cy_result.h"
#include "cybsp.h"
#include "cyhal_i2c.h"
#include "cyhal_spi.h"
#include "cyhal_adc.h"
#include "cyhal_pdmpcm.h"
#include "mtb_bmx160.h"
#include "mtb_wm8960.h"
#include "mtb_ssd1306.h"
#include "xensiv_dps3xx_mtb.h"

/**
 * \defgroup group_board_libs_shield Shield
 * \defgroup group_board_libs_pins Pins
 * \defgroup group_board_libs_orientation Orientation Sensor
 * \defgroup group_board_libs_pressure Pressure Sensor
 * \defgroup group_board_libs_display OLED Display
 * \defgroup group_board_libs_codec Audio CODEC
 *
 * \addtogroup group_board_libs_orientation
 * \{
 * The orientation sensor is handled by the sensor-orientation-bmx160 library, details are available
 * at https://github.com/cypresssemiconductorco/sensor-orientation-bmx160.
 * \}
 * \addtogroup group_board_libs_pressure
 * \{
 * The pressure sensor is handled by the sensor-xensiv-dps3xx library, details are
 * available at https://github.com/cypresssemiconductorco/sensor-xensiv-dps3xx.
 * \}
 * \addtogroup group_board_libs_display
 * \{
 * The display is handled by the display-oled-ssd1306 library, details are available at
 * https://github.com/cypresssemiconductorco/display-oled-ssd1306.
 * \}
 * \addtogroup group_board_libs_codec
 * \{
 * The audio codec is handled by the audio-codec-wm8960 library, details are available at
 * https://github.com/cypresssemiconductorco/audio-codec-wm8960.
 * \}
 */

/**
 * \addtogroup group_board_libs_shield
 * \{
 * Basic set of APIs for interacting with the CY8CKIT-028-SENSE shield board.
 * This provides pin definitions and initialization code for the shield.
 * Initialization of the shield configures the internal peripherals to allow
 * them to be used.
 */

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * Initialize the shield board and all peripherals contained on it.
 * @param[in] i2c_inst  An optional I2C instance to use for communicating with the display
 * and sensors on the shield. If NULL, a new instance will be allocated using the CYBSP_I2C_SCL
 * & CYBSP_I2C_SDA pins.
 * @param[in] spi_inst  An optional SPI instance to use for communicating with the orientation
 * sensor. If NULL, the I2C interface will be used.
 * @param[in] adc_inst  An optional ADC instance to use for communicating with the analog mic.
 * If NULL, a new instance will be allocated.
 * @param[in] pdm_pcm_cfg The configuration for the PDM object used with the microphone.
 * If NULL, the PDM object will not be initialized.
 * @param[in] audio_clock_inst The audio clock used with the microphone.
 * If NULL, the PDM object will not be initialized.
 * @return CY_RSLT_SUCCESS if properly initialized, else an error indicating what went wrong.
 */
cy_rslt_t cy8ckit_028_sense_init(cyhal_i2c_t* i2c_inst, cyhal_spi_t* spi_inst,
                                 cyhal_adc_t* adc_inst, const cyhal_pdm_pcm_cfg_t* pdm_pcm_cfg,
                                 cyhal_clock_t* audio_clock_inst);

/**
 * Gives the user access to the orientation sensor object
 * @return A reference to the orientation sensor object on this shield.
 */
mtb_bmx160_t* cy8ckit_028_sense_get_orientation_sensor(void);

/**
 * Gives the user access to the pressure sensor object
 * @return A reference to the pressure sensor object on this shield.
 */
xensiv_dps3xx_t* cy8ckit_028_sense_get_pressure_sensor(void);

/**
 * Gives the user access to the PDM object used with the microphone.
 * This will be null if the arguments to setup the PDM interface were not provided.
 * @return A reference to the PDM microphone object on this shield.
 */
cyhal_pdm_pcm_t* cy8ckit_028_sense_get_pdm(void);

/**
 * Frees up any resources allocated as part of \ref cy8ckit_028_sense_init().
 */
void cy8ckit_028_sense_free(void);

#if defined(__cplusplus)
}
#endif

/** \} group_board_libs */
