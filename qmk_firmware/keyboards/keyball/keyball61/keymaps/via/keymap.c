/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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
#include "quantum.h"

void dance_comma(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_COMM);
    } else if (state->count == 2) {
        tap_code (KC_DOT);
    } else if (state->count == 3) {
        tap_code(KC_MINS);
    } else {
        reset_tap_dance (state);
    }
}


enum combos {
  CCLK,
  wue,
  whidari,
  wmigi,
  wsita,
  fd,
  jk,
  fg,
  fmouse,
};

const uint16_t PROGMEM cckl_combo[] = {KC_BTN1, KC_L, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_BSPC, KC_I, COMBO_END};
const uint16_t PROGMEM hidari_combo[] = {KC_BSPC, KC_BTN1, COMBO_END};
const uint16_t PROGMEM migi_combo[] = {KC_BSPC, KC_L, COMBO_END};
const uint16_t PROGMEM sita_combo[] = {KC_BSPC, RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM fd_combo[] = {LT(4, KC_F), RCTL_T(KC_D), COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_BTN1, RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM fg_combo[] = {LT(4, KC_F), KC_G, COMBO_END};
const uint16_t PROGMEM fmouse_combo[] = {RCTL_T(KC_K), KC_BTN1, COMBO_END};

combo_t key_combos[] = {
  [CCLK] = COMBO(cckl_combo, TO(1)),
  [wue] = COMBO(ue_combo, LGUI(KC_UP)),
  [whidari] = COMBO(hidari_combo, LGUI(KC_LEFT)),
  [wmigi] = COMBO(migi_combo, LGUI(KC_RIGHT)),
  [wsita] = COMBO(sita_combo, LGUI(KC_DOWN)),
  [fd] = COMBO(fd_combo, KC_F10),
  [jk] = COMBO(jk_combo, TO(1)),
  [fg] = COMBO(fg_combo, KC_F7),
  [fmouse] = COMBO(fmouse_combo, KC_BTN2),
};


typedef struct {
bool is_press_action;
int state;
} tap;

enum {
SINGLE_TAP = 1,
SINGLE_HOLD,
DOUBLE_TAP,
SINGLE_TAP_HOLD,
DOUBLE_SINGLE_TAP,
TRIPLE_TAP,
};

enum {
    //TD_ESC_CAPS,
    X_TAP_DANCE_1 = 0,
    TD_KAKKO1,
    TD_KAKKO2,
    TD_KAKKO3,
    TD_KAKKO4,
    TD_DOT,
    TD_QS,
    TD_CLN,
    TD_QT,
    TD_GRV,
    TD_MNS,
    TD_EQ,
    //TD_TAB,
    TD_BIKKURI,
    TD_SHARP,
    X_TAP_DANCE_2,
    X_TAP_DANCE_3,
    X_TAP_DANCE_4,
    X_TAP_DANCE_5,
    X_TAP_DANCE_7,
};

int cur_dance (tap_dance_state_t *state);

void x_finished (tap_dance_state_t *state, void *user_data);
void x_reset (tap_dance_state_t *state, void *user_data);

#define TAP_1 TD(X_TAP_DANCE_1)
#define TAP_2 TD(X_TAP_DANCE_2) //migikurito lay1 
#define TAP_3 TD(X_TAP_DANCE_3) //ctl a 0F
#define TAP_4 TD(X_TAP_DANCE_4) //modoru 10
#define TAP_5 TD(X_TAP_DANCE_5) //space 11
#define TAP_7 TD(X_TAP_DANCE_7) //h 12

/* Tap danceの設定 */
int cur_dance (tap_dance_state_t *state) {
if (state->count ==1) {
if (!state->pressed) return SINGLE_TAP;
else return SINGLE_HOLD;
}
else if (state->count == 2) {
if (state->interrupted) return DOUBLE_SINGLE_TAP;
else if (state->pressed) return SINGLE_TAP_HOLD;
else return DOUBLE_TAP;
}
else if (state->count == 3) {
return TRIPLE_TAP;
}
else return 8; //magic number. At some point this method will expand to work for more presses
}
static tap xtap_state = {
.is_press_action = true,
.state = 0
};

/* X_TAP_DANCE_1の定義 */
void x_finished_1 (tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
case SINGLE_TAP:
register_code(KC_F13);
break;
case SINGLE_HOLD:
layer_on(2);
break;
case SINGLE_TAP_HOLD:
layer_on(3);
break;
case DOUBLE_TAP:
register_code(KC_LCTL);
register_code(KC_C);
break;
case TRIPLE_TAP:
register_code(KC_LCTL);
register_code(KC_V);
break;
}
}

void x_reset_1 (tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
case SINGLE_TAP:
unregister_code(KC_F13);
break;
case SINGLE_HOLD:
layer_off(2);
break;
case SINGLE_TAP_HOLD:
layer_off(3);
break;
case DOUBLE_TAP:
unregister_code(KC_LCTL);
unregister_code(KC_C);
break;
case TRIPLE_TAP:
unregister_code(KC_LCTL);
unregister_code(KC_V);
break;
}
xtap_state.state = 0;
}

