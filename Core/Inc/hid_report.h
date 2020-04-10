/*
 * report.h
 *
 *  Created on: Apr 10, 2020
 *      Author: Vladimir
 */

#ifndef INC_HID_REPORT_H_
#define INC_HID_REPORT_H_

#include <stdint.h>

typedef struct __attribute__((__packed__)) _HID_REPORT {
  uint8_t reportId;
  uint8_t data[63];
} HidReport_t;

#endif /* INC_HID_REPORT_H_ */
