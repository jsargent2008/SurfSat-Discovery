/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void SetupLTC(uint8_t *pData01);
static void ReadLTC(uint8_t *pData01);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//testestsetesetst
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  //uint8_t I2CError;
  /* USER CODE END 2 */
  uint8_t pData01, pData00, pData07, pData08;
  uint8_t Tint[2], Vcc[2] , V6[2];
  float Tint1, Vcc1, V61;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //HAL_Delay(100);
  //SetupLTC(&pData01);
  //SetupLTC(&pData01);
  //SetupLTC(&pData01);
  /*HAL_Delay(100);
  HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //status of channels
  HAL_Delay(100);
  HAL_I2C_Mem_Write(&hi2c2, 0x90, 0xF0, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //enable all channels
  HAL_Delay(100);
*/
  HAL_Delay(100);
  ReadLTC(&pData01);

  HAL_Delay(100);
  SetupLTC(&pData01);

  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  HAL_Delay(100);
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
	  HAL_Delay(100);
	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

	  HAL_Delay(100);
	  ReadLTC(&pData01);

	  if((pData01 >> 1)&1)
	  {
		  HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x1A, I2C_MEMADD_SIZE_8BIT, Tint, 2, 1000); //Reading Internal Temperature
		  //Tint[0] ^= Tint[0]<<8;
		  Tint1 = (((Tint[0]-128)<<8)+Tint[1])*0.0625;
	  }

	  if(pData01&1)
	  {
		  HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x1C, I2C_MEMADD_SIZE_8BIT, Vcc, 2, 1000); //Reading Internal VCC
		  //Vcc[0] ^= Vcc[0]<<8;
		  Vcc1 = (((Vcc[0]-128)<<8)+Vcc[1])*0.00030518+2.5;
	  }

	  HAL_Delay(100);
	  HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x00, I2C_MEMADD_SIZE_8BIT, &pData00, 2, 1000);


	  if((pData00 >> 6)&1)
	  {
		  HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x14, I2C_MEMADD_SIZE_8BIT, V6, 2, 1000); //Reading Internal VCC
		  //Vcc[0] ^= Vcc[0]<<8;
		  V61 = (((V6[0]-128)<<8)+V6[1])*0.00030518+2.5;
	  }
	  printf("%x\n",pData01);

	  //HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000);
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C2 init function */
static void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_Pin|LEDB7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin LEDB7_Pin */
  GPIO_InitStruct.Pin = LED_Pin|LEDB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void SetupLTC (uint8_t *pData01)
{
	  uint8_t datatosend[2];
	  datatosend[0] = 0x01;
	  datatosend[1] = 0xF8;
	  uint8_t data2send = 0xF8;

	  HAL_Delay(100);
	  //HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
	  HAL_I2C_Mem_Write(&hi2c2, 							0x90, 				0x01, I2C_MEMADD_SIZE_8BIT, &data2send, 				1, 				1000); //enable all channels
	  return;
}
void ReadLTC (uint8_t *pData01)
{
	HAL_Delay(100);
    HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, pData01, 1, 1000); //status of channels
    //HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);
    	  //HAL_I2C_IsDeviceReady(&hi2c2,0x90, 1, 100);

    	  /* HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
    	   *
    		HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

    	   	 HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    	   	 */

    	  //HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //status of channels

    	  //I2CError = HAL_I2C_Mem_Write(&hi2c2, 0x90, *datatosend, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //enable all channels
    	  //HAL_Delay(100);
    	  //HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x00, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //status of channels
    	  /*HAL_Delay(100);
    	  HAL_Delay(100);
    	  HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //status of channels
    	  HAL_Delay(100);
    	  HAL_I2C_Mem_Write(&hi2c2, 0x90, 0xF0, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //enable all channels*/

    	  //HAL_Delay(1000);
    	  //pData06 = 0x06;
    	   //HAL_I2C_Master_Transmit(&hi2c2, 0x90, &pData06, 1, 10000);
    	  //I2CError =
    	   //printf("%i\n",I2CError);
    	  //HAL_Delay(1000);
    	  //HAL_I2C_Mem_Read(&hi2c2,0x90, 0x07, I2C_MEMADD_SIZE_8BIT, &pData07, 1, 1000);
    	  //HAL_Delay(1000);
    	  //HAL_I2C_Mem_Read(&hi2c2,0x90, 0x08, I2C_MEMADD_SIZE_8BIT, &pData08, 1, 1000);
    	  //HAL_Delay(50);
    return;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
