/*
 * hardware.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "hardware.h"
#include <rtc.h>

namespace App::Drivers
{

Hardware::Hardware() :
  _rtc(&hrtc)
{
}

void Hardware::initialize()
{
  this->_rtc.initialize();
}

} /* namespace App::Drivers */
