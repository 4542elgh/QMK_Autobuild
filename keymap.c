/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
		_NUM,
		_FN,
};

enum {
    TD_ESC_CAPS,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define NAV      MO(_NAV)
#define SYM      MO(_SYM)
#define NUM      MO(_NUM)
#define QTY      TO(_QWERTY)

/* MOD TAP */
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)

/* Macros  */
enum custom_keycodes {
	ScreenShot = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ScreenShot:
        if (record->event.pressed) {
					/* HOLD DOWN WIN + SHIFT THEN PRESS S */
					SEND_STRING(SS_LGUI(SS_LSFT("s")));
        } else {
            // when keycode ScreenShot is released
        }
        break;
    }
    return true;
};

enum {
	TD_1_F1,
	TD_2_F2,
	TD_3_F3,
	TD_4_F4,
	TD_5_F5,
	TD_6_F6,
	TD_7_F7,
	TD_8_F8,
	TD_9_F9,
	TD_0_F10,
	TD_LRBRC,
	TD_LRPRN,
	TD_HOMEEND,
	TD_FBSLASH,
	TD_ATAMP,
	TD_QQST,
	TD_SSLASH,
	TD_BBSLASH,
	TD_NAVNUM
};

/* This is tap dance for layers, layers are defined in the enum above, tap once will switch to nav layer, tap any other amount of time will go to num */
void td_nav_num_finished(qk_tap_dance_state_t *state, void *user_data)
{
    if (state->count == 1) {
        layer_on(1);
    } else if (state->count == 2){
        layer_on(3);
		} else {
        layer_on(4);
		}
}

