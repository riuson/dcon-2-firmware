/*
 * hardware.h
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#ifndef DRIVERS_HARDWARE_H_
#define DRIVERS_HARDWARE_H_

#include "Rtc/rtc.h"

namespace App::Drivers
{

class Hardware
{
public:
  Hardware();
  virtual ~Hardware() {}

  void initialize();

private:
  Rtc::Rtc _rtc;
};

} /* namespace App::Drivers */

#endif /* DRIVERS_HARDWARE_H_ */
