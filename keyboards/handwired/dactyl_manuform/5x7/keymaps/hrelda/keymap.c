#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _PDVORAK 0 // programmero dvorak base layer
#define _SHIFTED_PDVORAK 1
#define _FN 10
#define _LH_DEBUG 5
#define _QWERTY 6
#define _QWERTY_TWOSPC 7

// Some basic macros
#define TASK   LCTL(LSFT(KC_ESC))
#define TAB_R  LCTL(KC_TAB)
#define TAB_L  LCTL(LSFT(KC_TAB))
#define TAB_RO LCTL(LSFT(KC_T))
#define WIN_SS LSG(KC_S)  //win+shift+s
//
//tap dance
enum {
    TD_CAPS_WORD, //capword, caps lock, single press turns off capslock
    TD_RCTLALT, // ctrl, alt
};

void td_fn_capsw_toggle(tap_dance_state_t *state, void *user_data)
{
    //wrote a function for this beacuse ACTION_TAP_DANCE_DBOULE only takes basic keycodes and
    //caps word toggle was not working with the CAPSWORD keycode
    if(state->count == 1) {
        //if caps is on turn it off, otherwise turn on caps word
        if(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)){
            register_code(KC_CAPS);
        } else {
            caps_word_toggle();
        }
    } else {
       register_code(KC_CAPS);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS_WORD] = ACTION_TAP_DANCE_FN(td_fn_capsw_toggle),
    //[TD_CAPS_WORD] = ACTION_TAP_DANCE_DOUBLE(QK_CAPS_WORD_TOGGLE,KC_CAPS),
    [TD_RCTLALT]   = ACTION_TAP_DANCE_DOUBLE(KC_RCTL,KC_RALT),
};


//keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_PDVORAK] = LAYOUT_5x7(
        // left hand
       //LSFT(KC_4),            LSFT(KC_EQUAL),  KC_LBRC,   LSFT(KC_LBRC),  LSFT(KC_9),   LSFT(KC_7),  KC_EQUAL,
//LBRC = left bracket , LCBR = left curly brace , LPRN = left parenthesis
        KC_DOLLAR,             KC_PLUS,         KC_LBRC,   KC_LCBR,        KC_LPRN,      KC_AMPERSAND, KC_EQUAL,
        KC_TAB,                KC_SEMICOLON,    KC_COMMA,  KC_DOT,         KC_P,         KC_Y,        TO(_LH_DEBUG),
        KC_ESCAPE,             KC_A,            KC_O,      KC_E,           KC_U,         KC_I,        TO(_FN),
        MO(_SHIFTED_PDVORAK),  KC_QUOTE,        KC_Q,      KC_J,           KC_K,         KC_X,
        TT(_FN),               TD(TD_CAPS_WORD),KC_LEFT,   KC_RIGHT,
                                                                            KC_BACKSPACE,         KC_DELETE,
                                                                            KC_LCTL,  KC_LALT,
                                                                            KC_END,            KC_HOME,
        // right hand
        //LSFT(KC_8),    LSFT(KC_3),  LSFT(KC_0),  LSFT(KC_RBRC),  KC_RBRC,  LSFT(KC_1),  LSFT(KC_2),
