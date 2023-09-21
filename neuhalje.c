// Copyright 2022 @jens neuhalfen
// SPDX-License-Identifier: GPL-2.0+

#include "neuhalje.h"
#include QMK_KEYBOARD_H

bool led_update_user(led_t led_state) {
    // force NUM LOCK OFF (it makes ":" under macos emacs beahave wierd)
    if (led_state.num_lock) {
        tap_code(KC_NUM_LOCK);
    }
    return true;
}
