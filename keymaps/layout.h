// Copyright 2021 @filterpaper
// SPDX-License-Identifier: GPL-2.0+
#pragma once

// including keymap_german REALLY f*s up compilation
// take the easy way: Copy & paste
// #include "keymap_german.h"
// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ^ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ß │ ´ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ Ü │ + │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ # │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DE_CIRC KC_GRV  // ^ (dead)
#define DE_1    KC_1    // 1
#define DE_2    KC_2    // 2
#define DE_3    KC_3    // 3
#define DE_4    KC_4    // 4
#define DE_5    KC_5    // 5
#define DE_6    KC_6    // 6
#define DE_7    KC_7    // 7
#define DE_8    KC_8    // 8
#define DE_9    KC_9    // 9
#define DE_0    KC_0    // 0
#define DE_SS   KC_MINS // ß
#define DE_ACUT KC_EQL  // ´ (dead)
// Row 2
#define DE_Q    KC_Q    // Q
#define DE_W    KC_W    // W
#define DE_E    KC_E    // E
#define DE_R    KC_R    // R
#define DE_T    KC_T    // T
#define DE_Z    KC_Y    // Z
#define DE_U    KC_U    // U
#define DE_I    KC_I    // I
#define DE_O    KC_O    // O
#define DE_P    KC_P    // P
#define DE_UDIA KC_LBRC // Ü
#define DE_PLUS KC_RBRC // +
// Row 3
#define DE_A    KC_A    // A
#define DE_S    KC_S    // S
#define DE_D    KC_D    // D
#define DE_F    KC_F    // F
#define DE_G    KC_G    // G
#define DE_H    KC_H    // H
#define DE_J    KC_J    // J
#define DE_K    KC_K    // K
#define DE_L    KC_L    // L
#define DE_ODIA KC_SCLN // Ö
#define DE_ADIA KC_QUOT // Ä
#define DE_HASH KC_NUHS // #
// Row 4
#define DE_LABK KC_NUBS // <
#define DE_Y    KC_Z    // Y
#define DE_X    KC_X    // X
#define DE_C    KC_C    // C
#define DE_V    KC_V    // V
#define DE_B    KC_B    // B
#define DE_N    KC_N    // N
#define DE_M    KC_M    // M
#define DE_COMM KC_COMM // ,
#define DE_DOT  KC_DOT  // .
#define DE_MINS KC_SLSH // -

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ° │ ! │ " │ § │ $ │ % │ & │ / │ ( │ ) │ = │ ? │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │ * │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │ ' │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ > │   │   │   │   │   │   │   │ ; │ : │ _ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DE_DEG  S(DE_CIRC) // °
#define DE_EXLM S(DE_1)    // !
#define DE_DQUO S(DE_2)    // "
#define DE_SECT S(DE_3)    // §
#define DE_DLR  S(DE_4)    // $
#define DE_PERC S(DE_5)    // %
#define DE_AMPR S(DE_6)    // &
#define DE_SLSH S(DE_7)    // /
#define DE_LPRN S(DE_8)    // (
#define DE_RPRN S(DE_9)    // )
#define DE_EQL  S(DE_0)    // =
#define DE_QUES S(DE_SS)   // ?
#define DE_GRV  S(DE_ACUT) // ` (dead)
// Row 2
#define DE_ASTR S(DE_PLUS) // *
// Row 3
#define DE_QUOT S(DE_HASH) // '
// Row 4
#define DE_RABK S(DE_LABK) // >
#define DE_SCLN S(DE_COMM) // ;
#define DE_COLN S(DE_DOT)  // :
#define DE_UNDS S(DE_MINS) // _

/* AltGr symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │ ² │ ³ │   │   │   │ { │ [ │ ] │ } │ \ │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ @ │   │ € │   │   │   │   │   │   │   │   │ ~ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ | │   │   │   │   │   │   │ µ │   │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define DE_SUP2 ALGR(DE_2)    // ²
#define DE_SUP3 ALGR(DE_3)    // ³
#define DE_LCBR ALGR(DE_7)    // {
#define DE_LBRC ALGR(DE_8)    // [
#define DE_RBRC ALGR(DE_9)    // ]
#define DE_RCBR ALGR(DE_0)    // }
#define DE_BSLS ALGR(DE_SS)   // (backslash)
// Row 2
#define DE_AT   ALGR(DE_Q)    // @
#define DE_EURO ALGR(DE_E)    // €
#define DE_TILD ALGR(DE_PLUS) // ~
// Row 4
#define DE_PIPE ALGR(DE_LABK) // |
#define DE_MICR ALGR(DE_M)    // µ
// END keymap_german.h
#define LAYER_BASE 0
#define LAYER_UMLAUT 1
#define LAYER_EXT 2
#define LAYER_SYMBOL 3
#define LAYER_FUN 4
#define LAYER_SYMBOL2 5

// OS X shortcuts
#define Z_UND G(KC_Z)
#define Z_CUT G(KC_X)
#define Z_CPY G(KC_C)
#define Z_PST G(KC_V)
#define Z_LOCK C(G(KC_Q))
#define Z_SLEEP A(G(KC_PWR))
#define Z_SHUT C(A(G(KC_PWR)))

// Tap hold macros
#define M_TH LT(0, KC_M)
#define COMM_TH LT(0, KC_COMM)
#define DOT_TH LT(0, KC_DOT)
#define SLSH_TH LT(0, KC_SLSH)
#define TH(k1, k2, k3, k4) LT(0, k1), LT(0, k2), LT(0, k3), LT(0, k4)

// Home row mod-tap macros
#define HM_A SFT_T(KC_A)
#define HM_S ALT_T(KC_S)
#define HM_D CTL_T(KC_D)
#define HM_F GUI_T(KC_F)
#define HM_J GUI_T(KC_J)
#define HM_K CTL_T(KC_K)
#define HM_L ALT_T(KC_L)
#define HM_QUOT SFT_T(KC_QUOT)
#define HRML(k1, k2, k3, k4) SFT_T(k1), ALT_T(k2), CTL_T(k3), GUI_T(k4)
#define HRMR(k1, k2, k3, k4) GUI_T(k1), CTL_T(k2), ALT_T(k3), SFT_T(k4)

// One shot mods
#ifdef NO_ACTION_ONESHOT
#    define OSM_SFT KC_LSFT
#    define OSM_CTL KC_LCTL
#    define OSM_ALT KC_LALT
#    define OSM_GUI KC_LGUI
#else
#    define OSM_SFT OSM(MOD_LSFT)
#    define OSM_CTL OSM(MOD_LCTL)
#    define OSM_ALT OSM(MOD_LALT)
#    define OSM_GUI OSM(MOD_LGUI)
#endif
