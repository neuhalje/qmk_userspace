// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include QMK_KEYBOARD_H
#include "keymap_german.h"

// Layer and mod tap bits
// 0xff00 bitmask
#define QK_LAYER_TAP_0  0x4000
#define QK_LAYER_TAP_1  0x4100
#define QK_LAYER_TAP_2  0x4200
#define QK_LAYER_TAP_3  0x4300
#define QK_MOD_TAP_LCTL 0x6100
#define QK_MOD_TAP_LSFT 0x6200
#define QK_MOD_TAP_LALT 0x6400
#define QK_MOD_TAP_LGUI 0x6800
// 0xf000 bitmask
#define QK_LMOD_TAP 0x6000
#define QK_RMOD_TAP 0x7000

/* (kc >> 8) & 0x1f for mod-tap bits
 * (kc & 0x1f) for osm bits
 * Mod bits:    43210
 *   bit 0      ||||+- Control
 *   bit 1      |||+-- Shift
 *   bit 2      ||+--- Alt
 *   bit 3      |+---- Gui
 *   bit 4      +----- LR flag(Left:0, Right:1)
 */

// Macro for LT(0,kc) mod tap. Return true for kc on tap
// send custom tap code on hold after TAPPING_TERM
#define TAP_HOLD(_hold_) \
	if (record->tap.count) return true; \
	else if (record->event.pressed) tap_code16(_hold_); \
	return false

// Macro to send oneshot mod on tap with mod tap keys
// like LT(1,MOD_LSFT)
#define MT_OSM(_mod_) \
	if (record->tap.count && record->event.pressed) { \
		add_oneshot_mods(_mod_); return false; \
	}
