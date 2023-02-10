/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <stdbool.h>

#define N_VAL 64
#define LINE_MAX_LENGTH 80

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// hej
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int __io_putchar(int ch)
{
	if (ch == '\n')
	{
		__io_putchar('\r');
	}

	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);

	return 1;
}

uint8_t stan = 0;

const uint8_t gamma8[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
	2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
	5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
	115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
	144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
	177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
	215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255};

bool is_button_pressed(void)
{
	if (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_RESET)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	stan++;
	if (stan > 6)
	{
		stan = 0;
	}
}

void efektDiody_1(void)
{
	while (1)
	{
		uint8_t r = gamma8[rand() % 256];
		uint8_t g = gamma8[rand() % 256];
		uint8_t b = gamma8[rand() % 256];

		for (int led = 0; led < 7; led++)
		{
			ws2812b_set_color(led, r, g, b);
			ws2812b_update();
			HAL_Delay(50);
		}
		HAL_Delay(200);
		for (int led = 0; led < 7; led++)
		{
			ws2812b_set_color(led, 0, 0, 0);
			ws2812b_update();
			HAL_Delay(50);
		}
		if (stan != 1)
		{
			break;
		}
	}
}

void efektDiody_3(void)
{
	while (1)
	{

		for (int led = 0; led < 7; led++)
		{
			uint8_t r = gamma8[rand() % 256];
			uint8_t g = gamma8[rand() % 256];
			uint8_t b = gamma8[rand() % 256];

			ws2812b_set_color(led, r, g, b);
			ws2812b_update();
			HAL_Delay(50);
		}
		HAL_Delay(200);
		for (int led = 0; led < 7; led++)
		{
			ws2812b_set_color(led, 0, 0, 0);
			ws2812b_update();
			HAL_Delay(50);
		}
		if (stan != 3)
		{
			break;
		}
	}
}

void efektDiody_5(void)
{
	while (1)
	{
		for (int led = 6; led >= 0; led -= 2)
		{
			uint8_t r = gamma8[rand() % 256];
			uint8_t g = gamma8[rand() % 256];
			uint8_t b = gamma8[rand() % 256];

			ws2812b_set_color(led, r, g, b);
			ws2812b_update();
			HAL_Delay(50);
		}
		for (int led = 1; led <= 5; led += 2)
		{
			uint8_t r = gamma8[rand() % 256];
			uint8_t g = gamma8[rand() % 256];
			uint8_t b = gamma8[rand() % 256];

			ws2812b_set_color(led, r, g, b);
			ws2812b_update();
			HAL_Delay(50);
		}
		HAL_Delay(200);
		for (int led = 0; led < 7; led++)
		{
			ws2812b_set_color(led, 0, 0, 0);
			ws2812b_update();
			HAL_Delay(50);
		}
		if (stan != 5)
		{
			break;
		}
	}
}
static char czerwona[] = "czerwona";
static char niebieska[] = "niebieska";
static char zielona[] = "zielona";
static char biala[] = "biala";
static char wylacz[] = "wylacz";
static char line_buffer[LINE_MAX_LENGTH + 1];
uint32_t line_length;
int line_append_done = 0;

void line_append(uint8_t value)
{
	if (value == '\r' || value == '\n')
	{
		// odebraliśmy znak końca linii
		if (line_length > 0)
		{
			line_buffer[line_length] = '\0';
			// przetwarzamy dane
			printf("%s\n", line_buffer); // wysyła na oba uarty
			if (!strcmp(&line_buffer, &czerwona))
			{
				stan = 0;
			}
			if (!strcmp(&line_buffer, &niebieska))
			{
				stan = 4;
			}
			if (!strcmp(&line_buffer, &zielona))
			{
				stan = 2;
			}
			if (!strcmp(&line_buffer, &biala))
			{
				stan = 7;
			}
			if (!strcmp(&line_buffer, &wylacz))
			{
				stan = 6;
			}

			line_append_done = 1;
			line_length = 0;
		}
	}
	else
	{
		line_append_done = 0;
		if (line_length >= LINE_MAX_LENGTH)
		{
			line_length = 0;
		}
		line_buffer[line_length++] = value;
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART2_UART_Init();
	MX_TIM3_Init();
	MX_TIM2_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	//  HAL_TIM_Base_Start(&htim3);
	//
	//  uint8_t test[] = { 100, 0, 32, 32, 32, 32, 32, 100 }; // 0/100 10/100 20/100 ... wypełnienie PWM
	//  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, &test, sizeof(test));
	//
	//  HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);

	//  HAL_TIM_Base_Start(&htim3);
	//
	//  uint8_t test[40 + 7 * 24 + 1] = {0};
	//
	//  // Zerowanie kolorów wszystkich diod
	//  for (int i = 0; i < 7 * 24; i++)
	//    test[40 + i] = 32;
	//
	//  // Włącz jedną diodę
	//  test[40] = 64;
	//
	//  // Stan wysoki na końcu
	//  test[40 + 7 * 24] = 100;
	//
	//  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, &test, sizeof(test));

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	ws2812b_init();

	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_1); // inicjalizacja liczników
	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3); // inicjalizacja pwm
	HAL_Delay(1000);

	float odleglosc_stara = 0.0f;
	float odleglosc;
	uint8_t value;
	while (1)
	{
		if (HAL_UART_Receive(&huart1, (uint8_t *)&value, sizeof(value), 0) == HAL_OK)
		{

			line_append(value);
		}

		//	  uint8_t r = gamma8[rand() % 256];
		//	  uint8_t g = gamma8[rand() % 256];
		//	  uint8_t b = gamma8[rand() % 256];
		//
		//	  for (int led = 0; led < 7; led++) {
		//	    ws2812b_set_color(led, r, g, b);
		//	    ws2812b_update();
		//	    HAL_Delay(100);
		//	  }

		switch (stan)
		{
		case 0:
			for (int led = 0; led < 7; led++)
			{
				ws2812b_set_color(led, 255, 0, 0);
				ws2812b_update();
			}
			break;
		case 1:
			efektDiody_1();
			break;
		case 2:
			for (int led = 0; led < 7; led++)
			{
				ws2812b_set_color(led, 0, 255, 0);
				ws2812b_update();
			}
			break;
		case 3:
			efektDiody_3();
			break;
		case 4:
			for (int led = 0; led < 7; led++)
			{
				ws2812b_set_color(led, 0, 0, 255);
				ws2812b_update();
			}
			break;
		case 5:
			efektDiody_5();
			break;
		case 6:
			ws2812b_init();
			break;
		case 7:
			for (int led = 0; led < 7; led++)
			{
				ws2812b_set_color(led, 255, 255, 255);
				ws2812b_update();
			}
			break;
		default:
			break;
		}
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
