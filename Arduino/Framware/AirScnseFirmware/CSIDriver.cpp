//
//  CSIDriver.cpp
//  AirSense Firmware
//

#include "CSIDriver.h"

#include <Arduino.h>
#include <WiFi.h>

extern "C"
{
    #include "esp_wifi.h"
    #include "esp_event.h"
}

CSIDriver&
CSIDriver::shared()
{
    static CSIDriver driver;
    return driver;
}

CSIDriver::CSIDriver()
{
    _started = false;
}

bool CSIDriver::begin()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println(" AirSense CSI Driver");
    Serial.println("==============================");

#ifdef CONFIG_ESP_WIFI_CSI_ENABLED

    Serial.println("CSI Supported : YES");

#else

    Serial.println("CSI Supported : NO");
    return false;

#endif

    if (!enableCSI())
        return false;

    if (!registerCallback())
        return false;

    _started = true;

    Serial.println("CSI Driver Ready");

    return true;
}

bool CSIDriver::started() const
{
    return _started;
}

bool CSIDriver::enableCSI()
{
    Serial.println("Enabling CSI...");

    wifi_csi_config_t config = {};

    config.lltf_en = true;
    config.htltf_en = true;
    config.stbc_htltf2_en = true;
    config.ltf_merge_en = true;

    config.channel_filter_en = true;
    config.manu_scale = false;
    config.shift = false;

    esp_err_t err;

    err = esp_wifi_set_csi_config(&config);

    if (err != ESP_OK)
    {
        Serial.printf(
            "esp_wifi_set_csi_config Failed : %d\n",
            err
        );

        return false;
    }

    err = esp_wifi_set_csi(true);

    if (err != ESP_OK)
    {
        Serial.printf(
            "esp_wifi_set_csi Failed : %d\n",
            err
        );

        return false;
    }

    return true;
}

bool CSIDriver::registerCallback()
{
    Serial.println("Registering CSI Callback...");

    esp_err_t err =
        esp_wifi_set_csi_rx_cb(
            &CSIDriver::wifiCsiCallback,
            nullptr
        );

    if (err != ESP_OK)
    {
        Serial.printf(
            "CSI Callback Failed : %d\n",
            err
        );

        return false;
    }

    Serial.println("CSI Callback Registered");

    return true;
}

void CSIDriver::wifiCsiCallback(
    void* ctx,
    wifi_csi_info_t* info
)
{
    if (info == nullptr)
    {
        return;
    }

    Serial.println();
    Serial.println("=========== CSI Packet ===========");

    Serial.print("RSSI : ");
    Serial.println(info->rx_ctrl.rssi);

    Serial.print("Channel : ");
    Serial.println(info->rx_ctrl.channel);

    Serial.print("Length : ");
    Serial.println(info->len);

    Serial.println("==================================");
}