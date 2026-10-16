#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "esp_ble_mesh_defs.h"

//=============  VENDOR MODEL DEFINITIONS ======================================
#define DF_MESH_CID_ESP                 0x02E5  /* Company ID Espressif */
#define DF_MESH_VND_MODEL_ID_CLIENT     0x0001  /* Client phia S3 (gui lenh) */
#define DF_MESH_VND_MODEL_ID_SERVER     0x0002  /* Server phia C3 (chap hanh) */

//=============  3-BYTE VENDOR OPCODES ======================================
#define DF_MESH_VND_OP_SET      ESP_BLE_MESH_MODEL_OP_3(0x01, DF_MESH_CID_ESP)  /* S3 gui lenh den C3   */
#define DF_MESH_VND_OP_GET      ESP_BLE_MESH_MODEL_OP_3(0x02, DF_MESH_CID_ESP)  /* S3 hoi trang thai C3 */
#define DF_MESH_VND_OP_STATUS   ESP_BLE_MESH_MODEL_OP_3(0x03, DF_MESH_CID_ESP)  /* C3 phan hoi len S3   */

/* ==========================================================================
 *  PAYLOAD TÙY BIẾN
 *  __attribute__((packed)) bắt buộc để tránh compiler chèn padding bytes.
 *  Tổng kích thước: 1 + 2 + 2 + 2 + 1 + 15 = 23 bytes
 * ========================================================================== */
typedef struct __attribute__((packed)) {
    uint8_t  u8Cmd;             // 1=Bat/Tat   2=Cai nguong   3=Dong bo trang thai 
    uint16_t u16PacketId;       // So thu tu goi, chong trung lap ban tin            
    int16_t  s16Temperature;    // Nhiet do (x10, vi du: 255 = 25.5 do C)           
    uint16_t u16Humidity;       // Do am (x10, vi du: 650 = 65.0%)                 
    uint8_t  u8RelayState;      // Trang thai relay dau ra (0=OFF, 1=ON)            
    char     acDeviceTag[15];   // Chuoi nhan thiet bi, ket thuc bang NUL           
} st_vendor_custom_data_t;

int32_t app_mesh_prov_SendVendorData(uint16_t u16DstAddr, const st_vendor_custom_data_t *pstData);