//      see above. AT = @, circumflex below = ^
        KC_ASTERISK,   KC_HASH,     KC_RPRN,     KC_RCBR,        KC_RBRC,  KC_EXCLAIM,  KC_AT,
        KC_BACKSLASH,  KC_F,        KC_G,        KC_C,           KC_R,     KC_L,        KC_SLASH,
        KC_GRAVE,      KC_D,        KC_H,        KC_T,           KC_N,     KC_S,        KC_MINUS,
                       KC_B,        KC_M,        KC_W,           KC_V,     KC_Z,        MO(_SHIFTED_PDVORAK),
                                                 KC_DOWN,        KC_UP,    KC_CIRCUMFLEX,  KC_PERCENT,
                  KC_ENTER,      KC_SPACE,
                  KC_LGUI,       TD(TD_RCTLALT),
                  KC_PGUP,       KC_PGDN

    ),
    [_SHIFTED_PDVORAK] = LAYOUT_5x7(
        // left hand
        LSFT(KC_4),  KC_1,                KC_2,            KC_3,          KC_4,        KC_5,        KC_EQUAL,
        LSFT(KC_TAB),      LSFT(KC_SEMICOLON),  LSFT(KC_COMMA),  LSFT(KC_DOT),  LSFT(KC_P),  LSFT(KC_Y),  TO(_QWERTY),
        LSFT(KC_ESCAPE),   LSFT(KC_A),          LSFT(KC_O),      LSFT(KC_E),    LSFT(KC_U),  LSFT(KC_I),  TO(_FN),
        KC_TRNS,     LSFT(KC_QUOTE),      LSFT(KC_Q),      LSFT(KC_J),    LSFT(KC_K),  LSFT(KC_X),
        KC_TRNS,     KC_TRNS,             LSFT(KC_LEFT),         LSFT(KC_RIGHT),
                                                                          KC_TRNS, KC_TRNS,
                                                                          KC_TRNS, KC_TRNS,
                                                                          LSFT(KC_END), LSFT(KC_HOME),
        // right hand
        LSFT(KC_8),          KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        LSFT(KC_2),
        LSFT(KC_BACKSLASH),  LSFT(KC_F),  LSFT(KC_G),  LSFT(KC_C),  LSFT(KC_R),  LSFT(KC_L),  LSFT(KC_SLASH),
        LSFT(KC_GRAVE),      LSFT(KC_D),  LSFT(KC_H),  LSFT(KC_T),  LSFT(KC_N),  LSFT(KC_S),  LSFT(KC_MINUS),
                             LSFT(KC_B),  LSFT(KC_M),  LSFT(KC_W),  LSFT(KC_V),  LSFT(KC_Z),  KC_TRNS,
                                                       LSFT(KC_DOWN), LSFT(KC_UP), KC_TRNS,   KC_TRNS,
                  KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS,
                  LSFT(KC_PGUP), LSFT(KC_PGDN)
    ),
    [_FN] = LAYOUT_5x7(
        // left hand
        QK_BOOT,   KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,    KC_F6,
        KC_VOLU,   _______,     LCTL(KC_W),  _______,     _______,     LCTL(KC_Y),  TO(_PDVORAK),
        KC_VOLD,   LCTL(KC_A),  LCTL(KC_S),  LCTL(KC_D),  LCTL(KC_F),  _______,  TO(_QWERTY),
        KC_MUTE,   LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C),  LCTL(KC_V),  TO(_LH_DEBUG),
        _______,   WIN_SS,      KC_CALC,     KC_MYCM,
                                    _______, _______,
                                    _______, _______,
                                    _______, _______,
        // right hand
                          KC_F7,     KC_F8,           KC_F9,     KC_F10,    KC_F11,     KC_F12,       KC_NUM_LOCK,
                          _______,   KC_KP_ASTERISK,  KC_KP_7,   KC_KP_8,   KC_KP_9,    KC_KP_MINUS,  KC_SCROLL_LOCK,
               TO(_QWERTY_TWOSPC),   KC_KP_SLASH,     KC_KP_4,   KC_KP_5,   KC_KP_6,    KC_KP_PLUS,   _______,
                                     _______,         KC_KP_1,   KC_KP_2,   KC_KP_3,    KC_KP_ENTER,      KC_KP_ENTER,
                                                      KC_KP_0,   KC_KP_DOT,  _______,   _______,
             KC_DEL, KC_ENTER,
             _______, _______,
             _______, _______
    ),
    [_LH_DEBUG] = LAYOUT_5x7(
        // left hand
        _______,   _______,  _______,  _______,  _______,  _______,    _______,
        _______,   LSFT(KC_F5), LCA(KC_B), _______,  KC_F5,  _______,    TO(_PDVORAK),
        _______,   _______,  _______,  LSFT(KC_F11),   KC_F10,  KC_F11,  TO(_QWERTY),
        _______,   _______,  _______,  _______,  _______,  _______,
        _______,   _______,  _______,  _______,
                                    _______, _______,
                                    _______, _______,
                                    _______, _______,
        // right hand
        KC_F7,     KC_F8,           KC_F9,     KC_F10,    KC_F11,     KC_F12,       KC_NUM_LOCK,
        _______,   KC_KP_ASTERISK,  KC_KP_7,   KC_KP_8,   KC_KP_9,    KC_KP_MINUS,  KC_SCROLL_LOCK,
        _______,   KC_KP_SLASH,     KC_KP_4,   KC_KP_5,   KC_KP_6,    KC_KP_PLUS,   _______,
        _______,         KC_KP_1,   KC_KP_2,   KC_KP_3,    KC_KP_ENTER,      KC_KP_ENTER,
        _______,   KC_KP_0,   KC_KP_DOT,  _______,
             KC_DEL, KC_ENTER,
             _______, _______,
             _______, _______
    ),

    //qwerty per the keycaps & a qwerty with double space on thumbs for games
    [_QWERTY] = LAYOUT_5x7(
        // left hand
        KC_MINUS,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_GRAVE,
        KC_TAB,      KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   TO(_PDVORAK),
        KC_ESCAPE,     KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   TO(_FN),
        MOD_LSFT,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
        TT(_FN),    TD(TD_CAPS_WORD), KC_LEFT,   KC_RIGHT,
                                                         KC_BACKSPACE,         KC_DELETE,
                                                         KC_LALT,  KC_LCTL,
                                                         KC_END,            KC_HOME,
        // right hand
                          KC_CALC, KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_EQUAL,
                          KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
                          _______, KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  MOD_RSFT,
                                            KC_DOWN, KC_UP,    KC_LBRC,  KC_RBRC,
                  KC_ENTER,      KC_SPACE,
                  KC_LGUI,       KC_RCTL,
                  KC_PGUP,       KC_PGDN
    ),
    [_QWERTY_TWOSPC] = LAYOUT_5x7( // left hand
        KC_MINUS,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_GRAVE,
        KC_TAB,      KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   TO(_PDVORAK),
        KC_ESCAPE,     KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   TO(_FN),
        OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
        TT(_FN),    TD(TD_CAPS_WORD), KC_LEFT,   KC_RIGHT,
                                                         KC_SPACE,         KC_BACKSPACE,
                                                         OSM(MOD_LALT),  OSM(MOD_LCTL),
                                                         KC_END,            KC_HOME,
        // right hand
                          KC_CALC, KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_EQUAL,
                          KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
                          _______, KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT),
                                            KC_DOWN, KC_UP,    KC_LBRC,  KC_RBRC,
                  KC_ENTER,      KC_SPACE,
                  KC_PGUP,       KC_PGDN,
                  OSM(MOD_RCTL), OSM(KC_RGUI)
    ),
};


