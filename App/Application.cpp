/*
 * Application.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "application.h"
#include "cmsis_os.h"

extern osMessageQueueId_t usbRxQueueHandle;
extern osMessageQueueId_t usbTxQueueHandle;

namespace App
{

Application::Application()
{
}

void Application::initialize()
{
  this->_hardware.initialize();
}

void Application::taskMain()
{
  while (true) {
    osDelay(1);
  }
}

void Application::taskExchange()
{
  while (true) {
    if (osMessageQueueGet(usbRxQueueHandle, &this->_rxReport, 0, 1000) == osOK) {
      osDelay(1000);
    }

    osDelay(100);
  }
}

} /* namespace App */
