/*
 * app_imports.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "application.h"
#include "app_imports.h"
#include <new>
#include <string.h>

static uint8_t app_space[sizeof(App::Application)];
static App::Application *pApp;

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

  pApp = reinterpret_cast<App::Application *>(app_space);
  new (app_space) App::Application();
}

void appTaskMain(void)
{
  pApp->taskMain();
}

void appTaskExchange(void)
{
  pApp->taskExchange();
}