// X_TAP_DANCE_2の定義 

void x_finished_2 (tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
case SINGLE_TAP:
register_code(KC_BTN2);
break;
case SINGLE_HOLD:
layer_on(1);
break;
case DOUBLE_TAP:
layer_on(1);
break;
}
}

void x_reset_2 (tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
case SINGLE_TAP:
unregister_code(KC_BTN2);
break;
case SINGLE_HOLD:
layer_off(1);
break;
case DOUBLE_TAP:
break;
}
xtap_state.state = 0;
}

void x_finished_3 (tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
case SINGLE_TAP:
register_code(KC_LCTL);
register_code(KC_A);
break;
case DOUBLE_TAP:
register_code(KC_LCTL);
register_code(KC_X);
break;
case TRIPLE_TAP:
register_code(KC_LCTL);
register_code(KC_Z);
break;
}
}

void x_reset_3 (tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
case SINGLE_TAP:
unregister_code(KC_LCTL);
unregister_code(KC_A);
break;
case DOUBLE_TAP:
unregister_code(KC_LCTL);
unregister_code(KC_X);
break;
case TRIPLE_TAP:
unregister_code(KC_LCTL);
unregister_code(KC_Z);
break;
}
xtap_state.state = 0;
}

void x_finished_4 (tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
case SINGLE_TAP:
register_code(KC_LALT);
register_code(KC_LEFT);
break;
case SINGLE_HOLD:
layer_on(1);
break;
case DOUBLE_TAP:
register_code(KC_LALT);
register_code(KC_RIGHT);
break;
}
}

void x_reset_4 (tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
case SINGLE_TAP:
unregister_code(KC_LALT);
unregister_code(KC_LEFT);
break;
case SINGLE_HOLD:
layer_off(1);
break;
case DOUBLE_TAP:
unregister_code(KC_LALT);
unregister_code(KC_RIGHT);
break;
}
xtap_state.state = 0;
}


void x_finished_5 (tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
case SINGLE_TAP:
register_code(KC_SPACE);
break;
case SINGLE_HOLD:
layer_on(3);
break;
case SINGLE_TAP_HOLD:
register_code(KC_LALT);
layer_on(3);
break;
}
}

void x_reset_5 (tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
case SINGLE_TAP:
unregister_code(KC_SPACE);
break;
case SINGLE_HOLD:
layer_off(3);
break;
case SINGLE_TAP_HOLD:
unregister_code(KC_LALT);
layer_off(3);
break;
}
xtap_state.state = 0;
}

void x_finished_6 (tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
case SINGLE_TAP:
register_code(KC_MINS);
break;
case SINGLE_HOLD:
layer_on(4);
break;
case DOUBLE_TAP:
register_code(KC_LSFT);
register_code(KC_MINS);
break;
}
}

void x_reset_6 (tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
case SINGLE_TAP:
unregister_code(KC_MINS);
break;
case SINGLE_HOLD:
layer_off(4);
break;
case DOUBLE_TAP:
unregister_code(KC_LSFT);
unregister_code(KC_MINS);
break;
}
xtap_state.state = 0;
}

void x_finished_7 (tap_dance_state_t *state, void *user_data) {
xtap_state.state = cur_dance(state);
switch (xtap_state.state) {
case SINGLE_TAP:
register_code(KC_H);
break;
case SINGLE_HOLD:
layer_on(1);
break;
case DOUBLE_TAP:
register_code(KC_BTN2);
break;
}
}

