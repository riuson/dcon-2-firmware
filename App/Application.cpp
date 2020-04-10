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
      if (this->_rxReport.reportId == 1 && this->_rxReport.data[0] == 0xab) {
        this->_txReport.reportId = 1;
        this->_txReport.data[0] = 0xba;
        this->_txReport.data[1] = ~this->_rxReport.data[1];
        osMessageQueuePut(usbTxQueueHandle, &this->_txReport, 0, 1000);
      }

      osDelay(1000);
    }

    osDelay(100);
  }
}

} /* namespace App */
