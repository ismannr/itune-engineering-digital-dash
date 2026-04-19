//
// Created by Isyman Nurfauzan Rustama on 4/19/2026.
// Copyright (c) 2026 I-Tune Engineering. All rights reserved.
//

#include "ui.h"

void ui_init(void) {
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Dashboard Simulator Ready!");
    lv_obj_center(label);
}
