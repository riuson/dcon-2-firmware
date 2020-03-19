/*
 * Application.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "Application.h"
#include "cmsis_os.h"

namespace App
{

Application::Application()
{
}

Application::~Application()
{
}

void Application::taskMain()
{
  while (true) {
    osDelay(1);
  }
}

} /* namespace App */
