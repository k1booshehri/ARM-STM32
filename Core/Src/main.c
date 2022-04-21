#include "main.h"
#include "lcd_txt.h"
#include <stdio.h>

#define KEYPAD_C1 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)
#define KEYPAD_C2 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)
#define KEYPAD_C3 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)

#define KEYPAD_NUM0 0
#define KEYPAD_NUM1 1
#define KEYPAD_NUM2 2
#define KEYPAD_NUM3 3
#define KEYPAD_NUM4 4
#define KEYPAD_NUM5 5
#define KEYPAD_NUM6 6
#define KEYPAD_NUM7 7
#define KEYPAD_NUM8 8
#define KEYPAD_NUM9 9
#define KEYPAD_STAR 10
#define KEYPAD_POUND 11

ADC_HandleTypeDef hadc1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);

uint8_t keypad_scan(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	char string[2];

	uint8_t key_res;
	uint16_t delayt = 0;
	uint16_t pit = 0;
	uint16_t milk=1000;
	uint16_t water =1000;
	
	
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
	
	// LCD
	lcd_init();
	lcd_clear();

	while (1)
	{
		
		lcd_puts(0, 0, (int8_t*)"type?");
		while(1){
		key_res = keypad_scan();
		if (key_res!=255){
			if (key_res==1)
				delayt=20000;
			if (key_res==2)
				delayt=30000;
			if (key_res==3)
				delayt=50000;
			if (key_res==4)
				delayt=60000;
			break;
		}
	}
	
		lcd_puts(0, 0, (int8_t*)"cup?");
			while(1)
		{
			key_res = keypad_scan();
			if (key_res!=255){
			if (key_res==1)
				pit=10;
			if (key_res==2)
				pit=12;
			if (key_res==3)
				pit=15;
			break;
		}
  }
		
			lcd_puts(0, 0, (int8_t*)"milk?");
		while(1){
		key_res = keypad_scan();
		if (key_res!=255){
			if (key_res==0)
				delayt+=0;
			if (key_res==1)
				delayt+=10000;

			break;
		}
	}
		
		lcd_clear();
		lcd_puts(0, 0, (int8_t*)"wait");
		HAL_Delay(delayt*pit);
		water=water-90;
	if(key_res==1)
		milk-=70;
	if(water<0 || milk<0)
		lcd_puts(0, 0, (int8_t*)"not enough!");
	else
		lcd_puts(0, 0, (int8_t*)"ready! press");
		lcd_puts(1, 0, (int8_t*)"9 to release");
		
		
		
}
}
uint8_t keypad_scan() {
	uint8_t result = 255;
	uint16_t delay = 1;
	////////////////////////  ROW1 ////////////////////////
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState)1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState)0); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState)0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState)0);
	
	HAL_Delay(delay);
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
		result = KEYPAD_NUM1;
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
		result = KEYPAD_NUM2;
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))
		result = KEYPAD_NUM3;

	////////////////////////  ROW2 ////////////////////////
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState)0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState)1); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState)0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState)0);
	
	HAL_Delay(delay);
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
		result = KEYPAD_NUM4;
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
		result = KEYPAD_NUM5;
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))
		result = KEYPAD_NUM6;

	////////////////////////  ROW3 ////////////////////////
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState)0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState)0); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState)1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState)0);
	
	HAL_Delay(delay);
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
		result = KEYPAD_NUM7;
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
		result = KEYPAD_NUM8;
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))
		result = KEYPAD_NUM9;

	////////////////////////  ROW4 ////////////////////////
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState)0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState)0); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState)0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState)1);
	
	HAL_Delay(delay);
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)) {
		result = KEYPAD_STAR;
		return 10;
	}
		
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6))
		result = KEYPAD_NUM0;
	else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))
		result = KEYPAD_POUND;

	return result;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 PA6 PA7 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB5 PB6
                           PB7 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

#ifdef  USE_FULL_ASSERT
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

