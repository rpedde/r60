/* Copyright 2017 Ron Pedde <ron@pedde.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "r60.h"

#define _B 0  /* Base Layer */
#define _F 1  /* Func Layer */

#define ______ KC_TRNS

// Used for SHIFT_ESC
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer
     * ,-------------------------------------------------------------------------.
     * |Esc~|   1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   -|   =|Backspac|
     * |-------------------------------------------------------------------------|
     * | Tab  |   Q|   W|   E|   R|   T|   Y|   U|   I|   O|   P|   [|   ]|   \  |
     * |-------------------------------------------------------------------------|
     * | Ctrl  |   A|   S|   D|   F|   G|   H|   J|   K|   L|   ;|   '| Return   |
     * `----,---------------------------------------------------------------,----'
     *      |Shift|   Z|   X|   C|   V|   B|   N|   M|   ,|   .|   /| Shift |
     *      |---------------------------------------------------------------|
     *      |Ctrl |Meta |Supr |    FN   |  Space  |Meta |Left| Rt | Up |Down|
     *      `---------------------------------------------------------------'
     */

    [_B] = KEYMAP( /* Base */
        F(0),    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,  KC_6,  KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,  KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
        KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,  KC_H,  KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,  KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
        KC_LCTL, KC_LALT, KC_LGUI,         MO(_F), KC_SPC,       KC_RALT, KC_LEFT, KC_RGHT, KC_UP,   KC_DOWN \
        ),
    /* Funcation
     * ,-------------------------------------------------------------------------.
     * |   `|  F1|  F2|  F3|  F4|  F5|  F6|  F7|  F8|  F9| F10| F11| F12| Del    |
     * |-------------------------------------------------------------------------|
     * |      |    |    |    |    |    |    |    |    |    |    |    |    |      |
     * |-------------------------------------------------------------------------|
     * |       |    |    |    |    |    |    |    |    |    |    |    |          |
     * `----,---------------------------------------------------------------,----'
     *      |     |    |    |    |    |    |    |    |    |    |    |       |
     *      |---------------------------------------------------------------|
     *      |     |     |     |         |         |     |HOME|END |PGUP|PGDN|
     *      `---------------------------------------------------------------'
     */

    [_F] = KEYMAP(
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_DEL, \
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______,         ______, ______,         ______, KC_HOME,KC_END, KC_PGUP,KC_PGDN \
        ),
};

enum function_id {
    SHIFT_ESC,
    SHIFT_LEFT,
    SHIFT_RIGHT,
    SHIFT_UP,
    SHIFT_DOWN,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(SHIFT_ESC),
};

void shift_do(keyrecord_t *record, uint8_t unshifted, uint8_t shifted) {
    static uint8_t is_shifted;

    if(record->event.pressed) {
        is_shifted = get_mods() & MODS_SHIFT_MASK;

        if (is_shifted) {
            add_key(shifted);
        } else {
            add_key(unshifted);
        }
    } else {
        if (is_shifted) {
            del_key(shifted);
        } else {
            del_key(unshifted);
        }
    }
    send_keyboard_report();
}


void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
    case SHIFT_ESC:
        shift_do(record, KC_ESC, KC_GRV);
        break;
    }
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
    case 0:
        if (record->event.pressed) {
            register_code(KC_RSFT);
        } else {
            unregister_code(KC_RSFT);
        }
        break;
    }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void led_set_user(uint8_t usb_led) {

}
