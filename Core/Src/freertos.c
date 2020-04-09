/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "app_imports.h"
#include "hid_report.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for mainTask */
osThreadId_t mainTaskHandle;
uint32_t mainTaskBuffer[ 256 ];
osStaticThreadDef_t mainTaskControlBlock;
const osThreadAttr_t mainTask_attributes = {
  .name = "mainTask",
  .stack_mem = &mainTaskBuffer[0],
  .stack_size = sizeof(mainTaskBuffer),
  .cb_mem = &mainTaskControlBlock,
  .cb_size = sizeof(mainTaskControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for taskExchange */
osThreadId_t taskExchangeHandle;
uint32_t taskExchangeBuffer[ 256 ];
osStaticThreadDef_t taskExchangeControlBlock;
const osThreadAttr_t taskExchange_attributes = {
  .name = "taskExchange",
  .stack_mem = &taskExchangeBuffer[0],
  .stack_size = sizeof(taskExchangeBuffer),
  .cb_mem = &taskExchangeControlBlock,
  .cb_size = sizeof(taskExchangeControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for usbRxQueue */
osMessageQueueId_t usbRxQueueHandle;
uint8_t usbRxQueueBuffer[ 2 * sizeof( HidReport_t ) ];
osStaticMessageQDef_t usbRxQueueControlBlock;
const osMessageQueueAttr_t usbRxQueue_attributes = {
  .name = "usbRxQueue",
  .cb_mem = &usbRxQueueControlBlock,
  .cb_size = sizeof(usbRxQueueControlBlock),
  .mq_mem = &usbRxQueueBuffer,
  .mq_size = sizeof(usbRxQueueBuffer)
};
/* Definitions for usbTxQueue */
osMessageQueueId_t usbTxQueueHandle;
uint8_t usbTxQueueBuffer[ 2 * sizeof( HidReport_t ) ];
osStaticMessageQDef_t usbTxQueueControlBlock;
const osMessageQueueAttr_t usbTxQueue_attributes = {
  .name = "usbTxQueue",
  .cb_mem = &usbTxQueueControlBlock,
  .cb_size = sizeof(usbTxQueueControlBlock),
  .mq_mem = &usbTxQueueBuffer,
  .mq_size = sizeof(usbTxQueueBuffer)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartMainTask(void *argument);
void StartTaskExchange(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  appPreInit();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of usbRxQueue */
  usbRxQueueHandle = osMessageQueueNew (2, sizeof(HidReport_t), &usbRxQueue_attributes);

  /* creation of usbTxQueue */
  usbTxQueueHandle = osMessageQueueNew (2, sizeof(HidReport_t), &usbTxQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of mainTask */
  mainTaskHandle = osThreadNew(StartMainTask, NULL, &mainTask_attributes);

  /* creation of taskExchange */
  taskExchangeHandle = osThreadNew(StartTaskExchange, NULL, &taskExchange_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartMainTask */
/**
  * @brief  Function implementing the mainTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartMainTask */
void StartMainTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartMainTask */
  appTaskMain();
  /* USER CODE END StartMainTask */
}

/* USER CODE BEGIN Header_StartTaskExchange */
/**
* @brief Function implementing the taskExchange thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskExchange */
void StartTaskExchange(void *argument)
{
  /* USER CODE BEGIN StartTaskExchange */
  appTaskExchange();
  /* USER CODE END StartTaskExchange */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
