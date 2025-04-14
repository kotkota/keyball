/*
 * keymap.c - Постепенный перенос с ZMK sofle.keymap
 * Шаг 1.6: Возврат к правильному (не обратному) порядку аргументов для правой половины.
 * Исправлены кейкоды, убран RESET. Только слои и базовые назначения клавиш.
 */

 #include QMK_KEYBOARD_H

 // --- Определения слоев ---
 enum sofle_layers {
     _DFLT = 0, _RU, _GAME, _NUM, _FUNC, _MEDIA, _STCKY, _SYS
 };
 
 // --- Алиасы Mod-Tap ---
 #define A_LSFT MT(MOD_LSFT, KC_A)
 #define S_LCTL MT(MOD_LCTL, KC_S)
 #define D_LALT MT(MOD_LALT, KC_D)
 #define F_LGUI MT(MOD_LGUI, KC_F)
 #define J_RGUI MT(MOD_RGUI, KC_J)
 #define K_RALT MT(MOD_RALT, KC_K)
 #define L_RCTL MT(MOD_RCTL, KC_L)
 #define SCLN_RSFT MT(MOD_RSFT, KC_SCLN)
 
 // --- Алиасы Layer-Tap ---
 #define BSPC_FUNC LT(_FUNC, KC_BSPC)
 #define SPC_NUM LT(_NUM, KC_SPC)
 #define ENT_MEDIA LT(_MEDIA, KC_ENT)
 #define GRAVE_STK LT(_STCKY, KC_GRV)
 #define ESC_SYS LT(_SYS, KC_ESC)
 #define BSLH_STK LT(_STCKY, KC_BSLS)
 #define TAB_CTL MT(MOD_LCTL, KC_TAB)
 #define QUOT_CTL MT(MOD_LCTL, KC_QUOT)
 
 // --- Алиасы One-Shot ---
 #define OSL_NUM OSL(_NUM)
 #define SK_LSFT OSM(MOD_LSFT)
 #define SK_LCTL OSM(MOD_LCTL)
 #define SK_LALT OSM(MOD_LALT)
 #define SK_LGUI OSM(MOD_LGUI)
 #define SK_RSFT OSM(MOD_RSFT)
 #define SK_RCTL OSM(MOD_RCTL)
 #define SK_RALT OSM(MOD_RALT)
 #define SK_RGUI OSM(MOD_RGUI)
 #define SK_HYPR OSM(MOD_HYPR)
 #define SK_MEH  OSM(MOD_MEH)
 
 // --- Заглушки для сложных ZMK ---
 #define ZMK_RU_Z KC_Z
 #define ZMK_RU_HA KC_H
 #define ZMK_PLAYNP KC_MPLY
 #define ZMK_NUMWORD OSL_NUM
 #define ZMK_BOOT QK_BOOT
 #define ZMK_RESET KC_NO
 
 // --- Основной массив раскладок ---
 // Используем LAYOUT_universal (псевдоним LAYOUT_no_ball)
 // ПРАВАЯ ПОЛОВИНА ПЕРЕДАЕТСЯ В НОРМАЛЬНОМ ПОРЯДКЕ (R00..R05, R10..R15, ...)
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
     [_DFLT] = LAYOUT_universal( // Слой 0: Default EN (Нормальный порядок Rxx)
         // L00-L05            R00-R05
         ESC_SYS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
         // L10-L15            R10-R15
         TAB_CTL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, // [
         // L20-L25            R20-R25
         KC_LCTL,  A_LSFT,  S_LCTL,  D_LALT,  F_LGUI,  KC_G,              KC_H,    J_RGUI,  K_RALT,  L_RCTL,  SCLN_RSFT,QUOT_CTL,
         // L30-L36            R30-R36
         GRAVE_STK,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_MPLY,   KC_MUTE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, BSLH_STK,
         // L40-L46            R40-R46
         KC_NO,    KC_DEL,  KC_LGUI, BSPC_FUNC, SPC_NUM, ENT_MEDIA, KC_NO, KC_NO,   ENT_MEDIA,SPC_NUM, BSPC_FUNC, KC_RGUI, KC_DEL,  KC_NO
     ),
 
     [_RU] = LAYOUT_universal( // Слой 1: Russian (Нормальный порядок Rxx)
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ZMK_RU_Z,ZMK_RU_HA, // R14(P)=я, R15([)=х
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUOT, KC_TRNS, // R35(')='
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
 
     [_GAME] = LAYOUT_universal( // Слой 2: Gaming (Нормальный порядок Rxx)
         KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
         KC_T,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
         KC_G,    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LBRC,
         KC_B,    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_NO,     KC_TRNS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
         KC_NO,   KC_I,    KC_H,    KC_G,    KC_SPC,  KC_ENT,  KC_NO,     KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
     ),
 
     [_NUM] = LAYOUT_universal( // Слой 3: Numbers and Navigation (Нормальный порядок Rxx)
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_TRNS, KC_NO,   KC_P7,   KC_P8,   KC_P9, MT(MOD_LSFT, KC_PAST), KC_HOME,LALT(KC_LEFT),KC_UP,LALT(KC_RIGHT),KC_END, KC_NO,
         KC_TRNS, MT(MOD_LSFT, KC_SCLN), MT(MOD_LCTL,KC_P4), MT(MOD_LALT,KC_P5), MT(MOD_LGUI,KC_P6), MT(MOD_LSFT, KC_PSLS), KC_PGUP, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,   KC_NO,
         KC_TRNS, KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_P0,   KC_NO,     KC_TRNS, KC_PGDN,LGUI(KC_LBRC),LGUI(KC_RBRC),RSFT(RCTL(KC_TAB)),RCTL(KC_TAB),KC_TRNS,
         KC_NO,   KC_LPRN, KC_RPRN, KC_PDOT, KC_TRNS, KC_TRNS, KC_NO,     KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
     ),
 
      [_FUNC] = LAYOUT_universal( // Слой 4: Function keys and Symbols (Нормальный порядок Rxx)
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,             KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, // Правая home row пуста?
         KC_SLSH, KC_LPRN, KC_LABK, KC_LBRC, KC_LCBR, MT(MOD_LSFT, KC_BSLS), KC_NO, KC_TRNS,KC_PIPE, KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, KC_QUES,
         KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,     KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
     ),
 
     [_MEDIA] = LAYOUT_universal( // Слой 5: Media keys and Shortcuts (Нормальный порядок Rxx)
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO, LSFT(LGUI(KC_1)), LSFT(LGUI(KC_2)), LGUI(LSFT(KC_3)), LSFT(LGUI(KC_4)), LSFT(LGUI(KC_5)), KC_NO, KC_NO, KC_NO, ZMK_PLAYNP,KC_VOLD, KC_VOLU,
         KC_NO, LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_NO, KC_NO, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO, LGUI(KC_Z), LGUI(LSFT(KC_Z)), KC_NO, KC_NO, KC_NO, KC_MUTE,KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO, SK_HYPR, KC_CAPS, KC_DEL,  KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_CAPS, SK_HYPR, KC_DEL,  KC_NO,   KC_NO, KC_NO // Порядок на R-thumb: ..., KC_DEL, SK_HYPR, KC_CAPS, KC_NO
     ),
 
     [_STCKY] = LAYOUT_universal( // Слой 6: Sticky Mods Layer (Нормальный порядок Rxx)
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO, LGUI(KC_LEFT), LGUI(KC_RIGHT), LGUI(KC_R), LGUI(KC_T), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         SK_HYPR, SK_LSFT, SK_LCTL, SK_LALT, SK_LGUI, LGUI(KC_G),          KC_NO,   SK_RGUI, SK_RALT, SK_RCTL, SK_RSFT, SK_HYPR,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO,   KC_TRNS, TO(_DFLT), TO(_RU), ZMK_NUMWORD, KC_TRNS, KC_NO, KC_NO,   TO(_RU), TO(_DFLT), KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
     ),
 
     [_SYS] = LAYOUT_universal( // Слой 7: System Layer (Нормальный порядок Rxx)
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         ZMK_RESET,KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO,   KC_NO,   KC_NO,   ZMK_BOOT,ZMK_BOOT,KC_NO,   KC_NO,     KC_NO,   ZMK_BOOT,ZMK_BOOT,KC_NO,   KC_NO,   KC_NO, KC_NO
     )
 };
 
 // --- Пустая функция обработчик событий ---
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     return true;
 }
 
 // --- Обработка состояния слоев ---
 layer_state_t layer_state_set_user(layer_state_t state) {
     // keyball_set_scroll_mode(get_highest_layer(state) == 3);
     return state;
 }
 
 // --- OLED ---
 #ifdef OLED_ENABLE
 #    include "lib/oledkit/oledkit.h" // Уточните путь, если нужно
 
 const char *layer_name(uint8_t layer_index) {
     switch (layer_index) {
         case _DFLT:  return "Default";
         case _RU:    return "Russian";
         case _GAME:  return "Game";
         case _NUM:   return "Num/Nav";
         case _FUNC:  return "Func/Sym";
         case _MEDIA: return "Media";
         case _STCKY: return "Sticky";
         case _SYS:   return "System";
         default:     return "Unknown";
     }
 }
 
 void oledkit_render_info_user(void) {
     keyball_oled_render_keyinfo();
     keyball_oled_render_ballinfo();
     oled_set_cursor(0, 2);
     oled_write_P(PSTR("Layer: "), false);
     oled_write_ln(layer_name(get_highest_layer(layer_state)), false);
 }
 #endif // OLED_ENABLE