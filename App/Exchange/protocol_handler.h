/*
 * protocol_handler.h
 *
 *  Created on: Apr 10, 2020
 *      Author: Vladimir
 */

#ifndef EXCHANGE_PROTOCOL_HANDLER_H_
#define EXCHANGE_PROTOCOL_HANDLER_H_

#include "cmsis_os.h"
#include "hid_report.h"

namespace App::Exchange
{

class ProtocolHandler
{
public:
  ProtocolHandler(osMessageQueueId_t rxQueue, osMessageQueueId_t txQueue);
  void handle();

private:
  osMessageQueueId_t _rxQueue;
  osMessageQueueId_t _txQueue;
  HidReport_t _rxReport;
  HidReport_t _txReport;

  bool getVersion(const HidReport_t &rxReport, HidReport_t &txReport);
};

} /* namespace App::Exchange */

#endif /* EXCHANGE_PROTOCOL_HANDLER_H_ */