void x_reset_7 (tap_dance_state_t *state, void *user_data) {
switch (xtap_state.state) {
case SINGLE_TAP:
unregister_code(KC_H);
break;
case SINGLE_HOLD:
layer_off(1);
break;
case DOUBLE_TAP:
unregister_code(KC_BTN2);
break;
}
xtap_state.state = 0;
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    //[TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [X_TAP_DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_2, x_reset_2),
    [TD_KAKKO1] = ACTION_TAP_DANCE_DOUBLE(S(KC_9), KC_LBRC),
    [TD_KAKKO2] = ACTION_TAP_DANCE_DOUBLE(S(KC_0), KC_RBRC),
    [TD_KAKKO3] = ACTION_TAP_DANCE_DOUBLE(S(KC_COMM), S(KC_LBRC)),
    [TD_KAKKO4] = ACTION_TAP_DANCE_DOUBLE(S(KC_DOT), S(KC_RBRC)),
    //[TD_DOT] = ACTION_TAP_DANCE_FN(dance_comma),
    [TD_DOT] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SLSH),
    [TD_QS] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, S(KC_SLSH)),
    [TD_CLN] = ACTION_TAP_DANCE_DOUBLE(S(KC_SCLN), KC_SCLN),
    [TD_QT] = ACTION_TAP_DANCE_DOUBLE(S(KC_QUOT), KC_QUOT),
    [TD_GRV] = ACTION_TAP_DANCE_DOUBLE(S(KC_GRV), KC_GRV),
    [TD_MNS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_6, x_reset_6),
    [TD_EQ] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, S(KC_EQL)),
    [X_TAP_DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset_1),
    [TD_BIKKURI] = ACTION_TAP_DANCE_DOUBLE(S(KC_1), S(KC_2)),
    [TD_SHARP] = ACTION_TAP_DANCE_DOUBLE(S(KC_3), S(KC_7)),
    [X_TAP_DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_3, x_reset_3),
    [X_TAP_DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_4, x_reset_4),
    [X_TAP_DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_5, x_reset_5),
    [X_TAP_DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_7, x_reset_7),
};



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_DEL   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_INT3  ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    MO(1)    , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_RBRC  ,              KC_NUHS, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
    _______  , KC_LCTL  , KC_LALT  , KC_LGUI,LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1),    KC_BSPC,LT(2,KC_ENT),LT(1,KC_LNG2),KC_RGUI, _______ , KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    S(KC_ESC), S(KC_1)  , KC_LBRC  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                  KC_EQL   , S(KC_6)  ,S(KC_QUOT), S(KC_8)  , S(KC_9)  ,S(KC_INT1),
    S(KC_DEL), S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                                  S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,S(KC_INT3),
    S(KC_TAB), S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                                  S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L)  , KC_QUOT  , S(KC_2)  ,
    _______  , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,S(KC_RBRC),           S(KC_NUHS), S(KC_N)  , S(KC_M)  ,S(KC_COMM), S(KC_DOT),S(KC_SLSH),S(KC_RSFT),
    _______  ,S(KC_LCTL),S(KC_LALT),S(KC_LGUI), _______  , _______  , _______  ,            _______  , _______  , _______  ,S(KC_RGUI), _______  , S(KC_RALT), _______
  ),

  [2] = LAYOUT_universal(
    SSNP_FRE , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  _______  , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , KC_F12   ,
    SSNP_HOR , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,            S(KC_9)  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , KC_0     , KC_DOT   , _______  , _______  , _______  ,             KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
  ),
};
// clang-format on


layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 1);
//#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
//  keyball_handle_auto_mouse_layer_change(state);
//#endif
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    //keyball_oled_render_keyinfo();
    //keyball_oled_render_ballinfo();
    //keyball_oled_render_layerinfo();
    //oled_write_ln_P(PSTR(" "), false);
    //oled_write_ln_P(PSTR(" "), false);
    //oled_write_ln_P(PSTR(" "), false);
    //oled_write_ln_P(PSTR(" "), false);
    //oled_write_ln_P(PSTR(" "), false);
    keyball_oled_render_cpi_status();
    keyball_oled_render_cat();
    keyball_oled_render_nikukyu();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return !is_keyboard_master() ? OLED_ROTATION_180 : OLED_ROTATION_270;
}
#endif
