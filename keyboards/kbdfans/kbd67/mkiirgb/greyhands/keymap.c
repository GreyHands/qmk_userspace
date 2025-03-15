#include "_wait.h"
#include "info_config.h"
#include "keycodes.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "send_string_keycodes.h"
#include <avr/pgmspace.h>
#include <print.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include QMK_KEYBOARD_H

#define _MAC 0   // MacOS default layer
#define _WIN 1   // Windows layer
#define _RGB 2   // RGB
#define _APEX 3  // Special layer to test Apex Legends superglide macro
#define _RAISE 4 // RAISE function layer

#define CAPS_LOCK_LED_INDEX 30
//#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255

enum custom_keycodes {
  SUPERGLIDE = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off
    /* macOS layer
     * ,--------------------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  Backspace  | Home |
     * |-------------------------------------------------------------------------------------------+------+
     * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \     | PgUp |
     * |-------------------------------------------------------------------------------------------+------+
     * | MO(_RAISE)  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |   Enter   | PgDw |
     * |-------------------------------------------------------------------------------------------+------+
     * | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   Shift    | Up  | End  |
     * +-------------------------------------------------------------------------┬---┬-------------+------+
     * | LCtrl | LAlt | LGUI |               Space           | MO(_RAISE) | RGUI |   | Left  | Dn  | Rght |
     * `-------------------------------------------------------------------------┘   └-------------+------´
     */

