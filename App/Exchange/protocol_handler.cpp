/*
 * protocol_handler.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: Vladimir
 */

#include "protocol_handler.h"
#include "Resources/revision.h"
#include <stdio.h>

namespace App::Exchange
{

ProtocolHandler::ProtocolHandler(osMessageQueueId_t rxQueue, osMessageQueueId_t txQueue) :
  _rxQueue(rxQueue),
  _txQueue(txQueue)
{
}

void ProtocolHandler::handle()
{
  while (true) {
    if (osMessageQueueGet(this->_rxQueue, &this->_rxReport, 0, 1000) == osOK) {
      if (this->_rxReport.reportId == 1) {
        bool result = false;

        switch (this->_rxReport.data[0]) {
          case 1: {
            result = this->getVersion(this->_rxReport, this->_txReport);
            break;
          }
        }

        if (result) {
          this->_txReport.reportId = 1;
          osMessageQueuePut(this->_txQueue, &this->_txReport, 0, 1000);
        }
      }
    }
  }
}

bool ProtocolHandler::getVersion(const HidReport_t &rxReport, HidReport_t &txReport)
{
  static const char *commitHash = COMMIT_REVISION;
  static const char *commitTime = COMMIT_TIME;
  snprintf(
    reinterpret_cast<char *>(txReport.data),
    sizeof(txReport.data),
    "%.*s\n%.*s",
    7, commitHash,
    26, commitTime);
  return true;
}

} /* namespace App::Exchange */
