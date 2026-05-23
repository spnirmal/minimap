#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "IMU_task.h"
#include "log_task.h"


static uint8_t x_h;
static uint8_t x_l;
static uint8_t y_h;
static uint8_t y_l;
static uint8_t z_h;
static uint8_t z_l;

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

void accel_read(void);

void imu_configure(void){
    uint8_t data[2];
    data[0] = ACCEL_CONFIG;
    data[1] = 0x08;
    i2c_master_transmit(imu_dev,data,2,-1);
}

void IMUTask(void *pvParameters){
    esp_err_t ret;

    while(1){
        vTaskDelay(pdMS_TO_TICKS(500));
        
        accel_read();
        log_t("accel readings x_h:%d x_l:%d y_h:%d y_l:%d z_h:%d z_l:%d\r\n",x_h,x_l,y_h,y_l,z_h,z_l);

    }  


}

void accel_read(void){
        esp_err_t ret;
        uint8_t xh_addr = ACCEL_XOUT_H;
        uint8_t xl_addr = ACCEL_XOUT_L;
        uint8_t yh_addr = ACCEL_YOUT_H;
        uint8_t yl_addr = ACCEL_YOUT_L;
        uint8_t zh_addr = ACCEL_ZOUT_H;
        uint8_t zl_addr = ACCEL_ZOUT_L;

        ret = i2c_master_transmit_receive(imu_dev, &xh_addr, 1, &x_h, 1, -1);
        if(ret != ESP_OK){
            log_t("failed at x_h");
        }

        ret = i2c_master_transmit_receive(imu_dev, &xl_addr, 1, &x_l, 1, -1);
        if(ret != ESP_OK){
            log_t("failed at x_l");
        }
   
        ret = i2c_master_transmit_receive(imu_dev, &yh_addr, 1, &y_h, 1, -1);
        if(ret != ESP_OK){
            log_t("failed at y_h");
        }
   

        ret = i2c_master_transmit_receive(imu_dev, &yl_addr, 1, &y_l, 1, -1);
        if(ret != ESP_OK){
            log_t("failed at y_l");
        }


        ret = i2c_master_transmit_receive(imu_dev, &zh_addr, 1, &z_h, 1, -1);
        if(ret != ESP_OK){
            log_t("failed at z_h");
        }
        
        ret = i2c_master_transmit_receive(imu_dev, &zl_addr, 1, &z_l, 1, -1);
        if(ret != ESP_OK){
            log_t("failed at z_l");
        }
        
}

