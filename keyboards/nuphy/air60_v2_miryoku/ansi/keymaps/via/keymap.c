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

#include QMK_KEYBOARD_H

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)
#define HOME_X RALT_T(KC_X)

// Right-hand home row mods
#define HOME_DOT RALT_T(KC_DOT)
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

// SpaceFN functionality
#define SPACE_FN LT(5, KC_SPC)

// My layers
#define NUM_N LT(6, KC_N)
#define SYM_M LT(7, KC_M)
#define FUN_COMM LT(8, KC_COMM)
#define MOUSE_ESC LT(9, KC_ESC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// layer 1 Win No mods
[0] = LAYOUT(
	KC_ESC, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 	KC_BSLS,
	MOUSE_ESC,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	            KC_ENT,
	KC_LSFT,	KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,	KC_RSFT,	KC_UP,		KC_DEL,
	KC_LCTL,	KC_LGUI,	KC_LALT,										KC_SPC, 							KC_RALT,	MO(2),   	KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 1 Win
[1] = LAYOUT(
	KC_ESC, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 	KC_BSLS,
	KC_CAPS,	HOME_A,     HOME_S,     HOME_D,     HOME_F,     KC_G,       KC_H,       HOME_J,     HOME_K,     HOME_L,     HOME_SCLN, 	KC_QUOT, 	            KC_ENT,
	KC_LSFT,	KC_Z,   	HOME_X,   	KC_C,  		KC_V,   	KC_B,   	NUM_N,   	SYM_M,   	FUN_COMM,	HOME_DOT,   KC_SLSH,	KC_RSFT,	KC_UP,		KC_DEL,
	KC_LCTL,	KC_LGUI,	KC_LALT,										SPACE_FN, 							KC_RALT,	MO(2),   	KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 2 win fn
[2] = LAYOUT(
	KC_GRV, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	MO(3),	    _______,   	_______,   	_______,  	_______,   	_______,   	_______,   	MO(4),   	RGB_SPD,	RGB_SPI,  	_______,	MO(3),  	RGB_VAI,    _______,
	_______,	_______,	_______,										_______, 							_______,	_______,   	RGB_MOD,	RGB_VAD,    RGB_HUI),

// layer 3 win fn+shift
[3] = LAYOUT(
	SHIFT_GRV, 	KC_BRID,   	KC_BRIU,    _______,  	_______,   	_______,   	_______,   	KC_MPRV,   	KC_MPLY,   	KC_MNXT,  	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	_______,	_______,   	_______,   	RGB_TEST,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,	_______, 	_______,    _______,
	_______,	_______,	_______,										_______, 							_______,	_______,   	_______,	_______,    _______),

// layer 4 function
[4] = LAYOUT(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	_______,    _______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	SIDE_SPD,	SIDE_SPI,  	_______,	_______,  	SIDE_VAI,   _______,
	_______,   	_______,	_______,										_______, 							_______,	_______,   	SIDE_MOD,	SIDE_VAD,   SIDE_HUI),

// layer 5 space_layer
[5] = LAYOUT(
    _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_END,     KC_APP,     _______,    _______,    _______,    _______,
    _______,    KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    _______,                _______,
    _______,    _______,    KC_RALT,    _______,    _______,    _______,    KC_BSPC,    KC_DEL,     _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,                                        _______,                            _______,    _______,    _______,    _______,    _______),

// layer 6 num_layer
[6] = LAYOUT(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_LBRC,    KC_7,       KC_8,       KC_9,       KC_RBRC,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_QUOT,    KC_4,       KC_5,       KC_6,       KC_EQL,     _______,    KC_RSFT,    KC_RCTL,    KC_LALT,    KC_RGUI,    _______,                _______,
    _______,    KC_GRV,     KC_1,       KC_2,       KC_3,       KC_BSLS,    _______,    _______,    _______,    KC_RALT,    _______,    _______,    _______,    _______,
    _______,    _______,    KC_0,                                           KC_MINS,                            _______,    _______,    _______,    _______,    _______),

// layer 7 sym_layer
[7] = LAYOUT(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_LCBR,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RCBR,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_DQUO,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_PLUS,    _______,    KC_RSFT,    KC_RCTL,    KC_LALT,    KC_RGUI,    _______,                _______,
    _______,    KC_TILD,    KC_EXLM,    KC_AT,      KC_HASH,    KC_PIPE,    _______,    _______,    _______,    KC_RALT,    _______,    _______,    _______,    _______,
    _______,    _______,    KC_RPRN,                                        KC_UNDS,                            _______,    _______,    _______,    _______,    _______),

// layer 8 fun_layer
[8] = LAYOUT(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_F12,     KC_F7,      KC_F8,      KC_F9,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_F11,     KC_F4,      KC_F5,      KC_F6,      _______,    _______,    KC_RSFT,    KC_RCTL,    KC_LALT,    KC_RGUI,    _______,                _______,
    _______,    KC_F10,     KC_F1,      KC_F2,      KC_F3,      _______,    _______,    _______,    _______,    KC_RALT,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,                                        _______,                            _______,    _______,    _______,    _______,    _______),

// layer 9
[9] = LAYOUT(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    MS_BTN1,    MS_BTN2,    _______,    _______,    _______,    MS_LEFT,    MS_DOWN,    MS_UP,      MS_RGHT,    _______,                _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    MS_WHLL,    MS_WHLD,    MS_WHLU,    MS_WHLR,    _______,    _______,    _______,
    _______,    _______,    _______,                                        _______,                            _______,    _______,    _______,    _______,    _______)
};


const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, A_16,   B_16,   C_16},      // "Esc"
    {0, A_2,    B_2,    C_2},       // "!1"
    {0, A_3,    B_3,    C_3},       // "@2"
    {0, A_4,    B_4,    C_4},       // "#3"
    {0, A_5,    B_5,    C_5},       // "$4"
    {0, A_6,    B_6,    C_6},       // "%5"
    {0, A_7,    B_7,    C_7},       // "^6"
    {0, A_8,    B_8,    C_8},       // "&7"
    {0, A_9,    B_9,    C_9},       // "*8"
    {0, A_10,   B_10,   C_10},      // "(9"
    {0, A_11,   B_11,   C_11},      // ")0"
    {1, D_1,    E_1,    F_1},       // "_-"
    {1, D_2,    E_2,    F_2},       // "+="
    {1, D_3,    E_3,    F_3},       // "Backsp"
    {0, D_1,    E_1,    F_1},       // "Tab"
    {0, D_2,    E_2,    F_2},       // "Q"
    {0, D_3,    E_3,    F_3},       // "W"
    {0, D_4,    E_4,    F_4},       // "E"
    {0, D_5,    E_5,    F_5},       // "R"
    {0, D_6,    E_6,    F_6},       // "T"
    {0, D_7,    E_7,    F_7},       // "Y"
    {0, D_8,    E_8,    F_8},       // "U"
    {0, D_9,    E_9,    F_9},       // "I"
    {0, D_10,   E_10,   F_10},      // "O"
    {0, D_11,   E_11,   F_11},      // "P"
    {1, G_1,    H_1,    I_1},       // "{["
    {1, G_2,    H_2,    I_2},       // "}]"
    {1, G_3,    H_3,    I_3},       // "|\\"
    {0, G_1,    H_1,    I_1},       // "Caps"
    {0, G_2,    H_2,    I_2},       // "A"
    {0, G_3,    H_3,    I_3},       // "S"
    {0, G_4,    H_4,    I_4},       // "D"
    {0, G_5,    H_5,    I_5},       // "F"
    {0, G_6,    H_6,    I_6},       // "G"
    {0, G_7,    H_7,    I_7},       // "H"
    {0, G_8,    H_8,    I_8},       // "J"
    {0, G_9,    H_9,    I_9},       // "K"
    {0, G_10,   H_10,   I_10},      // "L"
    {0, G_11,   H_11,   I_11},      // ":"
    {1, G_16,   H_16,   I_16},      // "\""
    {1, G_14,   H_14,   I_14},      // "Enter"
    {0, J_1,    K_1,    L_1},       // "Shift"
    {0, J_3,    K_3,    L_3},       // "Z"
    {0, J_4,    K_4,    L_4},       // "X"
    {0, J_5,    K_5,    L_5},       // "C"
    {0, J_6,    K_6,    L_6},       // "V"
    {0, J_7,    K_7,    L_7},       // "B"
    {0, J_8,    K_8,    L_8},       // "N"
    {0, J_9,    K_9,    L_9},       // "M"
    {0, J_10,   K_10,   L_10},      // "<,"
    {0, J_11,   K_11,   L_11},      // ">."
    {1, J_1,    K_1,    L_1},       // "?/"
    {1, J_3,    K_3,    L_3},       // "Shift"
    {1, J_4,    K_4,    L_4},       // "↑"
    {1, G_4,    H_4,    I_4},       // "Del"
    {0, J_16,   K_16,   L_16},      // "Ctrl"
    {0, J_15,   K_15,   L_15},      // "Opt"
    {0, J_14,   K_14,   L_14},      // "Cmd"
    {0, J_13,   K_13,   L_13},      // "Space"
    {0, J_12,   K_12,   L_12},      // "Cmd"
    {1, J_16,   K_16,   L_16},      // "Fn"
    {1, J_13,   K_13,   L_13},      // "←"
    {1, J_12,   K_12,   L_12},      // "↓"
    {1, J_11,   K_11,   L_11},      // "→"

    {1, A_5,    B_5,    C_5},       // logo left
    {1, A_4,    B_4,    C_4},       //
    {1, A_3,    B_3,    C_3},       //
    {1, A_2,    B_2,    C_2},       //
    {1, A_1,    B_1,    C_1},       //

    {1, A_6,    B_6,    C_6},       // logo right
    {1, A_7,    B_7,    C_7},       //
    {1, A_8,    B_8,    C_8},       //
    {1, A_9,    B_9,    C_9},       //
    {1, A_10,   B_10,   C_10}       //
};
