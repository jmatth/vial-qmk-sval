/*
Copyright 2023 Morgan Venable @_claussen

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

#include "../keymap_support.c"
#include "keycodes.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>
#include "svalboard.h"

#define LAYER_COLOR(name, color) rgblight_segment_t const (name)[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, color})

LAYER_COLOR(layer0_colors, HSV_GREEN); // NORMAL
LAYER_COLOR(layer1_colors, HSV_ORANGE); // FUNC
LAYER_COLOR(layer2_colors, HSV_AZURE); // NAS
LAYER_COLOR(layer3_colors, HSV_CORAL); // FKEYS
LAYER_COLOR(layer4_colors, HSV_YELLOW); // use for NORMAL hold?
LAYER_COLOR(layer5_colors, HSV_TEAL); // use for FUNC hold?
LAYER_COLOR(layer6_colors, HSV_RED); // use for NAS hold 
LAYER_COLOR(layer7_colors, HSV_RED);
LAYER_COLOR(layer8_colors, HSV_PINK);
LAYER_COLOR(layer9_colors, HSV_PURPLE);
LAYER_COLOR(layer10_colors, HSV_CORAL);
LAYER_COLOR(layer11_colors, HSV_SPRINGGREEN);
LAYER_COLOR(layer12_colors, HSV_TEAL);
LAYER_COLOR(layer13_colors, HSV_TURQUOISE);
LAYER_COLOR(layer14_colors, HSV_YELLOW);
LAYER_COLOR(layer15_colors, HSV_MAGENTA); // MBO
#undef LAYER_COLOR

const rgblight_segment_t*  const __attribute((weak))sval_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0_colors, layer1_colors, layer2_colors, layer3_colors,
    layer4_colors, layer5_colors, layer6_colors, layer7_colors,
    layer8_colors, layer9_colors, layer10_colors, layer11_colors,
    layer12_colors, layer13_colors, layer14_colors, layer15_colors
);

layer_state_t default_layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, 0));
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  for (int i = 0; i < RGBLIGHT_LAYERS; ++i) {
      rgblight_set_layer_state(i, layer_state_cmp(state, i));
  }

  layer_state_t layer_state_set_user(layer_state_t state) {
  // checks highest layer other than target layer
  switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
      case _LAYER5 ... _LAYER14:
          // remove_auto_mouse_target must be called to adjust state *before* setting enable
          state = remove_auto_mouse_layer(state, false);
          set_auto_mouse_enable(false);
          break;
      default:
          set_auto_mouse_enable(true);
          break;
  }

  return state;
}



void keyboard_post_init_user(void) {
  // Customise these values if you need to debug the matrix
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
  rgblight_layers = sval_rgb_layers;
}

enum layer {
    NORMAL,
    FUNC,
    NAS,
    BOARD_CONFIG,
    MBO = MH_AUTO_BUTTONS_LAYER,
};

const uint16_t PROGMEM keymaps[DYNAMIC_KEYMAP_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT(
        /*Center           North           East            South           West*/

        /*R1*/ KC_J,            KC_U,           KC_QUOTE,       KC_M,           KC_H, XXXXXXX,
        /*R2*/ KC_K,            KC_I,           KC_COLON,       KC_COMMA,       KC_Y, XXXXXXX,
        /*R3*/ KC_L,            KC_O,           KC_LGUI,        KC_DOT,         KC_N, XXXXXXX,
        /*R4*/ KC_SEMICOLON,    KC_P,           KC_BSLS,        KC_SLASH,       KC_RBRC, XXXXXXX,

        /*L1*/ KC_F,            KC_R,           KC_G,           KC_V,           KC_DOUBLE_QUOTE, XXXXXXX,
        /*L2*/ KC_D,            KC_E,           KC_T,           KC_C,           KC_GRAVE, XXXXXXX,
        /*L3*/ KC_S,            KC_W,           KC_B,           KC_X,           KC_ESC, XXXXXXX,
        /*L4*/ KC_A,            KC_Q,           KC_LBRC,        KC_Z,           KC_DEL, XXXXXXX,

        /*     Down            Pad            Up             Nail           Knuckle    DoubleDown*/
        /*RT*/ MO(NAS),         KC_SPACE,       TO(FUNC),       KC_BSPC,        KC_LALT,     XXXXXXX,
        /*LT*/ KC_LSFT,         KC_ENTER,       TO(NORMAL),          KC_TAB,         KC_LCTL,     KC_CAPS
        ),

    [FUNC] = LAYOUT(
        /*Center           North           East            South           West*/
        /*R1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT, XXXXXXX,
        /*R2*/ XXXXXXX,         KC_F8,          XXXXXXX,        KC_F7,          KC_END, XXXXXXX,
        /*R3*/ KC_PSCR,         KC_F10,         KC_LGUI,        KC_F9,          KC_INS, XXXXXXX,
        /*R4*/ KC_PAUSE,        KC_PGUP,        KC_F12,         KC_PGDN,        KC_F11, XXXXXXX,

        /*L1*/ KC_HOME,         KC_UP,          KC_RIGHT,       KC_DOWN,        KC_LEFT, XXXXXXX,
        /*L2*/ XXXXXXX,         KC_F6,          XXXXXXX,        KC_F5,          XXXXXXX, XXXXXXX,
        /*L3*/ XXXXXXX,         KC_F4,          XXXXXXX,        KC_F3,          KC_ESC, XXXXXXX,
        /*L4*/ TO(BOARD_CONFIG), KC_F2,         XXXXXXX,        KC_F1,          KC_DEL, XXXXXXX,

        /*     Down            Pad            Up             Nail           Knuckle    DoubleDown*/
        /*RT*/ MO(NAS),         KC_SPACE,       _______,       KC_BSPC,      KC_LALT, _______,
        /*LT*/ KC_LSFT,       KC_ENTER,         _______, KC_TAB,         KC_LCTL, _______
        ),

    [NAS] = LAYOUT(
        /*Center           North           East            South           West*/
        /*R1*/ KC_7,            KC_AMPR,        KC_UNDS,        KC_KP_PLUS,     KC_6, XXXXXXX,
        /*R2*/ KC_8,            KC_KP_ASTERISK, KC_COLON,       KC_COMMA,       KC_CIRCUMFLEX, XXXXXXX,
        /*R3*/ KC_9,            KC_LPRN,        KC_LGUI,        KC_DOT,         KC_SEMICOLON, XXXXXXX,
        /*R4*/ KC_0,            KC_RPRN,        XXXXXXX,        KC_QUES,        KC_RBRC, XXXXXXX,

        /*L1*/ KC_4,            KC_DOLLAR,      KC_5,           KC_MINUS,       KC_SLASH, XXXXXXX,
        /*L2*/ KC_3,            KC_HASH,        KC_GT,          KC_PERCENT,     KC_LT, XXXXXXX,
        /*L3*/ KC_2,            KC_AT,          XXXXXXX,        KC_X,           KC_ESC, XXXXXXX,
        /*L4*/ KC_1,            KC_EXCLAIM,     KC_TILDE,       KC_EQUAL,       KC_DEL, XXXXXXX,

        /*     Down            Pad            Up             Nail           Knuckle    DoubleDown*/
        /*RT*/ MO(NAS),         KC_SPACE,       _______,       KC_BSPC,        KC_LALT, _______,
        /*LT*/ KC_LSFT,         KC_ENTER,       _______,        KC_TAB,         KC_LCTL, _______
        ),

    [BOARD_CONFIG] = LAYOUT(
        /*                  Center              North               East                South               West                (XXX)               */
        /* R1 */            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            -1,
        /* R2 */            KC_TRNS,            RGB_VAI,            KC_TRNS,            RGB_VAD,            KC_TRNS,            -1,
        /* R3 */            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            -1,
        /* R4 */            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            -1,
        
        /* L1 */            SV_OUTPUT_STATUS,       KC_TRNS,             KC_TRNS,         KC_TRNS,            KC_TRNS,            -1,
        /* L2 */            SV_RIGHT_SCROLL_TOGGLE, SV_RIGHT_DPI_INC,    KC_TRNS,         SV_RIGHT_DPI_DEC,   KC_TRNS,            -1,
        /* L3 */            SV_LEFT_SCROLL_TOGGLE,  SV_LEFT_DPI_INC,     KC_TRNS,         SV_LEFT_DPI_DEC,    KC_TRNS,            -1,
        /* L4 */            SV_MH_CHANGE_TIMEOUTS,  SV_TOGGLE_ACHORDION, KC_TRNS,         KC_TRNS,            KC_TRNS,            -1,
        
        /*                  Down                Pad                 Up                  Nail                Knuckle             Double Down         */
        /* RT */            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,
        /* LT */            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS
      ),

    [MBO] = LAYOUT(
        /*Center           North           East            South           West*/
        /*R1*/ KC_BTN1,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, XXXXXXX,
        /*R2*/ KC_BTN3,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, XXXXXXX,
        /*R3*/ KC_BTN2,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, XXXXXXX,
        /*R4*/ SV_RECALIBRATE_POINTER,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, XXXXXXX,
        /*L1*/ KC_BTN1,        KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS, XXXXXXX,
        /*L2*/ KC_BTN3,        KC_TRNS,       KC_TRNS,       SV_SNIPER_2,        KC_TRNS, XXXXXXX,
        /*L3*/ KC_BTN2,        KC_TRNS,       KC_TRNS,       SV_SNIPER_3,        KC_TRNS, XXXXXXX,
        /*L4*/ SV_RECALIBRATE_POINTER, KC_TRNS, KC_TRNS,       SV_SNIPER_5,      KC_TRNS, XXXXXXX,
        /*     Down            Pad            Up             Nail           Knuckle    DoubleDown*/
        /*RT*/ KC_TRNS,        KC_BTN1,       KC_TRNS,       KC_BTN2,       KC_BTN3,   KC_TRNS,
        /*LT*/ KC_TRNS,        KC_BTN1,       KC_TRNS,       KC_BTN2,       KC_BTN3,   KC_TRNS
        )

};

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
    if (tap_hold_record->event.key.row == 0 || tap_hold_record->event.key.row == 5 ||
        other_record->event.key.row    == 0 || other_record->event.key.row    == 5) {
        return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

enum custom_keycodes {
    M_KEYBOARD = SV_SAFE_RANGE,
    M_ON,
    M_ENT,
    M_ION,
    M_UEN,
    M_MENT,
    M_THE,
    M_DOT_SLASH, aann
};

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case KC_NO:
            return false;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            return false;
    }

    return true;  // Other keys can be repeated.
}

