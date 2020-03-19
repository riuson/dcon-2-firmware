/*
 * Application.h
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Drivers/hardware.h"

namespace App
{

class Application
{
public:
  Application();
  virtual ~Application() {}

  void initialize();

  void taskMain();

private:
  Drivers::Hardware _hardware;
};

} /* namespace App */

#endif /* APPLICATION_H_ */
