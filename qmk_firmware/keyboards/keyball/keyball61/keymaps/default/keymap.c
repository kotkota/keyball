/*
 * Базовый keymap.c модифицирован для соответствия sofle.keymap (ZMK)
 * Автор оригинального ZMK keymap: (подразумевается пользователь)
 * Автор QMK keymap.c: @Yowkees, MURAOKA Taro (aka KoRoN, @kaoriya)
 * Перенос и адаптация: Gemini AI
 */

 #include QMK_KEYBOARD_H
 #include "quantum.h"
 #ifdef COMBO_ENABLE
 #include "process_combo.h"
 #endif
 
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
 
 // --- Определения Mod-Tap алиасов (для краткости) ---
 // --- Левая рука Home Row Mods ---
 #define A_LSFT MT(MOD_LSFT, KC_A)
 #define S_LCTL MT(MOD_LCTL, KC_S)
 #define D_LALT MT(MOD_LALT, KC_D)
 #define F_LGUI MT(MOD_LGUI, KC_F)
 // --- Правая рука Home Row Mods ---
 #define J_RGUI MT(MOD_RGUI, KC_J) // В ZMK был RCMD, что обычно = RGUI
 #define K_RALT MT(MOD_RALT, KC_K)
 #define L_RCTL MT(MOD_RCTL, KC_L)
 #define SCLN_RSFT MT(MOD_RSFT, KC_SCLN) // ;
 
 // --- Определения Layer-Tap алиасов ---
 #define BSPC_FUNC LT(_FUNC, KC_BSPC)
 #define SPC_NUM LT(_NUM, KC_SPC)
 #define ENT_MEDIA LT(_MEDIA, KC_ENT)
 #define GRAVE_SYS LT(_SYS, KC_GRV) // На GRAVE был LT(5, GRAVE) в ZMK, что _MEDIA. Но SYS кажется логичнее? Или LT(_MEDIA, KC_GRV)? Уточнить. В ZMK на Esc был LT(7, ESC).
 #define ESC_SYS LT(_SYS, KC_ESC) // Заменил &lt 7 ESC
 #define BSLH_MED LT(_MEDIA, KC_BSLS) // Заменил &lt 5 BSLH
 
 // --- Определения One-Shot ---
 #define OSL_NUM OSL(_NUM)
 
 // --- Определения кастомных кейкодов для Макросов и Комбо ---
 enum custom_keycodes {
     // Макросы (примеры, требуют реализации в process_record_user)
     PAR = SAFE_RANGE, // ()+left
     BKT,              // []+left (возможно с ru_off)
     BRC,              // {}+left (возможно с ru_off)
     TAG_OPEN,         // <>+left
     TAG_CLOSE,        // </>+left
     HTML_TAG,         // Hold: TAG_CLOSE, Tap: TAG_OPEN (требует process_record_user или tap-dance)
     EQ_QUOT,          // =""+left
     RU_ON,            // TG(_RU) + OS shortcut
     RU_OFF,           // TO(_DFLT) + OS shortcut
     // Tap Dance
     TD_PLAYNP,        // Play/Pause, Next, Prev
     // Leader Key (требует реализации)
     LEADER_KEY,
     // Другие кастомные кейкоды если нужны
     RU_Z, // Для 'я' (ZMK: P/O mod-morph) - Заменяем на KC_Z пока что
     RU_HA // Для 'х' (ZMK: [/P mod-morph) - Заменяем на KC_H пока что
 };
 
 // --- Комбо (ТРЕБУЕТСЯ ПРОВЕРКА И КОРРЕКТИРОВКА ИНДЕКСОВ!) ---
 #ifdef COMBO_ENABLE
 // Функция для отправки строки из PROGMEM
 #define SS_P(str) send_string_P(PSTR(str))
 
 // Сопоставление key-positions из ZMK с индексами QMK LAYOUT_universal
 // Это ПРИМЕРНОЕ сопоставление для Sofle-подобной раскладки.
 // Точные индексы зависят от того, как LAYOUT_universal определен для вашей платы.
 // Верхний ряд: 0-5 (L), 6-11 (R)
 // Второй ряд: 12-17 (L), 18-23 (R)
 // Третий ряд: 24-29 (L), 30-35 (R)
 // Нижний ряд: 36-41 (L), 42-47 (R)
 // Thumbs:     48-50 (L), 51-53 (R) // Или другое кол-во/нумерация в LAYOUT_universal! Проверьте H-файл вашей клавиатуры.
 // Примерное соответствие ZMK -> QMK (НУЖНА ПРОВЕРКА!)
 // ZMK 47, 36 -> QMK ? (R Pinky bottom, L Index bottom?) -> Например, 47, 36 ?
 // ZMK 26, 33 -> QMK ? (L Middle home, R Middle home?) -> Например, 26, 33 ?
 // ZMK 20, 21 -> QMK ? (R Index home, R Middle home?) -> Например, 20, 21 ?
 // ...и так далее
 
 enum combo_events {
     // EN/RU Combos
     EXCL_COMBO,    // ! (13, 25 -> Q W?)
     AT_COMBO,      // @ (14, 26 -> W S?)
     HASH_COMBO,    // # (15, 27 -> E D?)
     DLLR_COMBO,    // $ (16, 28 -> R F?)
     PERCNT_COMBO,  // % (29, 17 -> G T?)
     CARET_COMBO,   // ^ (18, 30 -> Y H?)
     AMPS_COMBO,    // & (19, 31 -> U J?)
     ASTRK_COMBO,   // * (20, 32 -> I K?)
     LPRN_COMBO,    // ( (21, 33 -> O L?)
     RPRN_COMBO,    // ) (22, 34 -> P ;)
     UNDS_COMBO,    // _ (Shift+Minus) (20, 19 -> I U?)
     EQL_COMBO,     // = (30, 31 -> H J?)
     DASH_COMBO,    // - (32, 31 -> K J?)
     SQT_COMBO,     // ' (46, 45 -> / .)
     DQT_COMBO,     // " (Shift+') (46, 47 -> / ?)
     GRV_COMBO,     // ` (48, 47 -> Thumb, ?)
     // RU Combos
     RU_HA_SCH_COMBO, // щ (20, 21 -> I O on RU?)
     RU_HARD_COMBO, // ъ (46, 45 -> . , on RU?)
     RU_YO_COMBO,   // ё (16, 17 -> R T on RU?)
     RU_DQT_COMBO,  // " (Shift+2) (47, 46 -> ? .)
     RU_FWSL_COMBO, // / (48, 47 -> Thumb, ?)
     RU_COMMA_COMBO,// , (Shift+6) (38, 39 -> M , ?)
     RU_DOT_COMBO,  // . (Shift+7) (40, 39 -> > , ?)
     // Layer Switching Combos
     TOGGLE_GAME,   // (47, 36 -> ? Z?)
     // Other Combos
     LEADER_C,      // (26, 33 -> S L?) -> F13
     COPY_CUT_C,    // Hold: Cut (Cmd+X), Tap: Copy (Cmd+C) (14, 15 -> W E?) -> MT?
     PASTE_C,       // Hold: Win Paste (Ctrl+V), Tap: Mac Paste (Cmd+V) (15, 16 -> E R?) -> MT?
     HTML_TAG_C,    // (28, 29 -> F G?) -> Custom Macro/Tap Dance?
     EQ_QUO_C,      // =""+left (40, 41 -> > ?) -> Custom Macro?
     SK_LSHIFT_C,   // OSM(MOD_LSFT) (25, 38 -> A , ?)
     SK_RSHIFT_C,   // OSM(MOD_RSFT) (34, 47 -> ; ?)
     // NUM Layer Combos
     DEL_C,         // Hold: Cmd+Del, Tap: Del (20, 21 on NUM layer?) -> MT?
     BSP_C,         // Hold: Cmd+Bspc, Tap: Bspc (19, 20 on NUM layer?) -> MT?
     PAR_C,         // ()+left (37, 38 on NUM layer?) -> Macro PAR
     BKT_C,         // []+left (38, 39 on NUM layer?) -> Macro BKT
     BRC_C,         // {}+left (39, 40 on NUM layer?) -> Macro BRC
     // MEDIA Layer Combos
     MUTE_C,        // (23, 22 -> [ P?)
     COMBO_COUNT
 };
 uint16_t COMBO_LEN = COMBO_COUNT; //_P for progmem version of combos
 
 // Define combos (ЗАПОЛНИТЕ ПРАВИЛЬНЫЕ ИНДЕКСЫ КЛАВИШ!)
 const uint16_t PROGMEM combo_toggle_game[] = {47, 36, COMBO_END}; // ? Z
 const uint16_t PROGMEM combo_leader[] = {26, 33, COMBO_END};      // S L
 const uint16_t PROGMEM combo_sqt[] = {46, 45, COMBO_END};         // / .
 // ... и так далее для всех комбо ...
 
 combo_t key_combos[] = {
     // EN/RU Combos (Базовые слои 0 и 1)
     [EXCL_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_1)), // Tap: Shift+1 (!), Hold: Alt+Shift+1 (?) - Уточнить ZMK поведение MT(LA(N1) LS(N1))
     [AT_COMBO]     = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_2)), // Tap: Shift+2 (@), Hold: Alt+Shift+2 (?)
     [HASH_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_3)), // Tap: Shift+3 (#), Hold: Alt+Shift+3 (?)
     [DLLR_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_4)), // Tap: Shift+4 ($), Hold: Alt+Shift+4 (?)
     [PERCNT_COMBO] = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_5)), // Tap: Shift+5 (%), Hold: Alt+Shift+5 (?)
     [CARET_COMBO]  = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_6)), // Tap: Shift+6 (^), Hold: Alt+Shift+6 (?)
     [AMPS_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_7)), // Tap: Shift+7 (&), Hold: Alt+Shift+7 (?)
     [ASTRK_COMBO]  = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_8)), // Tap: Shift+8 (*), Hold: Alt+Shift+8 (?)
     [LPRN_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_9)), // Tap: Shift+9 ((), Hold: Alt+Shift+9 (?)
     [RPRN_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_0)), // Tap: Shift+0 ()), Hold: Alt+Shift+0 (?)
     [UNDS_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_MINS)), // Tap: Shift+- (_), Hold: Alt+Shift+- (?)
     [EQL_COMBO]    = COMBO_ACTION(MT(MOD_LGUI, KC_EQL)), // Tap: =, Hold: += (?) - В ZMK было MT(PLUS EQUAL)
     [DASH_COMBO]   = COMBO_ACTION(MT(MOD_LALT | MOD_LSFT, KC_MINS)), // Tap: -, Hold: Alt+Shift+- (?) В ZMK было MT(LA(LS(MINUS)) MINUS) - уточнить!
     [SQT_COMBO]    = COMBO(combo_sqt, KC_QUOT), // Одинарный тап для одинарной кавычки. ZMK был сложнее.
     [DQT_COMBO]    = COMBO_ACTION(KC_DQUO),     // Двойная кавычка Shift+'
     [GRV_COMBO]    = COMBO_ACTION(KC_GRV),      // `
 
     // RU Combos (Слой 1)
     [RU_HA_SCH_COMBO] = COMBO_ACTION(KC_O), // щ (на O в RU раскладке?)
     [RU_HARD_COMBO] = COMBO_ACTION(KC_RBRC), // ъ (на ] в RU раскладке?)
     [RU_YO_COMBO]   = COMBO_ACTION(KC_BSLS), // ё (на \ в RU раскладке?)
     [RU_DQT_COMBO]  = COMBO_ACTION(LSFT(KC_2)), // " (Shift+2)
     [RU_FWSL_COMBO] = COMBO_ACTION(KC_SLSH), // / (ZMK был SLASH - проверить кейкод)
     [RU_COMMA_COMBO]= COMBO_ACTION(LSFT(KC_6)), // , (Shift+6)
     [RU_DOT_COMBO]  = COMBO_ACTION(LSFT(KC_7)), // . (Shift+7)
 
     // Layer Switching Combos (Слои 0, 1, 2)
     [TOGGLE_GAME]  = COMBO(combo_toggle_game, TG(_GAME)),
 
     // Other Combos
     [LEADER_C]     = COMBO(combo_leader, KC_F13), // F13 для Leader Key
     [COPY_CUT_C]   = COMBO_ACTION(MT(MOD_LGUI | MOD_LCTL, KC_X)), // Tap: Cmd+C, Hold: Cmd+X (Упрощено)
     [PASTE_C]      = COMBO_ACTION(MT(MOD_LGUI, KC_V)), // Tap: Cmd+V, Hold: Ctrl+V (Упрощено)
     [HTML_TAG_C]   = COMBO_ACTION(TAG_OPEN), // Требует макроса или TD
     [EQ_QUO_C]     = COMBO_ACTION(EQ_QUOT), // Требует макроса
     [SK_LSHIFT_C]  = COMBO_ACTION(OSM(MOD_LSFT)),
     [SK_RSHIFT_C]  = COMBO_ACTION(OSM(MOD_RSFT)),
 
     // NUM Layer Combos (Слой 3)
     [DEL_C]        = COMBO_ACTION(MT(MOD_LGUI, KC_DEL)), // Tap: Del, Hold: Cmd+Del (Упрощено)
     [BSP_C]        = COMBO_ACTION(MT(MOD_LGUI, KC_BSPC)),// Tap: Bspc, Hold: Cmd+Bspc (Упрощено)
     [PAR_C]        = COMBO_ACTION(PAR), // Макрос
     [BKT_C]        = COMBO_ACTION(BKT), // Макрос
     [BRC_C]        = COMBO_ACTION(BRC), // Макрос
 
     // MEDIA Layer Combos (Слой 5)
     [MUTE_C]       = COMBO_ACTION(KC_MUTE),
 };
 
 // Включить обработку комбо в process_record_user
 // uint16_t process_combo_event(uint16_t combo_index, bool pressed) {
 //     switch(combo_index) {
 //         // Обработка сложных комбо, если нужно
 //     }
 //     return true; // Return true to keep processing keycodes after combo.
 // }
 #endif // COMBO_ENABLE
 
 
 // --- Tap Dance ---
 #ifdef TAP_DANCE_ENABLE
 typedef enum {
     TD_NONE,
     TD_UNKNOWN,
     TD_PLAY_NEXT_PREV
 } td_state_t;
 
 // Определения Tap Dance
 qk_tap_dance_action_t tap_dance_actions[] = {
     [TD_PLAYNP] = ACTION_TAP_DANCE_TRIPLE(KC_MPLY, KC_MNXT, KC_MPRV) // Tap: Play/Pause, Double Tap: Next, Triple Tap: Prev
 };
 
 // Определить состояние (не обязательно для простых TD)
 // static td_state_t td_cur_state = TD_NONE;
 
 // Функции Tap Dance (если нужна кастомная логика)
 // void playnp_finished (qk_tap_dance_state_t *state, void *user_data) { ... }
 // void playnp_reset (qk_tap_dance_state_t *state, void *user_data) { ... }
 
 #endif // TAP_DANCE_ENABLE
 
 
 // --- Основной массив раскладок ---
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
     [_DFLT] = LAYOUT_universal( // Слой 0: Default EN (База из ZMK)
         // Left Hand
         ESC_SYS,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,
         KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,
         KC_LCTL,   A_LSFT,    S_LCTL,    D_LALT,    F_LGUI,    KC_G, // LCTL вместо MT(LC(LA(LCMD))) TAB из ZMK - Уточнить!
         GRAVE_SYS, KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_MPLY, // Grave_SYS вместо &lt 5 GRAVE; KC_MPLY вместо C_PLAY_PAUSE
                                KC_DEL,    KC_LGUI,   BSPC_FUNC, SPC_NUM,   ENT_MEDIA, // KC_LGUI вместо LS(LC(LA(LCMD))); DEL вместо MT CAPS DEL
         // Right Hand
                                KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_BSPC,
                                KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC, // [
                                KC_H,      J_RGUI,    K_RALT,    L_RCTL,    SCLN_RSFT, KC_QUOT, // ' вместо MT(LC(LA(LCMD))) SQT - Уточнить!
                  KC_MUTE,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   BSLH_MED,// MUTE вместо K_MUTE; / вместо MT QMARK SLASH; BSLH_MED вместо &lt 5 BSLH
                                ENT_MEDIA, SPC_NUM,   BSPC_FUNC, KC_RGUI,   KC_DEL // RGUT вместо RS(RA(RC(RCMD))); DEL вместо MT CAPS DEL
     ),
 
     [_RU] = LAYOUT_universal( // Слой 1: Russian
         // Left Hand
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         // Right Hand
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, RU_Z,    RU_HA,   KC_TRNS, // RU_Z -> я, RU_HA -> х - требуют кастомной логики или просто KC_Z, KC_H
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUOT, KC_TRNS, // ' вместо MT QMARK APOS - Уточнить!
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
         // Примечание: На этом слое в ZMK было много &trans.
         // Основная логика - переключение раскладки в ОС через RU_ON/RU_OFF
         // и обработка 'я', 'х', 'щ', 'ъ', 'ё', ',', '.' через комбо или mod-morph.
         // Комбо для RU определены выше. Mod-morph требуют кастомной логики.
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
                  KC_TRNS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
 
     [_NUM] = LAYOUT_universal( // Слой 3: Numbers and Navigation (перенесено из ZMK)
         // Left Hand
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_TRNS, KC_NO,   KC_P7,   KC_P8,   KC_P9,   MT(MOD_LSFT, KC_PAST), // MT KP_ASTERISK PLUS -> Shift+* ? Уточнить!
         KC_TRNS, MT(MOD_LSFT, KC_SCLN), MT(MOD_LCTL,KC_P4), MT(MOD_LALT,KC_P5), MT(MOD_LGUI,KC_P6), MT(MOD_LSFT, KC_PSLS), // MT(... N4/5/6) -> ? Уточнить!
         KC_TRNS, KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_P0,   KC_NO, // Был &trans
                                KC_LPRN, KC_RPRN, KC_PDOT, KC_TRNS, KC_TRNS, // ( ) .
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO,
                                KC_HOME, LALT(KC_LEFT), KC_UP, LALT(KC_RIGHT), KC_END, KC_NO,
                                KC_PGUP, KC_LEFT, KC_DOWN,    KC_RIGHT, KC_NO,   KC_NO,
                  KC_TRNS,      KC_PGDN, LGUI(KC_LBRC), LGUI(KC_RBRC), RSFT(RCTL(KC_TAB)), RCTL(KC_TAB), KC_TRNS, // Команды навигации табов Mac/Win?
                                KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
     ),
 
     [_FUNC] = LAYOUT_universal( // Слой 4: Function keys and Symbols (перенесено из ZMK symb)
         // Left Hand
         KC_TRNS, KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,
         KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,      KC_F6,
         KC_F7,   KC_F8,   KC_F9,   KC_F10,     KC_F11,     KC_F12,
         KC_SLSH, PAR,     TAG_OPEN,BKT,        BRC,        MT(MOD_LSFT, KC_BSLS), KC_NO, // / () <> [] {} | (Shift+\)
                                KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,
         // Right Hand
                                KC_NO,   KC_EXLM, KC_AT,      KC_HASH,    KC_DLR,     KC_PERC, // ! @ # $ %
                                KC_NO,   KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN, // ^ & * ( )
                                KC_TRNS, KC_PIPE, KC_MINS,    KC_UNDS,    KC_EQL,     KC_PLUS, // | - _ = +
                  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_QUES,    KC_NO, // ?
                                KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS
         // Примечание: ZMK макросы для парных символов заменены на кастомные кейкоды PAR, BKT, BRC, TAG_OPEN.
         // Они требуют реализации в process_record_user. MT PIPE BSLH заменены на KC_PIPE и MT(MOD_LSFT, KC_BSLS).
     ),
 
     [_MEDIA] = LAYOUT_universal( // Слой 5: Media keys and Shortcuts (перенесено из ZMK media)
         // Left Hand
         KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO, // BT команды пропущены
         KC_NO,   LSFT(LGUI(KC_1)), LSFT(LGUI(KC_2)), LGUI(LSFT(KC_3)), LSFT(LGUI(KC_4)), LSFT(LGUI(KC_5)), // Ярлыки?
         KC_NO,   LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_NO,      KC_NO,      KC_NO, // Навигация по табам Ctrl+Left/Right?
         KC_NO,   LGUI(KC_Z), LGUI(LSFT(KC_Z)), KC_NO,      KC_NO,      KC_NO,      KC_MUTE,
                                OSM(MOD_LALT | MOD_LCTL | MOD_LSFT | MOD_LGUI), OSM(MOD_CAPS), KC_DEL, KC_NO, KC_NO, // Sticky Mods + Del
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                                KC_NO,   KC_NO,   KC_NO,      TD(TD_PLAYNP), KC__VOLDOWN, KC__VOLUP, // Tap Dance Play/Next/Prev
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                  KC_NO,      KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,
                                KC_NO,   KC_DEL,  OSM(MOD_CAPS), OSM(MOD_RALT | MOD_RCTL | MOD_RSFT | MOD_RGUI) // Sticky Mods + Del
         // Примечание: BT команды пропущены. &sk заменены на OSM().
     ),
 
     [_STCKY] = LAYOUT_universal( // Слой 6: Sticky Mods Layer (перенесено из ZMK sticky)
         // Left Hand
         KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,
         KC_NO,   KC_NO,   LGUI(KC_LEFT), LGUI(KC_RIGHT), LGUI(KC_R), LGUI(KC_T), // Mac команды?
         OSM(MOD_LALT | MOD_LCTL | MOD_LSFT | MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), LGUI(KC_G), // Sticky Mods + Cmd+G
         KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                KC_TRNS, RU_OFF,  RU_ON,      OSL_NUM,    KC_TRNS, // OSL_NUM вместо num_word
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                                KC_NO,   KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,
                                KC_NO,   OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), OSM(MOD_RSFT), OSM(MOD_LALT | MOD_LCTL | MOD_LSFT | MOD_LGUI),
                  KC_NO,      KC_NO,   KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,
                                KC_TRNS, RU_ON,   RU_OFF,     KC_TRNS,    KC_TRNS
         // Примечание: &sk заменены на OSM(). &num_word заменен на OSL(_NUM). RU_ON/RU_OFF требуют макросов.
     ),
 
     [_SYS] = LAYOUT_universal( // Слой 7: System Layer (перенесено из ZMK system)
         // Left Hand
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // OUT_USB/BLE пропущены
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,
                                KC_NO,   KC_NO,   QK_BOOT, QK_BOOT, KC_NO, // Bootloader слева/по центру
         // Right Hand
                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // BT_PRV/NXT пропущены
                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // BT_SEL/EP_OFF пропущены
                  KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, // BT_DISC/CLR пропущены
                                KC_NO,   QK_BOOT, QK_BOOT, KC_NO,   KC_NO // Bootloader справа
         // Примечание: Большинство BT/Output/Power команд пропущено. &soft_off заменен на RESET. &bootloader заменен на QK_BOOT. Макросы upd_fw пропущены.
     )
 };
 
 // --- Обработка кастомных кейкодов, макросов, комбо ---
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     #ifdef COMBO_ENABLE
     if (!process_combo_record(keycode, record)) {
         return false;
     }
     // Process combos first - Important!
     process_combo_event(keycode, record->event.pressed);
     #endif
 
     switch (keycode) {
         case RU_ON:
             if (record->event.pressed) {
                 layer_on(_RU);
                 // Опционально: Отправить шорткат для смены раскладки ОС
                 // SEND_STRING(SS_LSFT(SS_LALT(SS_LCTL(SS_LGUI("n"))))); // Пример для сложного шортката из ZMK
                 SEND_STRING(SS_LCTL(" ")); // Пример для Ctrl+Space
             }
             return false; // Skip default processing
         case RU_OFF:
             if (record->event.pressed) {
                 layer_off(_RU);
                 // Опционально: Отправить шорткат для смены раскладки ОС
                 // SEND_STRING(SS_LSFT(SS_LALT(SS_LCTL(SS_LGUI("m"))))); // Пример
                 SEND_STRING(SS_LCTL(" ")); // Пример для Ctrl+Space
             }
             return false; // Skip default processing
 
         // --- Макросы (Примеры реализации) ---
         case PAR: // ()+left
             if (record->event.pressed) {
                 SEND_STRING("()");
                 TAP_CODE(KC_LEFT);
             }
             return false;
         case BKT: // []+left
              if (record->event.pressed) {
                 // Опционально: убедиться что активен EN слой перед отправкой
                 // if (IS_LAYER_ON(_RU)) { layer_off(_RU); SEND_STRING(SS_LCTL(" ")); wait_ms(50); }
                 SEND_STRING("[]");
                 TAP_CODE(KC_LEFT);
             }
             return false;
         case BRC: // {}+left
              if (record->event.pressed) {
                 // Опционально: убедиться что активен EN слой
                 // if (IS_LAYER_ON(_RU)) { layer_off(_RU); SEND_STRING(SS_LCTL(" ")); wait_ms(50); }
                 SEND_STRING("{}");
                 TAP_CODE(KC_LEFT);
             }
             return false;
         case TAG_OPEN: // <>+left
             if (record->event.pressed) {
                 // Опционально: убедиться что активен EN слой
                 // if (IS_LAYER_ON(_RU)) { layer_off(_RU); SEND_STRING(SS_LCTL(" ")); wait_ms(50); }
                 SEND_STRING("<>");
                 TAP_CODE(KC_LEFT);
             }
             return false;
          case TAG_CLOSE: // </>
              if (record->event.pressed) {
                 // Опционально: убедиться что активен EN слой
                 // if (IS_LAYER_ON(_RU)) { layer_off(_RU); SEND_STRING(SS_LCTL(" ")); wait_ms(50); }
                 SEND_STRING("</"); // ZMK был сложнее, это упрощение
             }
             return false;
         case EQ_QUOT: // =""+left
             if (record->event.pressed) {
                 SEND_STRING("=\"\"");
                 TAP_CODE(KC_LEFT);
             }
             return false;
 
         // Обработка других кастомных кейкодов если нужно
         // case RU_Z: ...
         // case RU_HA: ...
 
         // --- Leader Key (Пример) ---
         #ifdef LEADER_ENABLE
         case LEADER_KEY:
             if (record->event.pressed) {
                 leader_start();
             }
             return false;
         #endif
     }
     return true; // Process all other keycodes normally
 }
 
 
 // --- Опционально: Логика Leader Key ---
 #ifdef LEADER_ENABLE
 void leader_end_user(void) {
     if (leader_sequence_one_key(KC_F)) {
         if (leader_sequence_one_key(KC_S)) { // Leader F S -> fs
             SEND_STRING("leader fs macro"); // Замените на нужный макрос/действие
         } else if (leader_sequence_one_key(KC_W)) { // Leader F W -> fw
             SEND_STRING("leader fw macro");
         } // ... другие последовательности на F
     } else if (leader_sequence_one_key(KC_B)) {
          if (leader_sequence_one_key(KC_A)) { // Leader B A -> ba
             SEND_STRING("leader ba macro");
         } // ... другие последовательности на B
     }
     // ... другие начальные клавиши для Leader
 }
 #endif
 
 
 // --- Обработка состояния слоев (можно удалить или адаптировать) ---
 layer_state_t layer_state_set_user(layer_state_t state) {
     // Убираем авто-включение scroll mode из дефолтного keymap.c,
     // так как слой 3 теперь используется для _NUM
     // keyball_set_scroll_mode(get_highest_layer(state) == 3);
     return state;
 }


#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
