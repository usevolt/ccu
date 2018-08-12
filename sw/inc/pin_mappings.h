/*
 * pin_mappings.h
 *
 *  Created on: Jan 27, 2015
 *      Author: usenius
 *
 *  Defines keypad pin mappings for different pcb revisions used
 */

#ifndef UW_MB_SRC_PIN_MAPPINGS_H_
#define UW_MB_SRC_PIN_MAPPINGS_H_

#include <uv_gpio.h>
#include <uv_timer.h>
#include <uv_adc.h>
#include <uv_pwm.h>



#define MCP2515_INT			P0_18
#define MCP2515_RESET		P1_1


#define STEER_PWMA			PWM2_3
#define STEER_PWMB			PWM0_0
#define STEER_SENSE			ADC0_0

#define DRIVE1_PWMA			PWM1_4
#define DRIVE1_PWMB			PWM0_1
#define DRIVE1_SENSE		ADC0_3

#define DRIVE2_PWMA			PWM0_4
#define DRIVE2_PWMB			PWM1_3
#define DRIVE2_SENSE		ADC0_8

#define BOOM_VDD_OUT		P1_5
#define BOOM_VDD_SENSE		ADC1_10

#define BRAKE_OUT			P0_26
#define BRAKE_SENSE			ADC1_8


#endif /* UW_MB_SRC_PIN_MAPPINGS_H_ */
