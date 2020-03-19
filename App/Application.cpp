/*
 * Application.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "application.h"
#include "cmsis_os.h"

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

} /* namespace App */
