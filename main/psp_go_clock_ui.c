#include "lvgl.h"
#include <time.h>

// Timer callback to update the clock display
static void update_clock_cb(lv_timer_t *timer)
{
    lv_obj_t *time_label = (lv_obj_t *)lv_timer_get_user_data(timer);
    lv_obj_t *date_label = lv_obj_get_parent(time_label);
    date_label = lv_obj_get_child(lv_obj_get_parent(time_label), 1);
    
    // Get current time
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    
    // Format time string (HH:MM:SS)
    char time_str[16];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", timeinfo);
    lv_label_set_text(time_label, time_str);
    
    // Format date string (YYYY-MM-DD Day)
    char date_str[32];
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", timeinfo);
    lv_label_set_text(date_label, date_str);
}

void example_lvgl_demo_ui(lv_display_t *disp)
{
    // Get the active screen
    lv_obj_t *scr = lv_screen_active();
    
    // Set screen background to black
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
    
    // Get screen dimensions for layout
    lv_coord_t scr_width = lv_display_get_physical_horizontal_resolution(disp);
    lv_coord_t scr_height = lv_display_get_physical_vertical_resolution(disp);
    
    // Create main container for clock elements
    lv_obj_t *main_cont = lv_obj_create(scr);
    lv_obj_set_size(main_cont, scr_width, scr_height);
    lv_obj_set_pos(main_cont, 0, 0);
    lv_obj_set_style_bg_color(main_cont, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(main_cont, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(main_cont, 0, 0);
    lv_obj_set_style_pad_all(main_cont, 0, 0);
    
    // Create time label with large font
    lv_obj_t *time_label = lv_label_create(main_cont);
    lv_label_set_text(time_label, "00:00:00");
    
    // Set time label style - large blue text
    lv_obj_set_style_text_color(time_label, lv_color_make(100, 200, 255), 0);  // Light blue
    lv_obj_set_style_text_align(time_label, LV_TEXT_ALIGN_CENTER, 0);
    
    // Position time label in the upper-middle area
    lv_obj_set_pos(time_label, scr_width / 2 - 120, scr_height / 2 - 80);
    lv_obj_set_size(time_label, 240, 120);
    
    // Create date label
    lv_obj_t *date_label = lv_label_create(main_cont);
    lv_label_set_text(date_label, "0000-00-00");
    
    // Set date label style - smaller text
    lv_obj_set_style_text_color(date_label, lv_color_make(150, 150, 255), 0);  // Light purple
    lv_obj_set_style_text_align(date_label, LV_TEXT_ALIGN_CENTER, 0);
    
    // Position date label below time
    lv_obj_set_pos(date_label, scr_width / 2 - 100, scr_height / 2 + 60);
    lv_obj_set_size(date_label, 200, 60);
    
    // Create decorative lines/borders using rectangles
    lv_obj_t *top_line = lv_obj_create(main_cont);
    lv_obj_set_size(top_line, scr_width, 2);
    lv_obj_set_pos(top_line, 0, scr_height / 2 - 20);
    lv_obj_set_style_bg_color(top_line, lv_color_make(80, 150, 255), 0);
    lv_obj_set_style_border_width(top_line, 0, 0);
    
    lv_obj_t *bottom_line = lv_obj_create(main_cont);
    lv_obj_set_size(bottom_line, scr_width, 2);
    lv_obj_set_pos(bottom_line, 0, scr_height / 2 + 150);
    lv_obj_set_style_bg_color(bottom_line, lv_color_make(80, 150, 255), 0);
    lv_obj_set_style_border_width(bottom_line, 0, 0);
    
    // Create status indicator at the bottom
    lv_obj_t *status_label = lv_label_create(main_cont);
    lv_label_set_text(status_label, "PSP GO CLOCK");
    lv_obj_set_style_text_color(status_label, lv_color_make(100, 200, 255), 0);
    lv_obj_set_style_text_align(status_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(status_label, 0, scr_height - 40);
    lv_obj_set_size(status_label, scr_width, 30);
    
    // Create timer to update clock every second
    lv_timer_t *clock_timer = lv_timer_create(update_clock_cb, 1000, time_label);
    lv_timer_set_repeat_count(clock_timer, -1);  // Infinite repeat
    
    // Initial update
    update_clock_cb(clock_timer);
}