void td_nav_num_reset(qk_tap_dance_state_t *state, void *user_data)
{
    if (state->count == 1) {
        layer_off(1);
    } else if (state->count == 2){
        layer_off(3);
    } else {
        layer_off(4);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_1_F1] = ACTION_TAP_DANCE_DOUBLE(KC_1,KC_F1),
	[TD_2_F2] = ACTION_TAP_DANCE_DOUBLE(KC_2,KC_F2),
	[TD_3_F3] = ACTION_TAP_DANCE_DOUBLE(KC_3,KC_F3),
	[TD_4_F4] = ACTION_TAP_DANCE_DOUBLE(KC_4,KC_F4),
	[TD_5_F5] = ACTION_TAP_DANCE_DOUBLE(KC_5,KC_F5),
	[TD_6_F6] = ACTION_TAP_DANCE_DOUBLE(KC_6,KC_F6),
	[TD_7_F7] = ACTION_TAP_DANCE_DOUBLE(KC_7,KC_F7),
	[TD_8_F8] = ACTION_TAP_DANCE_DOUBLE(KC_8,KC_F8),
	[TD_9_F9] = ACTION_TAP_DANCE_DOUBLE(KC_9,KC_F9),
	[TD_0_F10] = ACTION_TAP_DANCE_DOUBLE(KC_0,KC_F10),
	[TD_LRBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC,KC_RBRC),
	[TD_LRPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN,KC_RPRN),
	[TD_HOMEEND] = ACTION_TAP_DANCE_DOUBLE(KC_HOME,KC_END),
	[TD_FBSLASH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH,KC_BSLS),
	[TD_ATAMP] = ACTION_TAP_DANCE_DOUBLE(KC_AT,KC_AMPR),
	[TD_QQST] = ACTION_TAP_DANCE_DOUBLE(KC_Q,KC_QUES),
	[TD_SSLASH] = ACTION_TAP_DANCE_DOUBLE(KC_S,KC_SLSH),
	[TD_BBSLASH] = ACTION_TAP_DANCE_DOUBLE(KC_B,KC_BSLS),
	[TD_NAVNUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_nav_num_finished,td_nav_num_reset)
};



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,--------------------------------------------.                                       ,--------------------------------------------.
 * |  Tab   |TD(Q/?)|   W  |   E  |   R  |   T  |                                       |   Y  |   U  |   I  |   O  |   P   |  MUTE  |
 * |--------+-------+------+------+------+------|                                       |------+------+------+------+-------+--------|
 * |Esc/Ctrl|   A   |TD(S/)|   D  |   F  |   G  |                                       |   H  |   J  |   K  |   L  | ;  :  |  ' "   |
 * |--------+-------+------+------+------+------+---------------------.  ,--------------+------+------+------+------+-------+--------|
 * | LShift |   Z   |   X  |   C  |   V  |TD(B\)| TD([{/}] |  SS      |  |      |TD((/))|   N  |   M  | ,  < | . >  |       |        |
 * `-----------------------+------+------+------+----------+----------|  |------+-------+------+------+------+-----------------------'
 *                         |      | LGUI | LAlt |  ENTER   |TD(NAVNUM)|  | Sym  |       | SPC  | BSPC |  DEL |
 *                         `------------------------------------------'  `-----------------------------------'
 */
	  /* MODDED */
    [_QWERTY] = LAYOUT(
     KC_TAB  , TD(TD_QQST),  KC_W, KC_E   , KC_R   , KC_T   ,                                               KC_Y  ,  KC_U  ,   KC_I ,   KC_O , KC_P    , KC_KB_MUTE,
     CTL_ESC , KC_A       ,  KC_S, KC_D   , KC_F   , KC_G   ,                                               KC_H  ,  KC_J  ,   KC_K ,   KC_L , KC_SCLN , KC_QUOTE  ,
     KC_LSFT , KC_Z       ,  KC_X, KC_C   , KC_V   , KC_B   , TD(TD_LRBRC), NUM , ScreenShot, TD(TD_LRPRN), KC_N  ,  KC_M  , KC_COMM, KC_DOT , _______ , _______   ,
                                   _______, KC_LGUI, KC_LALT, KC_ENT      , NAV , SYM       , _______     , KC_SPC, KC_BSPC, KC_DEL
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-----------------------------------------------.
 * |        |      |      |      |      |      |                              | HOME/END |      |  PGU |      |      |        |
 * |--------+------+------+------+------+------|                              |----------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | ←        |  ↓   |   ↑  |   →  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+----------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |          |  PGD |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+----------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |          |      |      |
 *                        `----------------------------------'  `--------------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     TD(TD_HOMEEND), _______, KC_PGUP, _______, _______, _______, 
      _______, _______, _______, _______, _______, _______,                                     KC_LEFT       , KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______       , KC_PGDN, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______       , _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,------------------------------------------.                              ,-----------------------------------------.
 * |      |       |      |   !  |      |   `  |                              |      |      |      |      |   %  |      |
 * |------+-------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |TD(@/&)|  /?  |   $  |      |      |                              |   #  |      |      |      |      |      |
 * |------+-------+------+------+------+------+-------------.  ,------+-------------+------+------+------+------+------|
 * |      |       |      |   ^  |      |  \ | |  +=  |  -_  |  |  *   |  /   |      |      |      |      |      |      |
 * `---------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                       |      |      |      |  +   |  _   |  |      |      |      |      |      |
 *                       `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     _______ , _______     , _______ , KC_EXLM , _______ , KC_GRV  ,                                     _______ , _______ , _______ , _______ ,KC_PERC , _______, 
  	 _______ , TD(TD_ATAMP), KC_SLSH , KC_DLR  , _______ , _______ ,                                     KC_HASH , _______ , _______ , _______ ,_______ , _______,
     _______, _______      , _______ , KC_CIRC , _______ , KC_BSLS , KC_EQL , KC_MINS, KC_ASTR, KC_SLSH, _______ , _______ , _______ , _______ ,_______ , _______,
                                       _______ , _______ , _______ , KC_PPLS, KC_UNDS, _______, _______, _______ , _______ , _______
    ),

/*
 * num layer: numbers pad only
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  7   |  8   |  9   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |  4   |  5   |  6   |      |        |
 * |--------+------+------+------+------+------+-------------.  ,------+-------------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  1   |  2   |  3   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |  0   |  0   |  .   |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_7, KC_8, KC_9   , _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     KC_4, KC_5, KC_6   , _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2, KC_3   , KC_PDOT, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, KC_0, KC_0, _______
    ),

/*
 * FN layer: Function keys only
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  F7  |  F8  |  F9  |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |  F4  |  F5  |  F6  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,------+-------------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | F10  |  F10 |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_F7  , KC_F8 , KC_F9, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     KC_F4  , KC_F5 , KC_F6, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F1  , KC_F2 , KC_F3, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, KC_F10 , KC_F10, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
// 
   //  [_LAYERINDEX] = LAYOUT(
     //  _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
     //  _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
     //  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                //  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
   //  ),
};

#ifdef ENCODER_ENABLE
static uint8_t  encoder_state[2] = {0};
static keypos_t encoder_ccw[2]   = {{0, 0}, {0, 1}};
static keypos_t encoder_cw[2]    = {{1, 0}, {1, 1}};

void encoder_action_unregister(void) {
    for (int index = 0; index < 2; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t){.key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index], .pressed = false, .time = (timer_read() | 1)};
            encoder_state[index]     = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t){.key = clockwise ? encoder_cw[index] : encoder_ccw[index], .pressed = true, .time = (timer_read() | 1)};
    encoder_state[index]     = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_user(void) { encoder_action_unregister(); }

bool encoder_update_user(uint8_t index, bool clockwise) {
    /* encoder_action_register(index, clockwise); */
		/* Each step is 3 volume up or down */
		/* Be aware that the rotarty encoder on slave side of the keyboard is reversed */
		if (clockwise) {
			tap_code(KC_VOLD);
			tap_code(KC_VOLD);
			tap_code(KC_VOLD);
		}
		else {
			tap_code(KC_VOLU);
			tap_code(KC_VOLU);
			tap_code(KC_VOLU);
		}
    return false;
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);

				/* This is based on the layer enum defined at the beginning of the file */
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case 3:
                oled_write_P(PSTR("Num\n"), false);
                break;
            case 4:
                oled_write_P(PSTR("FN\n"), false);
                break;
        }

        // Host Keyboard LED Status
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
			  /* Slave side OLED */
        static const char PROGMEM kyria_logo[] = {
					// 'Avicii Logo', 128x64px
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0xfc, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0xfc, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x78, 0x3c, 0x04, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0x3c, 0x1c, 0x1c, 0x0e, 0x0e, 0x0e, 0x1e, 0x1c, 0x3c, 0x78, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xf0, 0x78, 0x3e, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f, 0x7f, 0xff, 0xf0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf0, 0x70, 0x38, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x07, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif
