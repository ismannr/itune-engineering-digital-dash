//
// Created by Isyman Nurfauzan Rustama on 4/19/2026.
// Copyright (c) 2026 I-Tune Engineering. All rights reserved.
//

#include "lvgl/lvgl.h"
#include "ui/ui.h"

// =========================================================================
// --- SIMULATOR ONLY START ---
// =========================================================================

#include "SDL_main.h"

/* Windows SDL2 Linker Bridge */
#ifdef _WIN32
#undef main
int SDL_main(int argc, char *argv[]) {
    return main(argc, argv);
}
#endif

/* PC Simulator Display & Mouse Setup */
static lv_display_t * hal_init(int32_t w, int32_t h)
{
    lv_group_set_default(lv_group_create());

    /* Create a desktop window */
    lv_display_t * disp = lv_sdl_window_create(w, h);

    /* Create a simulated touch screen using the PC mouse */
    lv_indev_t * mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, disp);
    lv_display_set_default(disp);

    /* Set up the mouse cursor icon */
    LV_IMAGE_DECLARE(mouse_cursor_icon);
    lv_obj_t * cursor_obj = lv_image_create(lv_screen_active());
    lv_image_set_src(cursor_obj, &mouse_cursor_icon);
    lv_indev_set_cursor(mouse, cursor_obj);

    return disp;
}
// =========================================================================
// --- SIMULATOR ONLY END ---
// =========================================================================


int main(int argc, char **argv)
{
    /* 1. Initialize LVGL core */
    lv_init();

    /* 2. Initialize the display and input devices */
    // --- SIMULATOR ONLY! ---
    hal_init(1024, 600);
    // --- ON ESP32: call custom MIPI-DSI init function here ---

    /* 3. Initialize your custom UI */
    ui_init();

    // This will draw a border around your active screen so you can see where it actually is
    lv_obj_set_style_border_color(lv_screen_active(), lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_border_width(lv_screen_active(), 5, 0);

    /* 4. The Main Loop */
    while(1) {
        /* Periodically call the lv_timer_handler to render graphics and read touches */
        uint32_t time_until_next = lv_timer_handler();

        if (time_until_next == LV_NO_TIMER_READY) {
            time_until_next = LV_DEF_REFR_PERIOD; /* Default sleep time */
        }

        /* Sleep until the next frame needs to be drawn */
        // --- SIMULATOR ONLY: Uses SDL delay ---
        lv_delay_ms(time_until_next);
        // --- ON ESP32: Replace this with vTaskDelay(pdMS_TO_TICKS(time_until_next)); ---
    }

    return 0;
}