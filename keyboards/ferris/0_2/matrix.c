/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
          2020 Pierre Chevalier <pierrechevalier83@gmail.com>

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

/*
 * This code was heavily inspired by the ergodox_ez keymap, and modernized
 * to take advantage of the quantum.h microcontroller agnostics gpio control
 * abstractions and use the macros defined in config.h for the wiring as opposed
 * to repeating that information all over the place.
 */

#include "matrix.h"
#include "debug.h"
#include "wait.h"
#include "i2c_master.h"

extern i2c_status_t mcp23017_status;
#define MCP23017_I2C_TIMEOUT 1000

// For a better understanding of the i2c protocol, this is a good read:
// https://www.robot-electronics.co.uk/i2c-tutorial

// I2C address:
// See the datasheet, section 3.3.1 on addressing I2C devices and figure 3-6 for an
// illustration
// http://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf
// All address pins of the mcp23017 are connected to the ground on the ferris
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_ADDR (0b0100000 << 1)

// Register addresses
// See https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/blob/master/Adafruit_MCP23017.h
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C  // GPIO pull-up resistor register
#define GPPUB 0x0D
#define MCP23017_GPIOA 0x12  // general purpose i/o port register (write modifies OLAT)
#define MCP23017_GPIOB 0x13
#define OLATA 0x14  // output latch register
#define OLATB 0x15

bool         i2c_initialized = 0;
i2c_status_t mcp23017_status = I2C_ADDR;

uint8_t init_mcp23017(void) {
    print("init mcp23017\n");
    mcp23017_status = I2C_ADDR;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        wait_ms(MCP23017_I2C_TIMEOUT);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    // This means: we will read all the bits on GPIOA
    // This means: we will write to the pins 0-4 on GPIOB (in select_rows)
    uint8_t buf[] = {0b11111111, 0b11110000};
    print("before transmit\n");
    mcp23017_status = i2c_write_register(I2C_ADDR, IODIRA, buf, sizeof(buf), MCP23017_I2C_TIMEOUT);
    uprintf("after transmit %i\n", mcp23017_status);
    if (!mcp23017_status) {
        // set pull-up
        // - unused  : on  : 1
        // - input   : on  : 1
        // - driving : off : 0
        // This means: we will read all the bits on GPIOA
        // This means: we will write to the pins 0-4 on GPIOB (in select_rows)
        mcp23017_status = i2c_write_register(I2C_ADDR, GPPUA, buf, sizeof(buf), MCP23017_I2C_TIMEOUT);
        uprintf("after transmit2 %i\n", mcp23017_status);
    }
    return mcp23017_status;
}

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];  // debounced values

static matrix_row_t read_cols(uint8_t row);
static void         unselect_row(uint8_t row);
static void         unselect_rows(void);
static void         unselect_cols(void);
static void         select_row(uint8_t row);

static uint8_t mcp23017_reset_loop;

static void init_mcu_pins(void) {
    unselect_rows();
    unselect_cols();
}

