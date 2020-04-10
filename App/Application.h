/*
 * Application.h
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Drivers/hardware.h"
#include "Exchange/protocol_handler.h"

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
  Exchange::ProtocolHandler _protocol;
};

} /* namespace App */

#endif /* APPLICATION_H_ */
