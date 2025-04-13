/*
 * keymap.c - Постепенный перенос с ZMK sofle.keymap
 * Шаг 1.2: Корректное использование LAYOUT_no_ball/LAYOUT_universal (64 клавиши)
 * согласно keyball61.h. Только слои и базовые назначения клавиш.
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
 #define SK_CAPS OSM(MOD_CAPS)
 
 // --- Заглушки для сложных ZMK ---
 #define ZMK_RU_Z KC_Z
 #define ZMK_RU_HA KC_H
 #define ZMK_PLAYNP KC_MPLY
 #define ZMK_NUMWORD OSL_NUM
 #define ZMK_BOOT QK_BOOT
 #define ZMK_RESET RESET
 
 // --- Основной массив раскладок ---
 // Используем LAYOUT_universal (псевдоним LAYOUT_no_ball) и передаем 64 аргумента
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
     [_DFLT] = LAYOUT_universal( // Слой 0: Default EN (64 клавиши)
         // L00-L05            R05-R00 (Правая сторона в обратном порядке!)
         ESC_SYS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_BSPC, KC_0,    KC_9,    KC_8,    KC_7,    KC_6,
         // L10-L15            R15-R10
         TAB_CTL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_LBRC, KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,
         // L20-L25            R25-R20
         KC_LCTL,  A_LSFT,  S_LCTL,  D_LALT,  F_LGUI,  KC_G,              QUOT_CTL,SCLN_RSFT,L_RCTL, K_RALT,  J_RGUI,  KC_H,
         // L30-L36            R36-R30
         GRAVE_STK,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_MPLY,   BSLH_STK,KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,   KC_MUTE,
         // L40-L46            R46-R40
         KC_NO, MT(MOD_CAPS, KC_DEL), KC_LGUI, BSPC_FUNC, SPC_NUM, ENT_MEDIA, KC_NO, KC_NO, MT(MOD_CAPS, KC_DEL), KC_RGUI, BSPC_FUNC, SPC_NUM, ENT_MEDIA, KC_NO
         // ^^^ Заменил левый/правый thumb cluster на основе ZMK, добавил KC_NO для заполнения 7+7 позиций
     ),
 
     [_RU] = LAYOUT_universal( // Слой 1: Russian (64 клавиши, в основном пусто)
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           ZMK_RU_HA,ZMK_RU_Z,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, // Правая P, [ -> я, х
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, // Правый / -> '
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
 
     [_GAME] = LAYOUT_universal( // Слой 2: Gaming (64 клавиши)
         KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_MINS, KC_0,    KC_9,    KC_8,    KC_7,    KC_6,
         KC_T,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,              KC_EQL,  KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,
         KC_G,    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,              KC_LBRC, KC_SCLN, KC_L,    KC_K,    KC_J,    KC_H,
         KC_B,    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_NO,     KC_RBRC, KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,    KC_TRNS,
         KC_NO,   KC_I,    KC_H,    KC_G,    KC_SPC,  KC_ENT,  KC_NO,     KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
     ),
 
     [_NUM] = LAYOUT_universal( // Слой 3: Numbers and Navigation (64 клавиши)
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_TRNS, KC_NO,   KC_P7,   KC_P8,   KC_P9, MT(MOD_LSFT, KC_PAST), KC_NO, KC_END,LALT(KC_RIGHT),KC_UP,LALT(KC_LEFT),KC_HOME,
         KC_TRNS, MT(MOD_LSFT, KC_SCLN), MT(MOD_LCTL,KC_P4), MT(MOD_LALT,KC_P5), MT(MOD_LGUI,KC_P6), MT(MOD_LSFT, KC_PSLS), KC_NO, KC_RIGHT, KC_DOWN, KC_LEFT, KC_PGUP, KC_NO,
         KC_TRNS, KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_P0,   KC_NO,     KC_TRNS,RCTL(KC_TAB),RSFT(RCTL(KC_TAB)),LGUI(KC_RBRC),LGUI(KC_LBRC),KC_PGDN,KC_TRNS,
         KC_NO,   KC_LPRN, KC_RPRN, KC_PDOT, KC_TRNS, KC_TRNS, KC_NO,     KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
     ),
 
      [_FUNC] = LAYOUT_universal( // Слой 4: Function keys and Symbols (64 клавиши)
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,             KC_TRNS, KC_PERC, KC_DLLR, KC_HASH, KC_AT,   KC_EXLM,
         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,            KC_TRNS, KC_RPRN, KC_LPRN, KC_ASTR, KC_AMPR, KC_CIRC,
         KC_SLSH, KC_LPRN, KC_LABK, KC_LBRC, KC_LCBR, MT(MOD_LSFT, KC_BSLS), KC_NO, KC_QUES,KC_PLUS, KC_EQL,  KC_UNDS, KC_MINS, KC_PIPE, KC_TRNS,
         KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,     KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
     ),
 
     [_MEDIA] = LAYOUT_universal( // Слой 5: Media keys and Shortcuts (64 клавиши)
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO, LSFT(LGUI(KC_1)), LSFT(LGUI(KC_2)), LGUI(LSFT(KC_3)), LSFT(LGUI(KC_4)), LSFT(LGUI(KC_5)), KC__VOLUP,KC__VOLDOWN,ZMK_PLAYNP,KC_NO,KC_NO,KC_NO,
         KC_NO, LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_NO, KC_NO, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO, LGUI(KC_Z), LGUI(LSFT(KC_Z)), KC_NO, KC_NO, KC_NO, KC_MUTE,KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO, SK_HYPR, SK_CAPS, KC_DEL,  KC_NO,   KC_NO,   KC_NO,       KC_NO,   SK_HYPR, SK_CAPS, KC_DEL,  KC_NO,   KC_NO, KC_NO
     ),
 
     [_STCKY] = LAYOUT_universal( // Слой 6: Sticky Mods Layer (64 клавиши)
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO, LGUI(KC_LEFT), LGUI(KC_RIGHT), LGUI(KC_R), LGUI(KC_T), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         SK_HYPR, SK_LSFT, SK_LCTL, SK_LALT, SK_LGUI, LGUI(KC_G),          SK_HYPR, SK_RSFT, SK_RCTL, SK_RALT, SK_RGUI, KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO,   KC_TRNS, TO(_DFLT), TO(_RU), ZMK_NUMWORD, KC_TRNS, KC_NO, KC_NO,   KC_TRNS, TO(_DFLT), TO(_RU), KC_TRNS, KC_TRNS, KC_NO
     ),
 
     [_SYS] = LAYOUT_universal( // Слой 7: System Layer (64 клавиши)
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         ZMK_RESET,KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO,   KC_NO,   KC_NO,   ZMK_BOOT,ZMK_BOOT,KC_NO,   KC_NO,     KC_NO,   KC_NO,   ZMK_BOOT,ZMK_BOOT,KC_NO,   KC_NO, KC_NO
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