void matrix_init_custom(void) {
    debug_enable = true;
    debug_matrix = true;
    dprint("matrix_init_custom\n");
    // initialize row and col
    init_mcu_pins();
    mcp23017_status = init_mcp23017();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_matrix_row(matrix_row_t current_matrix[], uint8_t index) {
    matrix_row_t temp = read_cols(index);
    if (current_matrix[index] != temp) {
        current_matrix[index] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (mcp23017_status) {  // if there was an error
        if (++mcp23017_reset_loop == 0) {
            // if (++mcp23017_reset_loop >= 1300) {
            // since mcp23017_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            print("trying to reset mcp23017\n");
            mcp23017_status = init_mcp23017();
            if (mcp23017_status) {
                print("right side not responding\n");
            } else {
                print("right side attached\n");
            }
        }
    }

    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) {
        // select rows from left and right hands
        uint8_t left_index  = i;
        uint8_t right_index = i + MATRIX_ROWS_PER_SIDE;

        changed |= store_matrix_row(current_matrix, left_index);
        changed |= store_matrix_row(current_matrix, right_index);

        unselect_rows();
    }

    return changed;
}

static matrix_row_t read_cols(uint8_t row) {
    select_row(row);
    if (row < MATRIX_ROWS_PER_SIDE) {
        pin_t        matrix_col_pins_mcu[MATRIX_COLS_PER_SIDE] = MATRIX_COL_PINS_MCU;
        matrix_row_t current_row_value                         = 0;
        matrix_io_delay();
        // For each col...
        for (uint8_t col_index = 0; col_index < MATRIX_COLS_PER_SIDE; col_index++) {
            // Select the col pin to read (active low)
            uint8_t pin_state = gpio_read_pin(matrix_col_pins_mcu[col_index]);

            // Populate the matrix row with the state of the col pin
            current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
        }
        unselect_row(row);
        return current_row_value;
    } else {
        // we don't need a 30us delay anymore, because selecting a
        // right-hand row requires more than 30us for i2c.
        if (mcp23017_status) {  // if there was an error
            return 0;
        } else {
            // We read all the pins on GPIOA.
            // The initial state was all ones and any depressed key at a given column for the currently selected row will have its bit flipped to zero.
            // The return value is a row as represented in the generic matrix code were the rightmost bits represent the lower columns and zeroes represent non-depressed keys while ones represent depressed keys.
            // Since the pins connected to eact columns are sequential, and counting from zero up (col 5 -> GPIOA0, col 6 -> GPIOA1 and so on), the only transformation needed is a bitwise not to swap all zeroes and ones.
            uint8_t data[] = {0};
            mcp23017_status = i2c_read_register(I2C_ADDR, MCP23017_GPIOA, data, sizeof(data), MCP23017_I2C_TIMEOUT);
            return ~data[0];
        }
    }
}

static void unselect_row(uint8_t row) {
    pin_t matrix_row_pins_mcu[MATRIX_ROWS_PER_SIDE] = MATRIX_ROW_PINS_MCU;
    gpio_set_pin_input_high(matrix_row_pins_mcu[row]);
}

static void unselect_rows(void) {
    // no need to unselect on mcp23017, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction

    // unselect rows on microcontroller
    pin_t matrix_row_pins_mcu[MATRIX_ROWS_PER_SIDE] = MATRIX_ROW_PINS_MCU;
    for (int pin_index = 0; pin_index < MATRIX_ROWS_PER_SIDE; pin_index++) {
        pin_t pin = matrix_row_pins_mcu[pin_index];
        gpio_set_pin_input_high(pin);
    }
}
static void unselect_cols(void) {
    pin_t matrix_col_pins_mcu[MATRIX_COLS_PER_SIDE] = MATRIX_COL_PINS_MCU;
    for (int pin_index = 0; pin_index < MATRIX_COLS_PER_SIDE; pin_index++) {
        pin_t pin = matrix_col_pins_mcu[pin_index];
        gpio_set_pin_input_high(pin);
    }
}

static void select_row(uint8_t row) {
    if (row < MATRIX_ROWS_PER_SIDE) {
        // select on MCU
        pin_t matrix_row_pins_mcu[MATRIX_ROWS_PER_SIDE] = MATRIX_ROW_PINS_MCU;
        pin_t pin                                       = matrix_row_pins_mcu[row];
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    } else {
        // select on mcp23017
        if (mcp23017_status) {  // if there was an error
                                // do nothing
        } else {
            // Select the desired row by writing a byte for the entire GPIOB bus where only the bit representing the row we want to select is a zero (write instruction) and every other bit is a one.
            // Note that the row - MATRIX_ROWS_PER_SIDE reflects the fact that being on the right hand, the columns are numbered from MATRIX_ROWS_PER_SIDE to MATRIX_ROWS, but the pins we want to write to are indexed from zero up on the GPIOB bus.
            uint8_t buf[]   = {0xFF & ~(1 << (row - MATRIX_ROWS_PER_SIDE))};
            mcp23017_status = i2c_write_register(I2C_ADDR, MCP23017_GPIOB, buf, sizeof(buf), MCP23017_I2C_TIMEOUT);
        }
    }
}
