#include "ui_test.h"

#include "esp_log.h"
#include "lvgl.h"

static const char *UI_TEST_TAG = "ui_test";

static lv_obj_t *s_status_label;
static bool s_status_dot;

static void status_timer_cb(lv_timer_t *timer)
{
    (void)timer;

    if (s_status_label == NULL) {
        return;
    }

    s_status_dot = !s_status_dot;
    lv_label_set_text(s_status_label, s_status_dot ? "UI OK •" : "UI OK");
}

static void button_event_cb(lv_event_t *event)
{
    if (lv_event_get_code(event) != LV_EVENT_CLICKED) {
        return;
    }

    ESP_LOGI(UI_TEST_TAG, "Button pressed");

    if (s_status_label != NULL) {
        lv_label_set_text(s_status_label, "Button pressed ✅");
    }
}

void ui_test_create(void)
{
    lv_obj_t *screen = lv_scr_act();
    lv_obj_t *container = lv_obj_create(screen);
    lv_obj_set_size(container, 760, 440);
    lv_obj_center(container);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title_label = lv_label_create(container);
    lv_label_set_text(title_label, "HELLO ELECROW");
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_28, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 16);

    s_status_label = lv_label_create(container);
    lv_label_set_text(s_status_label, "UI OK");
    lv_obj_set_style_text_font(s_status_label, &lv_font_montserrat_20, 0);
    lv_obj_align_to(s_status_label, title_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 12);

    lv_obj_t *button = lv_btn_create(container);
    lv_obj_set_size(button, 260, 90);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_event_cb(button, button_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *button_label = lv_label_create(button);
    lv_label_set_text(button_label, "Tap Me");
    lv_obj_set_style_text_font(button_label, &lv_font_montserrat_20, 0);
    lv_obj_center(button_label);

    lv_timer_create(status_timer_cb, 500, NULL);
}
