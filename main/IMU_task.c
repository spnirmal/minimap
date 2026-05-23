#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "IMU_task.h"
#include "log_task.h"

i2c_master_bus_config_t imu_config = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = I2C_MASTER_SDA_IO,
    .scl_io_num = I2C_MASTER_SCL_IO,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
};

i2c_master_bus_handle_t imu_handle;
i2c_master_dev_handle_t imu_dev;

i2c_device_config_t dev_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = 0x68,
    .scl_speed_hz = 400000,
};

void imu_configure(){
    
}

void IMUTask(void *pvParameters){
    uint8_t who_am_i;
    uint8_t reg = WHO_AM_I_REG;
    esp_err_t ret;
    const TickType_t poll_delay = pdMS_TO_TICKS(100);  // Poll every 100ms

    while(1){
        vTaskDelay(poll_delay);
        ret = i2c_master_transmit_receive(imu_dev, &reg, 1, &who_am_i, 1, -1);
        if(ret == ESP_OK){
            log_t("IMU WHO_AM_I: 0x%02X\n", who_am_i);
        } else {
            log_t("IMU read error: 0x%X\n", ret);
        }
    }  

}

