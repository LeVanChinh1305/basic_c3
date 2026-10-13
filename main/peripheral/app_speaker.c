#include "app_speaker.h"
#include "app_common.h"

static const char *TAG = "app_speaker";

static float g_fGlobalVolumePercent = 80.0f;
static bool  g_bSpeakerInitialized  = false;
static bool  g_bAmpEnabled          = false;

int32_t app_speaker_Init(void)
{
    if (g_bSpeakerInitialized) {
        return ERROR_CODE_OK;
    }

    g_bSpeakerInitialized = true;
    LREP(TAG, "Khoi tao Speaker Driver (C3: Che do Log ao - Virtual/Log-only) thanh cong!");
    return ERROR_CODE_OK;
}

void app_speaker_EnableAmp(bool bEnable)
{
    g_bAmpEnabled = bEnable;
    LREP(TAG, "[SPEAKER LOG] Amplifier: %s", bEnable ? "ON (ENABLE)" : "OFF (DISABLE)");
}

int32_t app_speaker_SetVolume(float fPercent)
{
    if (fPercent < 0.0f) fPercent = 0.0f;
    if (fPercent > 100.0f) fPercent = 100.0f;

    g_fGlobalVolumePercent = fPercent;
    LREP(TAG, "[SPEAKER LOG] Cai dat am luong he thong: %.1f%%", g_fGlobalVolumePercent);
    return ERROR_CODE_OK;
}

float app_speaker_GetVolume(void)
{
    return g_fGlobalVolumePercent;
}

int32_t app_speaker_PlayByName(const char *pcFilename)
{
    if (pcFilename == NULL) {
        return ERROR_CODE_INVALID_PARAM;
    }

    if (!g_bSpeakerInitialized) {
        LREP_ERROR(TAG, "Speaker chua duoc khoi tao!");
        return ERROR_CODE_FAIL;
    }

    LREP(TAG, "[SPEAKER LOG] Phat am thanh file: \"%s\" (Am luong: %.1f%%)",
         pcFilename, g_fGlobalVolumePercent);

    return ERROR_CODE_OK;
}

void app_speaker_PlayBeep(int32_t s32FreqHz, int32_t s32DurationMs, int32_t s32VolumePercent)
{
    if (!g_bSpeakerInitialized) {
        LREP_ERROR(TAG, "Speaker chua duoc khoi tao!");
        return;
    }

    LREP(TAG, "[SPEAKER LOG] Phat tieng Beep: %d Hz | Thoi luong: %d ms | Am luong: %d%%",
         (int)s32FreqHz, (int)s32DurationMs, (int)s32VolumePercent);
}
