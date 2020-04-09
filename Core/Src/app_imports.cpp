/*
 * app_imports.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "application.h"
#include "app_imports.h"
#include <string.h>

static App::Application application;

uint8_t usb_rx_buffer[64];
uint8_t usb_rx_not_empty;
uint8_t usb_tx_buffer[64];
uint8_t usb_tx_ready;

void appPreInit(void)
{
  memset(usb_rx_buffer, 0, sizeof(usb_rx_buffer));
  memset(usb_tx_buffer, 0, sizeof(usb_tx_buffer));
  usb_rx_not_empty = false;
  usb_tx_ready = false;
}

void appTaskMain(void)
{
  application.taskMain();
}

void appTaskExchange(void)
{
  application.taskExchange();
}
