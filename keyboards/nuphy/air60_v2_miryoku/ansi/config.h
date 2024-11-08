/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define TAP_CODE_DELAY              8
#define DYNAMIC_KEYMAP_MACRO_DELAY  8
#define EECONFIG_USER_DATA_SIZE     8

#define DEV_MODE_PIN                C0
#define SYS_MODE_PIN                C1
#define DC_BOOST_PIN                C2
#define NRF_RESET_PIN               B4
#define NRF_BOOT_PIN                B5
#define NRF_WAKEUP_PIN              C4

#define RGB_DRIVER_SDB1             C6
#define RGB_DRIVER_SDB2             C7

#define SERIAL_DRIVER               SD1
#define SD1_TX_PIN                  B6
#define SD1_TX_PAL_MODE             0
#define SD1_RX_PIN                  B7
#define SD1_RX_PAL_MODE             0


// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 AD <-> GND
// 0b1110111 AD <-> VCC
// 0b1110101 AD <-> SCL
// 0b1110110 AD <-> SDA
#define DRIVER_ADDR_1              0b1010000
#define DRIVER_ADDR_2              0b1010011
#define ISSI_TIMEOUT               1

#define I2C_DRIVER                 I2CD1
#define I2C1_SCL_PIN               B8
#define I2C1_SDA_PIN               B9
#define I2C1_CLOCK_SPEED           1000000

#define I2C1_SCL_PAL_MODE          1
#define I2C1_SDA_PAL_MODE          1

#define I2C1_TIMINGR_PRESC         0U
#define I2C1_TIMINGR_SCLDEL        0U
#define I2C1_TIMINGR_SDADEL        0U
#define I2C1_TIMINGR_SCLH          0U
#define I2C1_TIMINGR_SCLL          0U
#define I2C1_DUTY_CYCLE            FAST_DUTY_CYCLE_16_9


#define DRIVER_COUNT               2
#define DRIVER_1_LED_TOTAL         48
#define DRIVER_2_LED_TOTAL         (16 + 10)
#define RGB_MATRIX_LED_COUNT       (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

#define RGB_MATRIX_DEFAULT_MODE    RGB_MATRIX_CYCLE_LEFT_RIGHT  // Sets the default mode, if none has been set
#define RGB_MATRIX_SLEEP                          // turn off effects when suspended

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// Enable bilateral combinations with a hold time threshold
// The last mod-tap hold will convert to the corresponding mod-tap tap if another key on the same hand is tapped during the hold, unless a key on the other hand is tapped first.
// This prevents accidental modifier combinations, especially those caused by rollover on home row mods.
// Holds longer than 500 milliseconds will permit same hand combinations.
#define BILATERAL_COMBINATIONS 500

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// Set the mouse settings to a comfortable speed/accuracy trade-off,
// assuming a screen refresh rate of 60 Htz or higher
// The default is 50. This makes the mouse ~3 times faster and more accurate
#define MOUSEKEY_INTERVAL 16
// The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// give it more time to accelerate to max speed to retain precise control over short distances.
#define MOUSEKEY_TIME_TO_MAX 40
// The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
#define MOUSEKEY_DELAY 100
// It makes sense to use the same delay for the mouseweel
#define MOUSEKEY_WHEEL_DELAY 100
// The default is 100
#define MOUSEKEY_WHEEL_INTERVAL 50
// The default is 40
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100
