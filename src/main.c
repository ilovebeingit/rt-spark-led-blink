#include "stm32f4xx_hal.h"

// RT-Spark onboard LED pins
#define LED_BLUE_PIN   GPIO_PIN_11
#define LED_RED_PIN    GPIO_PIN_12
#define LED_GPIO_PORT  GPIOF

void SysTick_Handler(void) {
    HAL_IncTick();
}

static void GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable peripheral clock for GPIO Port F
    __HAL_RCC_GPIOF_CLK_ENABLE();

    // Configure PF11 and PF12 as outputs
    GPIO_InitStruct.Pin = LED_BLUE_PIN | LED_RED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

int main(void) {
    HAL_Init();
    GPIO_Init();

    while (1) {
        // Toggle both onboard LEDs every 500 ms
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_BLUE_PIN | LED_RED_PIN);
        HAL_Delay(500);
    }
}