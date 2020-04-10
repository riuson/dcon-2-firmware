/*
 * app_imports.h
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#ifndef INC_APP_IMPORTS_H_
#define INC_APP_IMPORTS_H_

#ifdef __cplusplus
extern "C" {
#endif

void appPreInit(void);
void appTaskMain(void);
void appTaskExchange(void);

extern uint8_t usb_rx_buffer[64];
extern uint8_t usb_rx_not_empty;
extern uint8_t usb_tx_buffer[64];
extern uint8_t usb_tx_ready;

#ifdef __cplusplus
}
#endif


#endif /* INC_APP_IMPORTS_H_ */
