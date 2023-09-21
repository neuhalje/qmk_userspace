// Copyright 2023 neuhalje
// SPDX-License-Identifier: GPL-2.0+

/*
   Usage guide
   1 Place this file next to keymap.c or in userspace.
   2 Add the following lines into rules.mk:
        OLED_ENABLE = yes
        SRC += oled-version.c
   3 The 'oled_task_user()' calls 'render_mod_status()' for secondary OLED.
     It can be replaced with your own function, or deleted.
*/

#include QMK_KEYBOARD_H
#include "my_version.h"
#include "version.h"

static void render_firmware_version(void) {
    oled_write_ln_P(PSTR("QMK version:\n  " QMK_VERSION "\nKeymap version:\n  " MY_KEYMAP_VERSION), false);
}

#ifndef CMK
#    define CMK 1
#endif

static void render_version_status(void) {
    //    if (timer_elapsed32(tap_timer) > OLED_TIMEOUT) {
    //        oled_off();
    //    } else {
    render_firmware_version();
    //    }
}

// Init and rendering calls
oled_rotation_t oled_init_user(oled_rotation_t const rotation) {
    if (is_keyboard_master()) {
        return is_keyboard_left() ? rotation : OLED_ROTATION_180;
    } else {
        return OLED_ROTATION_270;
    }
}

bool oled_task_user(void) {
    extern void render_mod_status(void);
    is_keyboard_master() ? render_version_status() : render_mod_status();
    return false;
}
