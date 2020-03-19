/*
 * rtc.h
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#ifndef DRIVERS_RTC_RTC_H_
#define DRIVERS_RTC_RTC_H_

#include <stm32l4xx_hal.h>

namespace App::Drivers::Rtc
{

class Rtc
{
public:
  Rtc(RTC_TypeDef *rtc);
  virtual ~Rtc() {}

  void initialize();
};

} /* namespace App::Drivers::Rtc */

#endif /* DRIVERS_RTC_RTC_H_ */
