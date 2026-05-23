#include "driver/uart.h"
#include "system_init.h"
#include "IMU_task.h"

const uart_port_t uart_num = UART_NUM_1;

uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 122,
};




void configure_uart_port(){
    esp_err_t err;
    
    err = uart_driver_install(uart_num, 1024, 0, 0, NULL, 0);
    ESP_ERROR_CHECK(err);
    
    err = uart_param_config(uart_num, &uart_config);
    ESP_ERROR_CHECK(err);
    
    err = uart_set_pin(uart_num, 17, 18, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    ESP_ERROR_CHECK(err);
}

void imu_init(){
    esp_err_t err;

    err = i2c_new_master_bus(&imu_config,&imu_handle);
    ESP_ERROR_CHECK(err);
    err = i2c_master_bus_add_device(imu_handle,&dev_cfg,&imu_dev);
    ESP_ERROR_CHECK(err);

}

void system_init(){ 
    configure_uart_port();
    imu_init();
}