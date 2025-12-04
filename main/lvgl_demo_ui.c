#include "lvgl.h"
#include <time.h>
#include <stdio.h>

static lv_obj_t * time_label;
static lv_obj_t * date_label;

static void update_time(lv_timer_t * timer)
{
    time_t now;
    struct tm * timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    
    // Mock time if not set (e.g. 1970)
    if (timeinfo->tm_year < 100) {
        timeinfo->tm_hour = 10;
        timeinfo->tm_min = 23;
        timeinfo->tm_mon = 11; // Dec
        timeinfo->tm_mday = 4;
        timeinfo->tm_wday = 4; // Thu
    }

    lv_label_set_text_fmt(time_label, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
    
    char date_str[32];
    // Format: 12/04 Thu
    const char * week_days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    snprintf(date_str, sizeof(date_str), "%02d/%02d %s", timeinfo->tm_mon + 1, timeinfo->tm_mday, week_days[timeinfo->tm_wday]);
    lv_label_set_text(date_label, date_str);
}

void example_lvgl_demo_ui(lv_display_t *disp)
{
    lv_obj_t *scr = lv_display_get_screen_active(disp);
    
    // Background - Black
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    // Wave effect - A subtle blue gradient or shape at the bottom
    // Mimicking the PSP Go "Wave" style
    lv_obj_t * wave = lv_obj_create(scr);
    lv_obj_set_size(wave, 800, 300);
    lv_obj_align(wave, LV_ALIGN_BOTTOM_MID, 0, 150);
    lv_obj_set_style_radius(wave, LV_RADIUS_CIRCLE, 0); 
    lv_obj_set_style_bg_color(wave, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_set_style_bg_opa(wave, LV_OPA_40, 0);
    lv_obj_set_style_border_width(wave, 0, 0);
    lv_obj_remove_flag(wave, LV_OBJ_FLAG_SCROLLABLE);

    // Another wave layer for depth
    lv_obj_t * wave2 = lv_obj_create(scr);
    lv_obj_set_size(wave2, 700, 250);
    lv_obj_align(wave2, LV_ALIGN_BOTTOM_MID, 50, 120);
    lv_obj_set_style_radius(wave2, LV_RADIUS_CIRCLE, 0); 
    lv_obj_set_style_bg_color(wave2, lv_palette_lighten(LV_PALETTE_BLUE, 2), 0);
    lv_obj_set_style_bg_opa(wave2, LV_OPA_30, 0);
    lv_obj_set_style_border_width(wave2, 0, 0);
    lv_obj_remove_flag(wave2, LV_OBJ_FLAG_SCROLLABLE);

    // Time Label
    time_label = lv_label_create(scr);
    lv_obj_set_style_text_color(time_label, lv_color_white(), 0);
    // Scale: 256 is 1x. 
    // Assuming base font is small (14px), we scale up significantly.
    // 6x scale -> ~84px height
    lv_obj_set_style_transform_scale(time_label, 1536, 0); 
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, -50);

    // Date Label
    date_label = lv_label_create(scr);
    lv_obj_set_style_text_color(date_label, lv_palette_lighten(LV_PALETTE_GREY, 1), 0);
    // Scale: 2x scale -> ~28px height
    lv_obj_set_style_transform_scale(date_label, 512, 0);
    lv_obj_align(date_label, LV_ALIGN_CENTER, 0, 50);

    // Timer to update time
    lv_timer_create(update_time, 1000, NULL);
    
    // Initial update
    update_time(NULL);
}
