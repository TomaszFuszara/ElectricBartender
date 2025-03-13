/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_i2c.h"
#include <stdbool.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
struct lcd_disp disp;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  disp.addr = (0x27 << 1);
  disp.bl = true; //Podświelenie załączone
  lcd_init(&disp);
  lcd_prog(&disp);
  lcd_display(&disp);

  int ekran = 0;
  int liczba_szklanek = 1;
  int alkohol = 1;
  int napoj = 1;
  int zmiana = 1;
  int procedura = 1;
  int pozycja = 500;
  int zmiana_pozycji = 400;
  int czas_otwarcia = 1900;

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_GPIO_WritePin(Zawor_alkohol_GPIO_Port, Zawor_alkohol_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(Zawor_napoj_GPIO_Port, Zawor_napoj_Pin, GPIO_PIN_SET);

	  if(HAL_GPIO_ReadPin(Przycisk1_GPIO_Port, Przycisk1_Pin) == GPIO_PIN_RESET){
	  		HAL_Delay(200);
	  		ekran = ekran+zmiana;
	  	  }

	  switch(ekran){
	  case 0:
		  sprintf((char *)disp.f_line, "Liczba szklanek:");
		  lcd_display(&disp);
		  if(HAL_GPIO_ReadPin(Przycisk2_GPIO_Port, Przycisk2_Pin) == GPIO_PIN_RESET){
		  	  		HAL_Delay(200);
		  	  		liczba_szklanek = liczba_szklanek+zmiana;
		  	  		if(liczba_szklanek >= 5){
		  	  		liczba_szklanek = 5;
		  	  		}
		  	  	  }
		  if(HAL_GPIO_ReadPin(Przycisk3_GPIO_Port, Przycisk3_Pin) == GPIO_PIN_RESET){
		  		  	  		HAL_Delay(200);
		  		  	  		liczba_szklanek = liczba_szklanek - zmiana;
		  		  	  		if(liczba_szklanek <= 1){
		  		  	  		liczba_szklanek = 1;
		  		  	  		}
		  		  	  	  }
		  sprintf((char *)disp.s_line, "%d", liczba_szklanek);
		  	  		  lcd_display(&disp);
		  break;

	  case 1:
	  		  sprintf((char *)disp.f_line, "Ilo%c%c alkoholu: ", '\x6', '\x1');
	  		  lcd_display(&disp);
	  		  if(HAL_GPIO_ReadPin(Przycisk2_GPIO_Port, Przycisk2_Pin) == GPIO_PIN_RESET){
	  		  	  		HAL_Delay(200);
	  		  	  	alkohol = alkohol+zmiana;
	  		  	  		if(alkohol >= 10){
	  		  	  		alkohol = 10;
	  		  	  		}
	  		  	  	  }
	  		  if(HAL_GPIO_ReadPin(Przycisk3_GPIO_Port, Przycisk3_Pin) == GPIO_PIN_RESET){
	  		  		  	  		HAL_Delay(200);
	  		  		  	  alkohol = alkohol - zmiana;
	  		  		  	  		if(alkohol <= 1){
	  		  		  	  	alkohol = 1;
	  		  		  	  		}
	  		  		  	  	  }
	  		  sprintf((char *)disp.s_line, "%d ml ", alkohol*10);
	  		  	  		  lcd_display(&disp);
	  		  break;

	  case 2:
	  	  		  sprintf((char *)disp.f_line, "Ilo%c%c napoju:   ", '\x6', '\x1');
	  	  		  lcd_display(&disp);
	  	  		  if(HAL_GPIO_ReadPin(Przycisk2_GPIO_Port, Przycisk2_Pin) == GPIO_PIN_RESET){
	  	  		  	  		HAL_Delay(200);
	  	  		  	  napoj = napoj + zmiana;
	  	  		  	  		if(napoj >= 10){
	  	  		  	  		napoj = 10;
	  	  		  	  		}
	  	  		  	  	  }
	  	  		  if(HAL_GPIO_ReadPin(Przycisk3_GPIO_Port, Przycisk3_Pin) == GPIO_PIN_RESET){
	  	  		  		  	  		HAL_Delay(200);
	  	  		  		  	  napoj = napoj - zmiana;
	  	  		  		  	  		if(napoj <= 1){
	  	  		  		  	  	napoj = 1;
	  	  		  		  	  		}
	  	  		  		  	  	  }
	  	  		  sprintf((char *)disp.s_line, "%d ml ", napoj*10);
	  	  		  	  		  lcd_display(&disp);
	  	  		  break;

	  case 4:
		  sprintf((char *)disp.f_line, "Nalewanie.      ");
		  sprintf((char *)disp.s_line, "                ");
		  lcd_display(&disp);

		  //nalewa wódę w ilości int=alkohol
		  //obrót
		  while(liczba_szklanek > 0){
			  HAL_Delay(1000);
			  sprintf((char *)disp.s_line, "%d          ", liczba_szklanek);
		  	  lcd_display(&disp);
		  	  //..................................................................Otwarcie zaworu, odmierzenie, zamknięcie zaworu
		  	  HAL_GPIO_WritePin(Zawor_alkohol_GPIO_Port, Zawor_alkohol_Pin, GPIO_PIN_RESET);
		  	  HAL_Delay(alkohol*czas_otwarcia);
		  	  HAL_GPIO_WritePin(Zawor_alkohol_GPIO_Port, Zawor_alkohol_Pin, GPIO_PIN_SET);
		  	  HAL_Delay(1000);
		  	  //.........................................................................
			  pozycja = pozycja + zmiana_pozycji;
		  	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pozycja);
		  	  //..................................................................Otwarcie zaworu, odmierzenie, zamknięcie zaworu
		  	  HAL_GPIO_WritePin(Zawor_napoj_GPIO_Port, Zawor_napoj_Pin, GPIO_PIN_RESET);
		  	  HAL_Delay(napoj*czas_otwarcia);
		  	  HAL_GPIO_WritePin(Zawor_napoj_GPIO_Port, Zawor_napoj_Pin, GPIO_PIN_SET);
		  	  HAL_Delay(1000);
		  	  liczba_szklanek--;
		      //.........................................................................
		  	  //HAL_Delay(1000);
		  	  }

			  //nalewa przepoję w ilości int=napoj
			  //powtórzyć int=liczba_szklanek razy

		  //Po zakończeniu procesu nalewania:

		  HAL_Delay(1000);
		  sprintf((char *)disp.f_line, "Dzi%ckuj%c.       ", '\x2', '\x2');
		  sprintf((char *)disp.s_line, "                ");
		  lcd_display(&disp);
		  HAL_Delay(1000);

		  ekran = 0;
		  liczba_szklanek = 1;
		  alkohol = 1;
		  napoj = 1;
		  pozycja = 500;
	  	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pozycja);
		  break;

	  }

	  //..........................................................................................................................
//	  if(procedura <= 5){
//			pozycja = pozycja + zmiana_pozycji;
//	  			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pozycja);
//	  			  HAL_Delay(1000);
//	  			sprintf((char *)disp.f_line, "Dzi%ckuj%c.       ", '\x2', '\x2');
//	  		  sprintf((char *)disp.s_line, "%d              ", pozycja);
//	  		  lcd_display(&disp);
//	  		  procedura++;
//
//	  }
//	  else{
//		  sprintf((char *)disp.s_line, "Koniec          ", procedura);
//		  	  		  lcd_display(&disp);
//		  	  		  pozycja = 50;
//	  }


//	  if(procedura <= 5){
//		  pozycja = pozycja + zmiana_pozycji;
//		  HAL_Delay(1000);
//		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pozycja);
//	  }else{
//		  procedura = 1;
//		  pozycja = 500;
//	  }
//	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500);
//	  		  HAL_Delay(1000);__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000);
//		  HAL_Delay(1000);
//		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1500);
//			  HAL_Delay(1000);
//			  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 2000);
//			  		  HAL_Delay(1000);
//			  		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 2500);
//			  			  HAL_Delay(1000);


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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