bool process_magic_repeat(uint16_t keycode, keyrecord_t* record) {
    uint16_t layer = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    bool magic = false;
    bool shift = false;
    if (layer > 40) {
        shift = true;
        magic = layer >= 42;
        layer = 0;
    } else if (layer > 20) {
        layer -= 20;
        magic = true;
    }
    if (record->tap.count && record->event.pressed) {
        tap_code16(magic ? get_alt_repeat_key_keycode() : get_last_keycode());
    } else if (record->event.pressed) {
        if (shift) {
            register_mods(MOD_BIT_LSHIFT);
        } else {
            layer_on(layer);
        }
    } else {
        if (shift) {
            unregister_mods(MOD_BIT_LSHIFT);
        } else {
            layer_off(layer);
        }
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            return process_magic_repeat(keycode, record);
            break;
        case M_ON:
            if (record->event.pressed) {
                SEND_STRING("on");
            }
            break;
        case M_ENT:
            if (record->event.pressed) {
                SEND_STRING("ent"); break;
            }
            break;
        case M_ION:
            if (record->event.pressed) {
                SEND_STRING("ion"); break;
            }
            break;
        case M_UEN:
            if (record->event.pressed) {
                SEND_STRING("uen"); break;
            }
            break;
        case M_MENT:
            if (record->event.pressed) {
                SEND_STRING("ment"); break;
            }
            break;
        case M_THE:
            if (record->event.pressed) {
                SEND_STRING("the"); break;
            }
            break;
        case M_DOT_SLASH:
            if (record->event.pressed) {
                SEND_STRING("./"); break;
            }
            break;
    }
    return true;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_A: return KC_O;
        case KC_C: return KC_Y;
        case KC_D: return KC_Y;
        case KC_E: return KC_U;
        case KC_G: return KC_Y;
        case KC_I: return M_ON;
        case KC_L: return KC_K;
        case KC_M: return M_ENT;
        case KC_N: return M_ION;
        case KC_O: return KC_A;
        case KC_P: return KC_H;
        case KC_Q: return M_UEN;
        case KC_R: return KC_L;
        case KC_S: return KC_K;
        case KC_T: return M_MENT;
        case KC_U: return KC_E;
        case KC_Y: return KC_P;
        case KC_SPC: return M_THE;
        case KC_DOT: return M_DOT_SLASH;
    }

    return KC_TRNS;  // Defer to default definitions.
}
