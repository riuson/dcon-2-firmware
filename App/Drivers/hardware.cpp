/*
 * hardware.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "hardware.h"

namespace App::Drivers
{

Hardware::Hardware() :
  _rtc(nullptr)
{
}

void Hardware::initialize()
{
  this->_rtc.initialize();
}

} /* namespace App::Drivers */
