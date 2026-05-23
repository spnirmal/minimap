#ifndef LOG_TASK_H
#define LOG_TASK_H

#include "freertos/FreeRTOS.h"
#include "driver/uart.h"
#include "freertos/queue.h"

#define LOGGING_UART_PORT UART_NUM_1

extern QueueHandle_t log_q;

typedef struct{
    uint32_t timestamp;
    uint8_t level;
    char msg[128];
}log_struct;

void LogTask(void *pvParameters);

void log_t(const char *msg);

#endif