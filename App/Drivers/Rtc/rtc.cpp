/*
 * rtc.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "rtc.h"

namespace App::Drivers::Rtc
{

Rtc::Rtc(RTC_HandleTypeDef *hrtc) :
  _hrtc(hrtc)
{
}

void Rtc::initialize()
{
}

} /* namespace App::Drivers::Rtc */
