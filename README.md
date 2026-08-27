# RT-Spark (STM32F4) Onboard LED Blink Project

An embedded systems project built using **VS Code** and **PlatformIO** for the **RT-Spark (星火1号)** development board utilizing the STM32 HAL framework.

---

## Project Overview
This firmware initializes the STM32 GPIO peripherals and toggles the onboard blue and red status LEDs at 500 ms intervals using hardware timer delays (`HAL_Delay`).

* **Board:** RT-Spark (星火1号)
* **Architecture:** STM32F4 Series
* **Framework:** STM32Cube HAL (`stm32cube`)
* **IDE:** Visual Studio Code + PlatformIO Extension
* **Debug Interface:** Onboard ST-LINK via USB-DBG

---

## Hardware Configuration

| Component | Pin Assignment | Output Mode |
| :--- | :--- | :--- |
| **Blue LED** | `GPIO_PIN_11` (`PF11`) | Push-Pull |
| **Red LED** | `GPIO_PIN_12` (`PF12`) | Push-Pull |

---

## Code Implementation
```c
#include "stm32f4xx_hal.h"

#define LED_BLUE_PIN   GPIO_PIN_11
#define LED_RED_PIN    GPIO_PIN_12
#define LED_GPIO_PORT  GPIOF

void SysTick_Handler(void) {
    HAL_IncTick();
}

static void GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOF_CLK_ENABLE();

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
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_BLUE_PIN | LED_RED_PIN);
        HAL_Delay(500);
    }
}
