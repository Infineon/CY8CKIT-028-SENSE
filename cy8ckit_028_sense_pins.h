/***********************************************************************************************//**
 * \file cy8ckit_028_sense_pins.h
 *
 * Description: This file contains the pin definitions for the CY8CKIT-028-SENSE shield board.
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

#include "cybsp.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * \addtogroup group_board_libs_pins Pins
 * \{
 * Pin mapping of the GPIOs used by shield peripherals
 */

// Audio Codec, Display, Orientation Sensor and Pressure Sensor I2C pins
/** Pin for the shared I2C SCL signal */
#define CY8CKIT_028_SENSE_PIN_I2C_SCL       (CYBSP_I2C_SCL)
/** Pin for the shared I2C SDA signal */
#define CY8CKIT_028_SENSE_PIN_I2C_SDA       (CYBSP_I2C_SDA)

// Orientation Sensor pins
/** Pin for the orientation sensor SPI SCK signal */
#define CY8CKIT_028_SENSE_PIN_SPI_SCK       (CYBSP_D13)
/** Pin for the orientation sensor SPI MISO signal */
#define CY8CKIT_028_SENSE_PIN_SPI_MISO      (CYBSP_D12)
/** Pin for the orientation sensor SPI MOSI signal */
#define CY8CKIT_028_SENSE_PIN_SPI_MOSI      (CYBSP_D11)
/** Pin for the orientation sensor SPI CS signal */
#define CY8CKIT_028_SENSE_PIN_SPI_CS        (CYBSP_D10)
/** Pin for the IMU Interrupt1 signal */
#define CY8CKIT_028_SENSE_PIN_IMU_INT_1     (CYBSP_A2)
/** Pin for the IMU Interrupt2 signal */
#define CY8CKIT_028_SENSE_PIN_IMU_INT_2     (CYBSP_A3)

// Pressure Sensor pins
/** Pin for the Pressure sensor Interrupt signal */
#define CY8CKIT_028_SENSE_PIN_PSEN_INT      (CYBSP_D7)

// Microphone I2S interface
/** Pin for the I2S MCLK signal */
#define CY8CKIT_028_SENSE_PIN_MCU_MCLK      (CYBSP_D8)
/** Pin for the I2S RX SDI signal */
#define CY8CKIT_028_SENSE_PIN_RX_SDI        (CYBSP_D6)
/** Pin for the I2S RX WS signal */
#define CY8CKIT_028_SENSE_PIN_RX_WS         (CYBSP_D5)
/** Pin for the I2S RX SCK signal */
#define CY8CKIT_028_SENSE_PIN_RX_SCK        (CYBSP_D4)
/** Pin for the I2S TX SDO signal */
#define CY8CKIT_028_SENSE_PIN_TX_SDO        (CYBSP_D3)
/** Pin for the I2S TX WS signal */
#define CY8CKIT_028_SENSE_PIN_TX_WS         (CYBSP_D2)
/** Pin for the I2S TX SCK signal */
#define CY8CKIT_028_SENSE_PIN_TX_SCK        (CYBSP_D1)
/** Pin for the I2S IF signal */
#define CY8CKIT_028_SENSE_PIN_I2S_IF        (CYBSP_D0)

// Audio Codec
/** Pin for the Audio Codec's AOUT signal */
#define CY8CKIT_028_SENSE_PIN_VM_AOUT       (CYBSP_A0)
/** Pin for the Audio Codec's PSO signal */
#define CY8CKIT_028_SENSE_PIN_VM_PSO        (CYBSP_J2_6)
/** Pin for the Audio Codec's Mode signal */
#define CY8CKIT_028_SENSE_PIN_VM_MODE       (CYBSP_J2_10)
/** Pin for the Audio Codec's DOUT signal */
#define CY8CKIT_028_SENSE_PIN_VM_DOUT       (CYBSP_J2_12)

// PDM Microphone
/** Pin for the PDM Clock */
#define CY8CKIT_028_SENSE_PIN_PDM_CLK       (CYBSP_A4)
/** Pin for the PDM Data */
#define CY8CKIT_028_SENSE_PIN_PDM_DATA      (CYBSP_A5)
/** Pin for the PDM1 VDD */
#define CY8CKIT_028_SENSE_PIN_PDM1_VDD      (CYBSP_J2_2)
/** Pin for the PDM2 VDD */
#define CY8CKIT_028_SENSE_PIN_PDM2_VDD      (CYBSP_J2_4)

/** \} group_board_libs_pins */

#if defined(__cplusplus)
}
#endif