    [_MAC] = LAYOUT_65_ansi_blocker(/* Base */
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,
        MO(_RAISE), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END,
        KC_LCTL, KC_LALT, KC_LGUI, LT(_RAISE, KC_SPC), MO(_RAISE), KC_RGUI, KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    // clang-format on

    // clang-format off
    /* Windows layer
     * ,--------------------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  Backspace  | Home |
     * |-------------------------------------------------------------------------------------------+------+
     * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \     | PgUp |
     * |-------------------------------------------------------------------------------------------+------+
     * | MO(_RAISE)  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |   Enter   | PgDw |
     * |-------------------------------------------------------------------------------------------+------+
     * | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |   Shift    | Up  | End  |
     * +-------------------------------------------------------------------------┬---┬-------------+------+
     * | LCtrl | LGUI | LAlt |               Space          | MO(_RAISE) | RCtrl |   | Left  | Dn  | Rght |
     * `-------------------------------------------------------------------------┘   └-------------+------´
     */

    [_WIN] = LAYOUT_65_ansi_blocker(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,
        MO(_RAISE), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(_RAISE), KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT

    ),
    // clang-format on

    // clang-format off
    /* Layer 2
     * ,----------------------------------------------------------------------------------------------------------------------------------.
     * | Esc |  TG(_LAYER1)  |  TG(_LAYER2) |  		 |     | 	   |     |     | 	   |     |     | 	   |  TG(_BASE) |      |     | 		 | 		  |
     * |-------------------------------------------------------------------------------------------+--------------------------------------+
     * |     | RGB_TOG | RGB_MOD+ | RGB_HUI | RGB_UHD | RGB_SAI | RGB_SAD | RBG_VAI | RGB_VAD |      |  	|     |      |  BOOT_DFU  |     |
     * |-------------------------------------------------------------------------------------------+-------------------------------------------+
     * | 		 | RGB_SPI | RGB_SPD  |   		  |  	    |  		  | 		    |			  |     		|      |   	|     | 			 		 | EPRM RESET | 	  | 	 |
     * |-------------------------------------------------------------------------------------------+------+------------------------------------+
     * |           |     |     |     |     |     |     |     |     |     |     |             |     |      |
     * +-------------------------------------------------------------------------┬---┬-------------+------+
     * |     |  	 |     |                                   |     |     |       |   |      |      |      |
     * `-------------------------------------------------------------------------┘   └-------------+------´
     *
     * ,----------------------------------------------------------------------------------------------------------.
     * | ` ~ |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10  |  F11 |  F12  | Del  |       |
     * |-------------------------------------------------------------------------------------------+--------------+
     * | CAPS|      |      |      | 	   | 		  | 	   |      |      |      |  		  |  	 	 |  	   |TG(WIN)| 		  |
     * |-------------------------------------------------------------------------------------------+------+-------+
     * | 		 |      |      |      |  	   |  	  |  	   |  	  |  	   |  	  |  		  |  	   |  		 |      |
     * |-------------------------------------------------------------------------------------------+------+
     * |      |     |   	 |      |   	 |      |      |      |      |      |      |TG(RGB)|  Vol+ | Mute |
     * +-------------------------------------------------------------------------┬---┬-------------+------+
     * | 		  | 	  | MO(_LAYER2) |                                  |      |    |   |     |  Vol- |      |
     * `-------------------------------------------------------------------------┘   └-------------+------´
     */

    [_RAISE] = LAYOUT_65_ansi_blocker(/* FN */
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_NO,
        KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, TG(_APEX), TG(_WIN), KC_NO,
        KC_NO, KC_NO, RGB_SPD, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(_RGB), KC_VOLU, KC_MUTE,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_NO
    ),
    // clang-format on

    // clang-format off
    /* Layer 3
     * ,----------------------------------------------------------------------------------------------------------------------------------.
     * | Esc |  TG(_LAYER1)  |  TG(_LAYER2) |  		 |     | 	   |     |     | 	   |     |     | 	   |  TG(_BASE) |      |     | 		 | 		  |
     * |-------------------------------------------------------------------------------------------+--------------------------------------+
     * |     | RGB_TOG | RGB_MOD+ | RGB_HUI | RGB_UHD | RGB_SAI | RGB_SAD | RBG_VAI | RGB_VAD |      |  	|     |      |  BOOT_DFU  |     |
     * |-------------------------------------------------------------------------------------------+-------------------------------------------+
     * | 		 | RGB_SPI | RGB_SPD  |   		  |  	    |  		  | 		    |			  |     		|      |   	|     | 			 		 | EPRM RESET | 	  | 	 |
     * |-------------------------------------------------------------------------------------------+------+------------------------------------+
     * |           |     |     |     |     |     |     |     |     |     |     |             |     |      |
     * +-------------------------------------------------------------------------┬---┬-------------+------+
     * |     |  	 |     |                                   |     |     |       |   |      |      |      |
     * `-------------------------------------------------------------------------┘   └-------------+------´
     */

    /* RGB
     * ,----------------------------------------------------------------------------------------------------------------------------------.
     * |     |       |      |  		 |     | 	   |     |     | 	   |     |     | 	   |     |      |     | 		 | 		  |       |
     * |-------------------------------------------------------------------------------------------+--------------------------------------+
     * |     | RGB_TOG | RGB_MOD+ | RGB_HUI | RGB_UHD | RGB_SAI | RGB_SAD | RBG_VAI | RGB_VAD |   |  	|     |      |  BOOT_DFU  |       |
     * |----------------------------------------------------------------------------------------------------------------------------------+
     * | 		 | RGB_SPI | RGB_SPD  |   	|	   |	  |     |	  | 		|      |     	|     |  	|  	  |                       |
     * |-------------------------------------------------------------------------------------------+------+-------------------------------+
     * |         |         |          |       |          |       |        |        |        |       |      |  TG(RGB)   |        |          |
     * +-------------------------------------------------------------------------┬---┬-------------+--------------------------------------+
     * |         |         |          |                                             |       |      |        |         |        |          |
     * `----------------------------------------------------------------------------┘---------------        └-+---------------------------´
     */

    [_RGB] = LAYOUT_65_ansi_blocker(/* FN */
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, RGB_SPI, RGB_SPD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(_RGB), KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    // clang-format on

    // clang-format off
    [_APEX] = LAYOUT_65_ansi_blocker(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,
        MO(_RAISE), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END,
        KC_LCTL, SUPERGLIDE, KC_LALT, KC_SPC, MO(_RAISE), KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT

    ),
    // clang-format on

};

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)

#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#else
#define CAPS_LOCK_MAX_BRIGHTNESS 0xFF
#endif

#ifdef RGB_MATRIX_VAL_STEP
#define CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#else
#define CAPS_LOCK_VAL_STEP 8
#endif

bool rgb_matrix_indicators_user(void) {
  switch (get_highest_layer(layer_state)) {
  case _MAC:
    break;
  case _RAISE:
    rgb_matrix_set_color(29, 255, 0, 0);
    break;
  case _WIN:
    rgb_matrix_set_color(43, 255, 0, 0);
    break;
  case _RGB:
    // rgb_matrix_set_color_all(0,0,0);
    // rgb_matrix_set_color(6, 204, 255, 204);
    // rgb_matrix_set_color(6, 255, 0, 0);
    rgb_matrix_set_color(57, 255, 0, 0);
    break;
  case _APEX:
    rgb_matrix_set_color(66, 255, 0, 0);
    break;
  default:
    break;
  }

  if (host_keyboard_led_state().caps_lock) {
    uint8_t b = rgb_matrix_get_val();
    if (b < CAPS_LOCK_VAL_STEP) {
      b = CAPS_LOCK_VAL_STEP;
    } else if (b < (CAPS_LOCK_MAX_BRIGHTNESS - CAPS_LOCK_VAL_STEP)) {
      b += CAPS_LOCK_VAL_STEP; // one step more than current brightness
    } else {
      b = CAPS_LOCK_MAX_BRIGHTNESS;
    }
    // uint8_t b = 255;
    rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, b, b,
                         b); // white, with the adjusted brightness
  }

