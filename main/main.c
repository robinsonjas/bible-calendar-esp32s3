#include "ui_test.h"

#include "esp_log.h"
#include "lvgl.h"

#if __has_include("esp_lvgl_port.h")
#include "esp_lvgl_port.h"
#define UI_TEST_USE_LVGL_PORT 1
#else
#define UI_TEST_USE_LVGL_PORT 0
#endif

static const char *MAIN_UI_TAG = "main_ui";

void app_main(void)
{
    lv_init();

    if (lv_disp_get_default() == NULL) {
        ESP_LOGE(MAIN_UI_TAG, "LVGL display not registered; UI not created");
        return;
    }

#if UI_TEST_USE_LVGL_PORT
    lvgl_port_lock(0);
    ui_test_create();
    lvgl_port_unlock();
#else
    ui_test_create();
#endif
}
