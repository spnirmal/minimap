#ifndef IMU_TASK_H
#define IMU_TASK_H

#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_MASTER_SCL_IO 9
#define I2C_MASTER_SDA_IO 8
#define I2C_MASTER_FREQ_HZ 400000

//register address definitions
#define MPU9250_ADRR  0x68
#define WHO_AM_I_REG  0x75
#define PWR_MGMT_1    0x6B
#define ACCEL_CONFIG  0x1C
#define ACCEL_CONFIG2 0x1D
#define ACCEL_XOUT_H  0x3B
#define ACCEL_XOUT_L  0x3C
#define ACCEL_YOUT_H  0x3D
#define ACCEL_YOUT_L  0x3E
#define ACCEL_ZOUT_H  0x3F
#define ACCEL_ZOUT_L  0x40      

extern i2c_master_bus_handle_t imu_handle;
extern i2c_master_dev_handle_t imu_dev;

extern i2c_master_bus_config_t imu_config;
extern i2c_device_config_t dev_cfg;

void IMUTask(void *pvParameters);

#endif