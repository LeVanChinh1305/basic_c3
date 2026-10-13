#include "app_common.h"
#include "app_console.h"
#include "app_littlefs.h"
#include "nvs_flash.h"
#include "app_blemesh.h"

static const char *TAG = "APP_MAIN";

void app_main_InitNvs(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void app_main(void)
{
    LREP(TAG, "========================================");
    LREP(TAG, "  %s  v%s", DF_FIRMWARE_NAME, app_common_GetVersion());
    LREP(TAG, "  Target : %s | HW: %s", CONFIG_IDF_TARGET, DF_HARDWARE_VERSION);
    LREP(TAG, "========================================");

    app_console_Init();
    app_main_InitNvs();
    app_littlefs_Init();

#if DF_ENABLE_BLE_MESH
    /* Khoi dong BLE Mesh sau LittleFS (can doc /storage/mesh_node.json) */
    if (app_mesh_Init() != ERROR_CODE_OK) {
        LREP_ERROR(TAG, "Khoi dong BLE Mesh THAT BAI!");
    }
#endif

    uint32_t u32Count100ms = 0;

    /* app_main co the tiep tuc lam viec khac hoac ket thuc */
    while (1) {
        /* Moi 100ms tang bien dem */
        u32Count100ms++;

        /* Moi 10 giay (100 * 100ms) in thong tin heap */
        if (u32Count100ms % 100 == 0) {
            /* ESP32-C3 khong co PSRAM, chi in SRAM noi bo */
            size_t sram_free = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);

            LREP("MAIN", "Free SRAM: %u KB",
                (unsigned int)(sram_free / 1024));
        }

        app_common_DelayMs(100);
    }
}