/*
 * keymap.c - Постепенный перенос с ZMK sofle.keymap
 * Шаг 1: Только слои и базовые назначения клавиш (KC_, MT, LT, OSM, OSL)
 */

 #include QMK_KEYBOARD_H
 #include "quantum.h"
 
 // --- Определения слоев для читаемости (соответствуют ZMK) ---
 enum sofle_layers {
     _DFLT = 0, // Default Layer (EN)
     _RU,       // Russian Layer
     _GAME,     // Gaming Layer
     _NUM,      // Numbers and Navigation
     _FUNC,     // Function keys and Symbols (В ZMK это был слой 4 - symb)
     _MEDIA,    // Media keys and Shortcuts (В ZMK это был слой 5)
     _STCKY,    // Sticky Mods Layer (В ZMK это был слой 6)
     _SYS       // System Layer (BT, Power etc. - Многие функции не перенесены)
 };
 
 // --- Определения Mod-Tap алиасов (для краткости и читаемости) ---
 // --- Левая рука Home Row Mods ---
 #define A_LSFT MT(MOD_LSFT, KC_A)
 #define S_LCTL MT(MOD_LCTL, KC_S)
 #define D_LALT MT(MOD_LALT, KC_D)
 #define F_LGUI MT(MOD_LGUI, KC_F) // LCMD в ZMK -> LGUI в QMK
 // --- Правая рука Home Row Mods ---
 #define J_RGUI MT(MOD_RGUI, KC_J) // RCMD в ZMK -> RGUI в QMK
 #define K_RALT MT(MOD_RALT, KC_K)
 #define L_RCTL MT(MOD_RCTL, KC_L)
 #define SCLN_RSFT MT(MOD_RSFT, KC_SCLN) // Semicolon (;)
 
 // --- Определения Layer-Tap алиасов ---
 #define BSPC_FUNC LT(_FUNC, KC_BSPC)
 #define SPC_NUM LT(_NUM, KC_SPC)
 #define ENT_MEDIA LT(_MEDIA, KC_ENT)
 #define GRAVE_STK LT(_STCKY, KC_GRV) // В ZMK: &lt 5 GRAVE -> слой MEDIA. Но _STCKY (слой 6) может быть логичнее? Или LT(_MEDIA, KC_GRV)? Проверьте ZMK слой 5. Пока ставлю STCKY (6).
 #define ESC_SYS LT(_SYS, KC_ESC) // В ZMK: &lt 7 ESC -> слой SYS
 #define BSLH_STK LT(_STCKY, KC_BSLS) // В ZMK: &lt 5 BSLH -> слой MEDIA. Ставлю STCKY (6) для симметрии с GRAVE_STK. Или LT(_MEDIA, KC_BSLS)?
 #define TAB_CTL MT(MOD_LCTL, KC_TAB) // В ZMK был сложный MT(LC(LA(LCMD))) TAB. Упрощено до Ctrl+Tab. Адаптируйте, если нужно другое.
 #define QUOT_CTL MT(MOD_LCTL, KC_QUOT) // В ZMK был сложный MT(LC(LA(LCMD))) SQT. Упрощено до Ctrl+'. Адаптируйте.
 
 // --- Определения One-Shot алиасов ---
 #define OSL_NUM OSL(_NUM)  // One-Shot Layer NUM (для замены num_word)
 // Sticky Mods (из ZMK &sk)
 #define SK_LSFT OSM(MOD_LSFT)
 #define SK_LCTL OSM(MOD_LCTL)
 #define SK_LALT OSM(MOD_LALT)
 #define SK_LGUI OSM(MOD_LGUI)
 #define SK_RSFT OSM(MOD_RSFT)
 #define SK_RCTL OSM(MOD_RCTL)
 #define SK_RALT OSM(MOD_RALT)
 #define SK_RGUI OSM(MOD_RGUI)
 #define SK_HYPR OSM(MOD_HYPR) // Hyper (Все модификаторы: Ctrl+Shift+Alt+Gui)
 #define SK_MEH  OSM(MOD_MEH)  // Meh (Ctrl+Shift+Alt)
 #define SK_CAPS OSM(MOD_CAPS)
 
 // --- Определения для пока не реализованных функций ---
 // Заглушки для сложных ZMK поведений, которые пока не переносим
 #define ZMK_RU_Z KC_Z     // Был &ru_z (mod-morph P/O) -> пока просто Z
 #define ZMK_RU_HA KC_H    // Был &ru_ha (mod-morph [/P) -> пока просто H
 #define ZMK_PLAYNP KC_MPLY // Был &playnp (tap-dance) -> пока просто Play/Pause
 #define ZMK_NUMWORD OSL_NUM // Был &num_word -> заменен на One-Shot Layer NUMB
 #define ZMK_BOOT QK_BOOT  // Был &bootloader
 #define ZMK_RESET RESET   // Был &soft_off
 // Пропущенные: &bt..., &out..., &ext_power... -> KC_NO
 
 // --- Основной массив раскладок ---
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
     [_DFLT] = LAYOUT_universal( // Слой 0: Default EN (База из ZMK)
         // Left Hand
         ESC_SYS,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,
         TAB_CTL,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,  // TAB_CTL вместо сложного MT
         KC_LCTL,   A_LSFT,    S_LCTL,    D_LALT,    F_LGUI,    KC_G,  // KC_LCTL вместо сложного MT на Tab в ZMK. Возможно, стоит вернуть KC_TAB?
         GRAVE_STK, KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_MPLY, // KC_MPLY вместо C_PLAY_PAUSE
                                MT(MOD_CAPS, KC_DEL), KC_LGUI, BSPC_FUNC, SPC_NUM, ENT_MEDIA, // Caps+Del вместо сложного MT
         // Right Hand
                                KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_BSPC,
                                KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC, // [
                                KC_H,      J_RGUI,    K_RALT,    L_RCTL,    SCLN_RSFT, QUOT_CTL, // QUOT_CTL вместо сложного MT
                  KC_MUTE,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   BSLH_STK, // / вместо MT QMARK SLASH
                                ENT_MEDIA, SPC_NUM,   BSPC_FUNC, KC_RGUI, MT(MOD_CAPS, KC_DEL) // Caps+Del вместо сложного MT
     ),
 
     [_RU] = LAYOUT_universal( // Слой 1: Russian (Только переключатели и заглушки для mod-morph)
         // Left Hand
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         // Right Hand
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, ZMK_RU_Z,ZMK_RU_HA,KC_TRNS, // Заглушки для 'я' и 'х'
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUOT, KC_TRNS, // ' вместо MT QMARK APOS
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
         // Примечание: Этот слой в основном пуст. Переключение языка (RU_ON/RU_OFF)
         // и обработка специфичных символов потребуют макросов или комбо позже.
     ),
 
     [_GAME] = LAYOUT_universal( // Слой 2: Gaming (перенесено из ZMK)
         // Left Hand
         KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
         KC_T,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,
         KC_G,    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,
         KC_B,    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_NO, // Был &trans
                                KC_I,    KC_H,    KC_G,    KC_SPC,  KC_ENT,
         // Right Hand
                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LBRC,
                  KC_TRNS,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
 
     [_NUM] = LAYOUT_universal( // Слой 3: Numbers and Navigation (перенесено из ZMK)
         // Left Hand
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_TRNS, KC_NO,   KC_P7,   KC_P8,   KC_P9,   MT(MOD_LSFT, KC_PAST), // Tap:*, Hold:Shift+* (?) Уточнить ZMK MT KP_ASTERISK PLUS
         KC_TRNS, MT(MOD_LSFT, KC_SCLN), MT(MOD_LCTL,KC_P4), MT(MOD_LALT,KC_P5), MT(MOD_LGUI,KC_P6), MT(MOD_LSFT, KC_PSLS), // Tap:Numpad, Hold:Mod+Numpad (?) Уточнить ZMK MT
         KC_TRNS, KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_P0,   KC_NO, // Был &trans
                                KC_LPRN, KC_RPRN, KC_PDOT, KC_TRNS, KC_TRNS, // ( ) .
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO,
                                KC_HOME, LALT(KC_LEFT), KC_UP, LALT(KC_RIGHT), KC_END, KC_NO,
                                KC_PGUP, KC_LEFT, KC_DOWN,    KC_RIGHT, KC_NO,   KC_NO,
                  KC_TRNS,      KC_PGDN, LGUI(KC_LBRC), LGUI(KC_RBRC), RSFT(RCTL(KC_TAB)), RCTL(KC_TAB), KC_TRNS, // Комбинации для навигации
                                KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
     ),
 
     [_FUNC] = LAYOUT_universal( // Слой 4: Function keys and Symbols (перенесено из ZMK symb)
         // Left Hand
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,
         KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,      KC_F6,
         KC_F7,   KC_F8,   KC_F9,   KC_F10,     KC_F11,     KC_F12,
         KC_SLSH, KC_LPRN, KC_LABK, KC_LBRC,    KC_LCBR,    MT(MOD_LSFT, KC_BSLS), KC_NO, // / ( < [ { | (Shift+\). Пары (),<> и т.д. пока убраны (требуют макросов/комбо)
                                KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,
         // Right Hand
                                KC_NO,   KC_EXLM, KC_AT,      KC_HASH,    KC_DLR,     KC_PERC, // ! @ # $ %
                                KC_NO,   KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN, // ^ & * ( )
                                KC_TRNS, KC_PIPE, KC_MINS,    KC_UNDS,    KC_EQL,     KC_PLUS, // | - _ = +
                  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_QUES,    KC_NO, // ?
                                KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS
     ),
 
     [_MEDIA] = LAYOUT_universal( // Слой 5: Media keys and Shortcuts (перенесено из ZMK media)
         // Left Hand
         KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO, // BT команды пропущены
         KC_NO,   LSFT(LGUI(KC_1)), LSFT(LGUI(KC_2)), LGUI(LSFT(KC_3)), LSFT(LGUI(KC_4)), LSFT(LGUI(KC_5)), // Ярлыки?
         KC_NO,   LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_NO,      KC_NO,      KC_NO,
         KC_NO,   LGUI(KC_Z), LGUI(LSFT(KC_Z)), KC_NO,      KC_NO,      KC_NO,      KC_MUTE,
                                SK_HYPR, SK_CAPS, KC_DEL,     KC_NO,      KC_NO, // Sticky Mods + Del
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                                KC_NO,   KC_NO,   KC_NO,      ZMK_PLAYNP, KC__VOLDOWN, KC__VOLUP, // Play/Pause вместо TapDance
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                  KC_NO,      KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,
                                KC_NO,   KC_DEL,  SK_CAPS,    SK_HYPR // Sticky Mods + Del
     ),
 
     [_STCKY] = LAYOUT_universal( // Слой 6: Sticky Mods Layer (перенесено из ZMK sticky)
         // Left Hand
         KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,
         KC_NO,   KC_NO,   LGUI(KC_LEFT), LGUI(KC_RIGHT), LGUI(KC_R), LGUI(KC_T), // Mac команды?
         SK_HYPR, SK_LSFT, SK_LCTL,    SK_LALT,    SK_LGUI,    LGUI(KC_G), // Sticky Mods + Cmd+G
         KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                KC_TRNS, TO(_DFLT), TO(_RU),    ZMK_NUMWORD,KC_TRNS, // TO вместо ru_off/on, OSL_NUM вместо num_word
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                                KC_NO,   SK_RGUI, SK_RALT,    SK_RCTL,    SK_RSFT, SK_HYPR,
                  KC_NO,      KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,
                                KC_TRNS, TO(_RU),   TO(_DFLT),  KC_TRNS,    KC_TRNS
     ),
 
     [_SYS] = LAYOUT_universal( // Слой 7: System Layer (перенесено из ZMK system)
         // Left Hand
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // OUT_USB/BLE пропущены
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         ZMK_RESET, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,
                                KC_NO,   KC_NO,   ZMK_BOOT,ZMK_BOOT, KC_NO, // Bootloader
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // BT_PRV/NXT пропущены
                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // BT_SEL/EP_OFF пропущены
                  KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // BT_DISC/CLR пропущены
                                KC_NO,   ZMK_BOOT,ZMK_BOOT, KC_NO,   KC_NO // Bootloader
     )
 };
 
 // --- Пустая функция обработчик событий ---
 // Оставляем ее, так как она может быть нужна для других частей QMK (например, OLED)
 // или для добавления кастомной логики позже.
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     // Пока здесь ничего не делаем
     return true; // Process all keycodes normally
 }
 
 
 // --- Обработка состояния слоев (можно удалить или адаптировать) ---
 // Убираем авто-включение scroll mode из дефолтного keymap.c,
 // так как слой 3 теперь используется для _NUM
 layer_state_t layer_state_set_user(layer_state_t state) {
     // keyball_set_scroll_mode(get_highest_layer(state) == 3); // Закомментировано
     return state;
 }
 
 // --- OLED (адаптировано для отображения новых слоев) ---
 #ifdef OLED_ENABLE
 #    include "lib/oledkit/oledkit.h" // Убедитесь, что путь правильный для вашей структуры
 
 // Функция для отображения имени текущего слоя
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
     // Можно оставить или закомментировать базовую информацию keyball
     keyball_oled_render_keyinfo();
     keyball_oled_render_ballinfo();
 
     // Рисуем имя текущего активного слоя
     oled_set_cursor(0, 2); // Позиция на экране (строка, столбец) - подберите
     oled_write_P(PSTR("Layer: "), false);
     oled_write_ln(layer_name(get_highest_layer(layer_state)), false);
 }
 #endif // OLED_ENABLE