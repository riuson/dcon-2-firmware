/*
 * Application.h
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Drivers/hardware.h"
#include "hid_report.h"

namespace App
{

class Application
{
public:
  Application();
  virtual ~Application() {}

  void initialize();

  void taskMain();
  void taskExchange();

private:
  Drivers::Hardware _hardware;
  HidReport_t _rxReport;
  HidReport_t _txReport;
};

} /* namespace App */

#endif /* APPLICATION_H_ */
