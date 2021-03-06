/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
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
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */
#include "cmsis_os.h"
#include "hid_report.h"
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern osMessageQueueId_t usbRxQueueHandle;
extern osMessageQueueId_t usbTxQueueHandle;
/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
HidReport_t rx_report;
HidReport_t tx_report;
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
  0x06, 0x00, 0xff,         // Usage Page (Vendor Defined Page 1)
    0x09, 0x01,              // USAGE (Vendor Usage 1)
    0xa1, 0x01,              // COLLECTION (Application)
    0x15, 0x00,                // LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,          // LOGICAL_MAXIMUM (255)

    0x75, 0x08,                // REPORT_SIZE (8)

    0x85, 0x01,                // Report Id 1
    0x95, 0x3f,                // REPORT_COUNT (63)
    0x09, 0x01,                // USAGE (Undefined)
    0x81, 0x02,                // INPUT (Data, Var, Abs)

    0x85, 0x01,                // Report Id 1
    0x95, 0x3f,                // REPORT_COUNT (63)
    0x09, 0x02,                // USAGE (Undefined)
    0x91, 0x02,                // OUTPUT (Data, Var, Abs)

    0x85, 0x02,                // Report Id 2
    0x95, 0x3f,                // REPORT_COUNT (63)
    0x09, 0x03,                // USAGE (Undefined)
    0xb1, 0x02,                // FEATURE (Data, Var, Abs)
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t *buffer);
static int8_t CustomHID_GetReportInput  (uint8_t event_idx, uint8_t* buffer, uint16_t* length);
static int8_t CustomHID_GetReportFeature(uint8_t event_idx, uint8_t* buffer, uint16_t* length);
static int8_t CustomHID_SetReportOutput (uint8_t event_idx, uint8_t* buffer);
static int8_t CustomHID_SetReportFeature(uint8_t event_idx, uint8_t* buffer);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS,
  CustomHID_GetReportInput,
  CustomHID_GetReportFeature,
  CustomHID_SetReportOutput,
  CustomHID_SetReportFeature
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t *_buffer)
{
  /* USER CODE BEGIN 6 */
  //memcpy(buffer, _buffer, 64); // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<!!!!!!!
  //USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, buffer, 64);
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
static int8_t CustomHID_GetReportInput(uint8_t event_idx, uint8_t* buffer, uint16_t* length)
{
  // as ReportID must reside inside the [0] byte

  switch(event_idx) {
    case 1: {
      if (osMessageQueueGet(usbTxQueueHandle, &tx_report, 0, 0) != osOK) {
        return (USBD_BUSY);
      }

      memcpy(buffer, &tx_report, USBD_CUSTOMHID_INREPORT_BUF_SIZE);
      *length = 64;
      return USBD_OK;
    }

    default: /* Report does not exist */
      return (USBD_FAIL);
  }
}

static int8_t CustomHID_GetReportFeature(uint8_t event_idx, uint8_t* buffer, uint16_t* length)
{
  // as ReportID must reside inside the [0] byte

  switch(event_idx) {
    case 1: {
      *length = 5;
      buffer[0] = event_idx;
      buffer[1] = 1;
      buffer[2] = 2;
      buffer[3] = 3;
      buffer[4] = 4;
      return USBD_OK;
    }

    default: /* Report does not exist */
      return (USBD_FAIL);
  }
}

static int8_t CustomHID_SetReportOutput(uint8_t event_idx, uint8_t* buffer)
{
  switch(event_idx) {
    case 1: {
      rx_report.reportId = event_idx;
      memcpy(&rx_report.data, buffer, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE - 1);

      if (osMessageQueuePut(usbRxQueueHandle, &rx_report, 0, 0) == osOK) {
        return USBD_OK;
      } else {
        return USBD_BUSY;
      }
    }

    default: /* Report does not exist */
      return USBD_FAIL;
   }

   //return (USBD_OK);
}

static int8_t CustomHID_SetReportFeature(uint8_t event_idx, uint8_t* buffer)
{
  switch(event_idx) {
    case 1: {
      return USBD_OK;
    }

    default: /* Report does not exist */
      return USBD_FAIL;
   }

   //return (USBD_OK);
}

/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

