#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "log_task.h"
#include "driver/uart.h"
#include "string.h"
#include "freertos/queue.h"
#include "stdarg.h"

QueueHandle_t log_q;

void log_t(const char *msg,...){
    log_struct log_buffer;
    va_list args;
    va_start(args,msg);
    vsnprintf(log_buffer.msg,sizeof(log_buffer.msg),msg,args);

    log_buffer.msg[sizeof(log_buffer.msg)-1] = '\0';

    xQueueSend(log_q,&log_buffer,portMAX_DELAY);
}

void LogTask(void *pvParameters){
    (void)pvParameters;
    log_struct log_buffer;
    while(1){
        xQueueReceive(log_q, &log_buffer, portMAX_DELAY);
        int bytes_written = uart_write_bytes(LOGGING_UART_PORT, log_buffer.msg, strlen(log_buffer.msg));
    }
}