  return true;
}

uint8_t randomNumber(uint8_t from, uint8_t to) {
  uint8_t lower = from;
  uint8_t upper = to;

  uint8_t rval = TCNT0 + TCNT1 + TCNT3 + TCNT4;
  // uint8_t delay = rval % (upper + 1 - lower) + lower;

  return rval % (upper - lower + 1) + lower;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t delay = 10;
  uint8_t delays[7] = {7, 8, 9, 10, 11};
  uint8_t len = sizeof(delays) / sizeof(delays[0]);

  // Draw a random number to see if this should be a successfull superglide or
  // not
  uint8_t expectation = 75;
  uint8_t chance = randomNumber(1, 100);

  // int  len = 128;
  // char str[len];
  // snprintf(str, len, "Upper: %d\nLower: %d\nrandom: %d\ndelay: %d\n", upper,
  // lower, rval, delay);

  uint8_t sumOfWeight = 0;
  for (uint8_t i = 0; i < len - 1; i++) {
    sumOfWeight += delays[i];
  }

  uint8_t a;

  uint8_t rval = randomNumber(7, sumOfWeight);

  switch (keycode) {
  case SUPERGLIDE:
#ifdef CONSOLE_ENABLE
    uprintf("Superglide chance: %d%% vs expectation %d%%\n", chance,
            expectation);
#endif

    if (chance > expectation) {
      break;
    }

#ifdef CONSOLE_ENABLE
    uprintf("Calculating delay...\n");
#endif

    if (record->event.pressed) {
      a = 0;

      for (uint8_t i = 0; i < len - 1; i++) {
        uint8_t weight = delays[i];
#ifdef CONSOLE_ENABLE
        uprintf("weight: %d\n", weight);
#endif

        if (rval <= weight) {
#ifdef CONSOLE_ENABLE
          uprintf("rval(%d) <= weight(%d)\n", rval, weight);
#endif
          delay = delays[a];
          break;
        } else {
          a++;
#ifdef CONSOLE_ENABLE
          uprintf("rval(%d) > weight(%d)\n", rval, weight);
#endif

          rval = rval - weight;

#ifdef CONSOLE_ENABLE
          uprintf("rval(%d) > weight(%d) - a: %d\n", rval, weight, a);
#endif

          if (a >= len) {
            a = 0;
          }
        }
      }

      SEND_STRING(SS_DOWN(X_SPC));
      wait_ms(delay);
      SEND_STRING(SS_DOWN(X_V) SS_UP(X_SPC) SS_UP(X_V));
#ifdef CONSOLE_ENABLE
      uprintf("Generated delay %u - rval: %d\n", delay, rval);
#endif
    }
    break;
  }

  return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable = true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}

#endif
