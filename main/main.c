
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "system_init.h"
#include <string.h>
#include "log_task.h"
#include "IMU_task.h"
#include "freertos/queue.h"

TaskHandle_t logging_handle;
TaskHandle_t IMU_handle;

void app_main()
{
    system_init();
    log_q = xQueueCreate(16,sizeof(log_struct));
     
    xTaskCreate(LogTask,"log task",2048,NULL,1,&logging_handle);
    xTaskCreate(IMUTask,"IMU task",2048,NULL,1,&IMU_handle);
    
    return;
}
