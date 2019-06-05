
//#include "esp_system.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
 
 #include "esp_log.h"

/**
 * This is an example which echos any data it receives on UART1 back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: UART1
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 * - Pin assignment: see defines below
 */

#define ECHO_TEST_TXD  (GPIO_NUM_4)
#define ECHO_TEST_RXD  (GPIO_NUM_5)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define BLINK_GPIO     (CONFIG_BLINK_GPIO)

#define BUF_SIZE (1024)

static const char* TAG = "bacr";

static void
uart_task(void *pvParameters)
{

    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate              = 230400,
        .data_bits              = UART_DATA_8_BITS,
        .parity                 = UART_PARITY_DISABLE,
        .stop_bits              = UART_STOP_BITS_1,
        .flow_ctrl              = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh    = 122,
        .use_ref_tick           = true
    };
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(UART_NUM_1, data, BUF_SIZE, 20 / portTICK_RATE_MS);

        
        //ESP_LOGW(TAG, ".");
        
        printf(".");
        fflush(stdout);
        if (len <= 0) {
            continue;
        }

        // Write data back to the UART
        printf("len=%d %.*s\n", len, len, data);
    }
}

static void
led_task(void *pvParameters)
{
    
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(BLINK_GPIO);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while(1) {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        ESP_LOGW(TAG, "blink");
        //printf("blink");
        //fflush(stdout);
    }
}

extern "C" {

void app_main()
{
    //nvs_flash_init();

    /*
    	static inline IRAM_ATTR BaseType_t xTaskCreate(
			TaskFunction_t pvTaskCode,
			const char * const pcName,
			const uint32_t usStackDepth,
			void * const pvParameters,
			UBaseType_t uxPriority,
			TaskHandle_t * const pvCreatedTask)
    */
    xTaskCreate(uart_task, "uart_task", 2048, NULL, 6, NULL);
    //xTaskCreate(led_task , "led_task", 2048, NULL, 5, NULL);

    //led_task(NULL);

}

}